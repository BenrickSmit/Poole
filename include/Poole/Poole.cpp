#include "Poole.h"  

Poole::Poole(){
    // Do nothing for now
    init();
}

Poole::~Poole(){
    // Closes the threads if they aren't already
    if(!m_is_stopped)
    std::cout << "THREAD POOL DTOR" << std::endl; 
        stop_pool();
}


int Poole::get_possible_threads() {
    return m_possible_threads;
}


int Poole::add_function(std::function<void()> added_function) {
    // Ensure thread-safe queue pushing
    std::unique_lock<std::mutex> mlock(m_queue_mutex);
    m_function_pool.push(std::bind(added_function));
    mlock.unlock();
    m_cond_var.notify_one();

    return m_function_pool.size();
}


void Poole::stop_pool() {
    // this function will call the shutdown method and set the
    // shutdown variable
    set_pool_shutdown_status(true);
    shutdown();
}


void Poole::init() {
    // Set the total number of supported threads
    m_possible_threads = std::thread::hardware_concurrency();

    // Set the shutdown value
    set_pool_shutdown_status(false);
    m_is_stopped = false;

    // Create the required threads
    for(auto i = 0; i < m_possible_threads; i++){
        // Create the Thread information
        ThreadInfo info;
        info.set_id(i);

        // Create the thread
        std::thread new_thread = std::thread([this, i]{event_function_loop(i);});

        // Create the multimap
        m_thread_info_pool.insert({i, info});
        m_thread_pool.insert({i, std::move(new_thread)});
    }
}


void Poole::event_function_loop(int id) {
    auto thread_information = find(id);
    std::function<void()>   function_to_execute;    

    while(true){//(!thread_information.shutdown_status()){
        { // Scope
            // Ensure Thread-safe operation
            std::unique_lock<std::mutex> mlock(m_queue_mutex);
        
            // Set additional information
            thread_information.set_busy_status(true);
            thread_information.set_completed_status(false);
        
                //m_cond_var.wait(mlock, [this](){return (!m_function_pool.empty() || get_pool_shutdown_status());});
                //m_cond_var.wait(mlock);
                //m_cond_var.wait_for(mlock, std::chrono::microseconds(10));
                while((m_function_pool.empty())){
                    m_cond_var.wait_for(mlock, std::chrono::microseconds(10));
                
                    //if((!get_pool_shutdown_status()) && (m_function_pool.empty())){
                    if(get_pool_shutdown_status()) {
                        return ;
                    }
                }

            function_to_execute = m_function_pool.front();
            m_function_pool.pop();
        } // End SCope

        // Execute the program
        function_to_execute();
        
        // Set additional information
        thread_information.set_busy_status(false);
        thread_information.set_completed_status(true);        
    }// End of while
}


ThreadInfo& Poole::find(int id) {
    // Search for the Item in the vector, and return the ThreadInfo
    static ThreadInfo to_return;

    for (auto i = 0; i < m_thread_info_pool.size(); i++){
        if(m_thread_info_pool.at(i).id() == id){
           to_return = m_thread_info_pool.at(i); 
        }
    }// End of for loop

    return to_return;
}


void Poole::shutdown() {
    // Tell the threads' functions to end
        
    // Setup the shutdown status for each thread and it's information
    // m_cond_var.notify_all();
    // Join the threads to allow them to close
    // Empty the function pool if it isn't empty
    // Clear the other maps

    std::unique_lock<std::mutex> mlock(m_queue_mutex);
    set_pool_shutdown_status(true);
    mlock.unlock();

    m_cond_var.notify_all();

    // Complete the threads
    for (auto i = 0; i < m_thread_pool.size(); i++){
        if(m_thread_pool[i].joinable()){
            //std::cout << "<JOINED THREAD " << i << "/" << m_thread_pool.size()-1 << ">" << std::endl;
            //m_thread_pool[i].detach();
            m_cond_var.notify_all();
            m_thread_pool[i].join();
        }
    }

    // Clear the functions in the pool
    while(m_function_pool.empty()){
        m_function_pool.pop();
    }

    // Clear the other std::map<> structures
    m_thread_info_pool.clear();
    m_thread_pool.clear();

    m_is_stopped = true;
}


void Poole::set_pool_shutdown_status(bool value) {
    m_shutdown_status = value;
}


bool Poole::get_pool_shutdown_status() {
    return m_shutdown_status;
}