#include "Poole.h"

// the constructor just launches some amount of m_worker_threads
Poole::Poole(){
    init();
}
   
// the destructor joins all threads
Poole::~Poole(){
    // Finish the thread execution
    force_thread_stop();
}


//Initialises the thread Poole
void Poole::init(){
    // Ensure the program continues
    m_stop_Poole = false;
    m_has_stopped = false;

    m_total_possible_threads = std::thread::hardware_concurrency();

    // Create the threads
    for(auto i = 0; i < m_total_possible_threads; ++i){
        // Create the thread information for use
        ThreadInfo thread_info;
        thread_info.set_id(i);
        thread_info.set_busy_status(false);
        thread_info.set_finished_status(false);

        m_worker_threads.insert({i, std::thread([this](){this->infinite_event_loop();})});
        m_worker_thread_info.insert({i, thread_info});
        //m_worker_threads.push(std::thread([this](){this->infinite_event_loop();}));
    }
}


void Poole::force_thread_stop() {
    // stop all threads
    if(m_has_stopped == false){
        m_stop_Poole = true;
        m_condition.notify_all();
     
        // join them
        for(size_t i = 0;i<m_worker_threads.size();++i){
            // Join threads if they haven't already been joined
            if(m_worker_threads[i].joinable()){
                m_worker_threads[i].join();
            }
        }

        //Ensure the function Poole is empty
        if(!m_function_tasks.empty()){
        m_function_tasks.clear();
        }

        m_has_stopped = true;
    }
}

// add new work item to the Poole
void Poole::add_function(std::function<void()> function_to_add){
    { // Ensure no other functions are added to the queue
        std::unique_lock<std::mutex> lock(m_queue_mutex);
    
        // Append the function for use
        m_function_tasks.push_back(std::bind(function_to_add));
    } // Release the mutex
     
    // Wake up one thread to execute the function
    m_condition.notify_one();
}


bool Poole::is_busy() {
    // Look through the ThreadInfo structures to see whether the threads are busy
    // executing. If they are, return true
    bool to_return = false;
    ThreadInfo info;

    for (auto counter = 0; counter < get_possible_threads(); counter++){
        info = m_worker_thread_info.find(counter)->second;
        if((info.get_finished_status() == false) && (info.get_busy_status() == true)){
            to_return = true;
            break;
        }
    }//end of for loop

    return to_return;
}


void Poole::wait() {
    // This function will stop the execution of the main thread for a bit
    // while it ensures that no other functions are executing. It helps
    // to ensure task that should be finished can be finished
    // Ensure the function queue is empty
    std::unique_lock<std::mutex> lock(m_queue_mutex);
    // Works but hangs
    m_finished_condition.wait(lock, [this](){return m_function_tasks.empty() && (is_busy()==false);});
    //m_finished_condition.wait(lock, [this](){return (is_busy()==false);});
    
}


void Poole::force_shutdown() {
    // Forcefully "call the dtor"
    force_thread_stop();
}


int Poole::get_possible_threads() {
    return m_total_possible_threads;
}

void Poole::infinite_event_loop(int id){
    std::function<void()> function_to_execute;
    while(true){
        {   // Acquire lock on the queue for execution
            std::unique_lock<std::mutex> lock(m_queue_mutex);
             
            // Find a function to execute if it exists
            while(!m_stop_Poole && m_function_tasks.empty())
            { // if there are none wait for notifications
                m_condition.wait(lock);
            }
 
            // Exit the Poole if forced to stop
            if(m_stop_Poole)
                return;
 
            // Get the function from the queue
            function_to_execute = m_function_tasks.front();
            m_function_tasks.pop_front();
 
        }   // Release lock on the mutex
 
        // Set the information for the ThreadInfo object
            std::unique_lock<std::mutex> latch(m_queue_mutex);
            m_worker_thread_info.find(id)->second.set_busy_status(true);
            m_worker_thread_info.find(id)->second.set_finished_status(false);

        // Execute the function
        function_to_execute();

        // Update the thread information for use
            m_worker_thread_info.find(id)->second.set_busy_status(false);
            m_worker_thread_info.find(id)->second.set_finished_status(true);
            latch.unlock();
            m_finished_condition.notify_one();
    }
}   