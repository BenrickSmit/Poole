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
 * @modified: 25 November 2020
 * 
 * @brief: This contains the implementation of the Poole class for concurrency
 *          in c++11/14
 * 
 */ 

#include "Poole.h"

// The Constructor creates the Threads and sets some objects used by the pool
Poole::Poole(int32_t total_threads){
    init(total_threads);
}
   
// The Deconstructor uses the same method as the force_shutdown method and joins all threads
Poole::~Poole(){
    // Finish the thread execution
    force_stop();
}

void Poole::add_function(std::function<void()> function_to_add) {
    // This function is to add a function to the function_queue for execution
    {
        std::unique_lock<std::recursive_mutex> queue_lock(m_queue_mutex);

        // Make sure that you can't add functions if the function is 
        // pool is stopped, or exited
        if (m_stop_processing || m_emergency_stop){
            std::cerr << "ERROR: Poole::add_function() - attempted to add function to stopepd pool.";
            exit(1);
        }

        // Add the function to the queue
        m_function_queue.emplace(std::bind(function_to_add));
    }
    // Notify one thread in the thread pool that a function has been added
    m_threadpool_notifier.notify_one();
}


//Initialises the thread Poole
void Poole::init(int32_t total_threads){
    // Ensure the program continues
    m_stop_processing = false;
    m_emergency_stop = false;
    m_paused = false;

    // Set the number of threads based on a few factors:
    // - There needs to be at least 1 thread
    // - Any negative threads default to the total capable by the hardware
    // - The specified number should be between 1 - MAX_POSSIBLE_THREADS
    int32_t possible_threads = total_threads;
    int32_t MAX_THREADS_POSSIBLE = std::thread::hardware_concurrency();
    if (total_threads < 1){
        // 0 and negative threads
        possible_threads = MAX_THREADS_POSSIBLE;
    } else{
        // Set thread number to maximum number possible if the number specified
        // is bigger than the total possible on the system.
        if(total_threads > MAX_THREADS_POSSIBLE){
            possible_threads = MAX_THREADS_POSSIBLE;
        }
    }
    // Set the nubmer of threads to create
    set_possible_threads(possible_threads);

    // Reserve exactly the amount of space needed for the threads
    m_threads.reserve(get_possible_threads());
    m_thread_info.reserve(get_possible_threads());

    // Create the threads and the thread information
    for(auto i = 0; i < get_possible_threads(); ++i){
        // Create the thread information for use
        ThreadInfo thread_info;
        thread_info.set_ID(i);
        thread_info.set_busy(true);
        thread_info.set_done(false);

        // Create the thread that will wait on functions
        //m_worker_threads.insert({i, std::thread([this](){this->infinite_event_loop();})});
        //m_worker_thread_info.insert({i, thread_info});
        m_threads.emplace_back([this, i](){zombie_loop(i);});
        m_thread_info.push_back(thread_info);
    }
}

void Poole::pause(bool pause) {
    // Scoped mutex lack to ensure only one function executes it
    {
        std::unique_lock<std::recursive_mutex> queue_lock(m_queue_mutex);
        m_paused = pause;
    }// release scoped mutex

    // Notify all threads to stop execution and wait for an unlock
    m_threadpool_notifier.notify_all();
}

void Poole::wait() {
    // This function waits until all threads are finished executing to 
    // continue processing.
    /*std::unique_lock<std::recursive_mutex> queue_lock(m_queue_mutex);
        
    m_wait_execution_notifier.wait(
        queue_lock, 
        [this](){
            // False to wait; True to continue waiting
            return m_function_queue.empty() && !is_busy();
        }); 
    */
    while (true){
        if(m_function_queue.empty() && is_done()){
            pause(false);
            break;
        }else{
            pause(true);
        }
    }
}

bool Poole::is_done() {
    // Scan through the ThreadInfo data to see whether the threads are busy 
    // executing. If they are, return false.
    bool to_return = true;
    ThreadInfo info;

    for(auto counter = 0; counter < get_possible_threads(); counter++){
        info = m_thread_info.at(counter);
        if((info.is_done() == false)){
            to_return = false;
            break;
        }
    }

    return to_return;
}

bool Poole::is_busy() {
    // Scan through the ThreadInfo data to see whether the threads are busy
    // executing a funciton. If they are return true, if not, return false;
    bool to_return = false;
    ThreadInfo info;

    // Slightly slower, but still good to use for now
    for (auto thread : m_thread_info){
        if (thread.is_busy()){
            to_return = true;
            break;
        }
    }

    return to_return;
}

void Poole::zombie_loop(uint32_t thread_id) {
    // This function is an infinite loop used to obtain functions from the list
    // to execute
    while (true){
        std::function<void()> function_to_execute;

        // Scoped Wait for available tasks
        {
            std::unique_lock<std::recursive_mutex> queue_lock(m_queue_mutex);
            m_threadpool_notifier.wait(
                queue_lock,
                [this](){
                    return (!m_function_queue.empty() && m_paused) 
                    || m_stop_processing
                    || m_emergency_stop;
                }
            );

            // Stop the function when there are no more tasks and asked to stop,
            // or if requested to stop via the emergency stop procedure
            if((m_stop_processing && m_function_queue.empty()) 
                || m_emergency_stop){
                return;
            }

            // Retrieve the function to execute
            function_to_execute = std::move(m_function_queue.front());
            m_function_queue.pop();
        }

        // Update statistics for the thread
        m_thread_info.at(thread_id).set_busy(true);
        m_thread_info.at(thread_id).set_done(false);
        

        // Execute the task and add information about the loop
        function_to_execute();

        // Update job statistics for the thread
        m_thread_info.at(thread_id).set_done(true);
        m_thread_info.at(thread_id).set_busy(false);
        m_thread_info.at(thread_id).add_task();

        //Inform the wait condition_variable that a function has been completed
        m_wait_execution_notifier.notify_one();
    }
}

void Poole::force_stop() {
    // Ensure the mutex automatically releases once it's out of scope
    {
        std::unique_lock<std::recursive_mutex> queue_lock(m_queue_mutex);
        stop_processing(true);
    }// Automatically release mutex

    // Wake up all threads to let them exit their loops
    m_threadpool_notifier.notify_all();

    // Join the threads for to finish execution
    for (auto i = 0; i < get_possible_threads(); i++){
        if(m_threads.at(i).joinable()){
            m_threads.at(i).join();
        }
    }
}

void Poole::stop_processing(bool con) {
    m_stop_processing = con;
}

void Poole::set_possible_threads(uint32_t possible_threads) {
    m_total_possible_threads = possible_threads;
}


// Returns the number of threads possible on the current hardware.
uint32_t Poole::get_possible_threads() {
    return m_total_possible_threads;
}

std::vector<unsigned long long> Poole::get_thread_total_tasks_executed() {
    std::vector<unsigned long long> to_return;

    for(auto thread_info: m_thread_info){
        to_return.push_back(thread_info.get_tasks());
    }

    return to_return;
}

std::vector<unsigned long long> Poole::get_thread_total_uptime() {
    std::vector<unsigned long long> to_return;

    for(auto thread_info: m_thread_info){
        to_return.push_back(thread_info.get_uptime());
    }

    return to_return;
}

uint64_t Poole::get_total_tasks_executed() {
    uint64_t to_return = 0;

    // Sum all the tasks executed
    for (auto count : get_thread_total_tasks_executed()){
        to_return += count;
    }

    return to_return;
}

uint64_t Poole::get_total_uptime() {
    uint64_t to_return = 0;

    // Scan for the thread with the longest running time and use that
    for(auto uptime : get_thread_total_uptime()){
        if(uptime >= to_return){
            to_return = uptime;
        }
    }

    return to_return;
}

std::string Poole::statistics() {
    std::string to_return = "";

    // Add the information for each individual thread
    for (auto thread_info: m_thread_info){
        to_return += "Thread ";
        
        if (thread_info.get_ID() < 10){
            to_return += "00";
        }else if (thread_info.get_ID() < 100) {
            to_return += "0";
        } 
        to_return += std::to_string(thread_info.get_ID());
        to_return += " " + std::to_string(thread_info.get_tasks()) + " tasks,";
        to_return += " " + std::to_string(thread_info.get_uptime()) + " ms";
        to_return += "\n";
    }

    // Add the summary information for all threads
    to_return += "\n";
    to_return += "Total Tasks:  " + std::to_string(get_total_tasks_executed()) + "\n";
    to_return += "Total Uptime: " + std::to_string(get_total_uptime())+ " ms \n";

    return to_return;
}