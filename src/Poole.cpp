/**   Copyright 2020 Benrick Smit
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
*/
/**
 * @author: Benrick Smit
 * @email: metatronicprogramming@hotmail.com
 * @date: 20 June 2020
 * @modified: 20 June 2020
 * 
 * @brief: This is the main class implementation using std::deque, std:condition_variable, std::map, and std::thread.
 * 
 */ 

#include "Poole.h"

// The Constructor creates the Threads and sets some objects used by the pool
Poole::Poole(){
    init();
}
   
// The Deconstructor uses the same method as the force_shutdown method and joins all threads
Poole::~Poole(){
    // Finish the thread execution
    force_thread_stop();
}


//Initialises the thread Poole
void Poole::init(){
    // Ensure the program continues
    m_stop_poole = false;
    m_has_stopped = false;

    // How many threads are possible on the current hardware
    m_total_possible_threads = std::thread::hardware_concurrency();
    if (m_total_possible_threads < 1){
        m_total_possible_threads = 1;
    }

    // Create the threads and the thread information
    for(auto i = 0; i < m_total_possible_threads; ++i){
        // Create the thread information for use
        ThreadInfo thread_info;
        thread_info.set_id(i);
        thread_info.set_busy_status(false);
        thread_info.set_finished_status(false);
        thread_info.set_start_time();
        thread_info.reset_finished_tasks();

        // Create the thread that will wait on functions
        m_worker_threads.insert({i, std::thread([this](){this->infinite_event_loop();})});
        m_worker_thread_info.insert({i, thread_info});
    }
}


// Forces the threads to join, and removes all functions in the queue
void Poole::force_thread_stop() {
    // stop all threads
    if(m_has_stopped == false){
        m_stop_poole = true;
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

// Add new functions to the pool in a thread-safe method
void Poole::add_function(std::function<void()> function_to_add){
    { // Ensure no other functions are added to the queue while this function is added; Ensures thread-safety
        std::unique_lock<std::mutex> lock(m_queue_mutex);
    
        // Append the function for use
        m_function_tasks.push_back(std::bind(function_to_add));
        // Wake up one thread to execute the function just appended. Works on a FIFO principle.
        m_condition.notify_one();
    } // Release the mutex (for thread-safety)
    //m_condition.notify_one();
}


// Determines whether at least one function is busy executing.
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


// Wait until is_busy is true, to ensure some functions which need to be finished executing before continuing the program are finished.
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


// Forces the threads to stop executing before the ctor is done.
void Poole::force_shutdown() {
    // Forcefully "call the dtor"
    force_thread_stop();
}


// Returns the number of threads possible on the current hardware.
int Poole::get_possible_threads() {
    return m_total_possible_threads;
}


unsigned long long Poole::get_total_tasks_at(int id) {
    return m_worker_thread_info.find(id)->second.get_total_tasks();
}


unsigned long long Poole::get_uptime_at(int id) {
    return m_worker_thread_info.find(id)->second.get_uptime();
}


std::vector<unsigned long long> Poole::get_thread_uptimes() {
    std::vector<unsigned long long> to_return;

    for (auto i = 0; i < get_possible_threads(); i++){
        to_return.push_back(m_worker_thread_info.find(i)->second.get_uptime());
    }

    return to_return;
}


std::vector<unsigned long long> Poole::get_thread_total_tasks() {
    std::vector<unsigned long long> to_return;

    for (auto i = 0; i < get_possible_threads(); i++){
        to_return.push_back(m_worker_thread_info.find(i)->second.get_total_tasks());
    }

    return to_return;
}


// An event loop which looks for new functions added to the pool.
void Poole::infinite_event_loop(int id){
    std::function<void()> function_to_execute;
    while(true){
        {   // Acquire lock on the queue for execution
            std::unique_lock<std::mutex> lock(m_queue_mutex);
             
            // Find a function to execute if it exists
            while(!m_stop_poole && m_function_tasks.empty()){ 
                // if there are none wait for notifications
                m_condition.wait(lock);
                //m_condition.wait(lock, [&](){return !m_stop_poole || m_function_tasks.empty();});
            }
 
            

            // Exit the Poole if forced to stop
            if(m_stop_poole)
                return;
 
            // Get the function from the queue
            function_to_execute = m_function_tasks.front();
            m_function_tasks.pop_front();
 
        }   // Release lock on the mutex
 
        // Set the information for the ThreadInfo object
            //std::unique_lock<std::mutex> latch(m_queue_mutex);
            m_worker_thread_info.find(id)->second.set_busy_status(true);
            m_worker_thread_info.find(id)->second.set_finished_status(false);
            
        // Execute the function
        function_to_execute();

        // Update the thread information for use
            m_worker_thread_info.find(id)->second.set_busy_status(false);
            m_worker_thread_info.find(id)->second.set_finished_status(true);
            m_worker_thread_info.find(id)->second.add_finished_task();
            //latch.unlock();
            m_finished_condition.notify_one();
    }
}   