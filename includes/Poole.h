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
 * @brief: This is the main class interface with documentation for how to use the thread pool class.
 * 
 */ 

#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <map>
#include <vector>
#include <functional>
 
// ADD the following functionality
// - Thread Information
// - A function to ensure another function can see whether the threads have finished executing
// - Adding in std::map instead of std::vector();
class ThreadInfo{
	public:
	// Getters
	bool get_busy_status(){return m_is_busy;}
	bool get_finished_status(){return m_is_finished;}
	int get_id(){return m_thread_id;}
	
	void set_busy_status(bool value) {m_is_busy = value;}
	void set_finished_status(bool value) {m_is_finished = value;}
	void set_id(int value) {m_thread_id = value;}
	
	// Setters
	private:
	bool m_is_busy;
	bool m_is_finished;
	int m_thread_id;
};

class Poole {
public:
	//Ctor and Dtor
	/**
	 * @brief Construct a new Poole object
	 */
    Poole();
	/**
	 * @brief Destroy the Poole object
	 */
    ~Poole();

	// Main interface with the program
	/**
	 * @brief This function adds a function to a list of functions that can be executed by random
	 * thread.
	 * 
	 * @param function the function to execute later.
	 */
    void add_function(std::function<void ()> function);    
	
	// Determines whether all the functions have finished executing
	/**
	 * @brief This function determines whether at least one thread is still executing.
	 * 
	 * @return true if at least one thread is executing.
	 * @return false if all threads have finished executing.
	 */
	bool is_busy();

	// Waits the execution of the main thread until all threads have finished computing.
	/**
	 * @brief wait until all threads have finished executing all functions in the pool.
	 */
	void wait();

	// Forces the shutdown of the threads if necessary
	/**
	 * @brief force the shutdown of the threads and remove all functions in the pool. This may
	 * cause some memory problems.
	 */
	void force_shutdown();

	// Display the total possible threads for the system
	/**
	 * @brief Get the possible threads supported by the system.
	 * 
	 * @return int 
	 */
	int get_possible_threads();

private:
	// Delete certain functions
	Poole(const Poole*) = delete;
	Poole(const Poole&&) = delete;

	// Initialise the threads and the exit condition
	/**
	 * @brief setup all the member variables correctly.
	 */
	void init();

	// Ensure a safe ending for the threads
	/**
	 * @brief The internal function used by both the dtor and force_shutdown();
	 * 
	 */
	void force_thread_stop();

	// The infinite loops that ensure the functions get executed
	/**
	 * @brief an event loop that obtains a function and executes it.
	 * 
	 * @param id an int value used to identify the thread executing it.
	 */
	void infinite_event_loop(int id = 0);

    // The Poole of threads and their information
    std::map<int, std::thread> m_worker_threads;
	std::map<int, ThreadInfo> m_worker_thread_info;
 
    // The Poole of functions to execute
    std::deque<std::function<void()>> m_function_tasks;
 
    // Ensure the threads use the queue in a thread-safe manner
    std::mutex m_queue_mutex;
    std::condition_variable m_condition;
	std::condition_variable m_finished_condition;
    bool m_stop_Poole;
	int m_total_possible_threads;

	bool m_has_stopped;
};