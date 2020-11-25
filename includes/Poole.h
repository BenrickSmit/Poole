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
#include <chrono>
 
class ThreadInfo{
	public:
	// Getters
	bool get_busy_status(){return m_is_busy;}
	bool get_finished_status(){return m_is_finished;}
	int get_id(){return m_thread_id;}
	uint get_uptime() {return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now() - m_start_time).count();}
	uint64_t get_total_tasks() {return m_total_tasks;}
	void add_finished_task() {m_total_tasks+=1;}
	void reset_finished_tasks() {m_total_tasks = 0;}
	
	void set_busy_status(bool value) {m_is_busy = value;}
	void set_finished_status(bool value) {m_is_finished = value;}
	void set_id(int value) {m_thread_id = value;}
	void set_start_time() {m_start_time = std::chrono::system_clock::now();}
	
	// Setters
	private:
	bool m_is_busy;
	bool m_is_finished;
	int m_thread_id;
	std::chrono::_V2::system_clock::time_point m_start_time;
	unsigned long long m_total_tasks;
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

	// Thread Information
	/**
	 * @brief Get the total tasks completed by an individual thread
	 * 
	 * @param position demarcates the index of the thread
	 * @return unsigned long long indicating the number of tasks completed
	 */
	unsigned long long get_total_tasks_at(int id);
	/**
	 * @brief Get the uptime of an individual thread in milliseconds
	 * 
	 * @param position demarcates the index of the thread
	 * @return unsigned long long indicating the uptime in milliseconds
	 */
	unsigned long long get_uptime_at(int id);
	/**
	 * @brief Get the thread uptimes for all threads available
	 * 
	 * @return std::vector<unsigned long long> a vector of all uptimes
	 */
	std::vector<unsigned long long> get_thread_uptimes();
	/**
	 * @brief Get the total tasks completed for all threads available
	 * 
	 * @return std::vector<unsigned long long> a vector of all tasks completed
	 */
	std::vector<unsigned long long> get_thread_total_tasks();

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
    mutable std::mutex m_queue_mutex;
    std::condition_variable m_condition;
	std::condition_variable m_finished_condition;
    bool m_stop_poole;
	int m_total_possible_threads;

	bool m_has_stopped;
};