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
 * @brief: This is the main class interface with documentation for how to use the thread pool class.
 * 
 */ 

#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <map>
#include <vector>
#include <functional>
#include <chrono>
#include <future>
#include <iostream>
 
#include "ThreadInfo.h"

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
	 * @brief Adds a function, likely a lambda, to execute in the any thread
	 * 
	 * @param function_to_add is a lambda or a void function to execute
	 */
	void add_function(std::function<void()> function_to_add);
	
	/**
	 * @brief This function pauses the execution of the threads even if jobs are available
	 * 
	 * @param pause the condition, true to pause, false to unpause
	 */
	void pause(bool pause = true);

	/**
	 * @brief This function waits until all threads have finished execution
	 * 
	 */
	void wait();

	/**
	 * @brief This function checks the available thread info 
	 * 
	 * @return true if at least one thread is busy
	 * @return false if no threads are busy
	 */
	bool is_done();
	bool is_busy();

	// Display the total possible threads for the system
	/**
	 * @brief Get the total number of threads possible on the current device
	 * 
	 * @return uint32_t return number of possible threads
	 */
	uint32_t get_possible_threads();

	// Thread Information
	/**
	 * @brief Get the total tasks executed per thread as a vector
	 * 
	 * @return std::vector<unsigned long long> is a vector of completed thread tasks
	 */
	std::vector<unsigned long long> get_thread_total_tasks_executed();
	
	/**
	 * @brief Get the total uptime for each thread as a vactor
	 * 
	 * @return std::vector<unsigned long long>  is a vector of uptimes per thread
	 */
	std::vector<unsigned long long> get_thread_total_uptime();

	/**
	 * @brief Get the total tasks executed by the threadpool
	 * 
	 * @return uint64_t a number indicating the total number of functions executed
	 */
	uint64_t get_total_tasks_executed();
	
	/**
	 * @brief Get the total uptime of the longest running thread
	 * 
	 * @return uint64_t a number indicating uptime in milliseconds
	 */
	uint64_t get_total_uptime();

	/**
	 * @brief creates a string of statistics to display the information per thread
	 * 
	 * @return std::string the string to display
	 */
	std::string statistics();

private:
	// Delete certain functions
	Poole(const Poole*) = delete;
	Poole(const Poole&&) = delete;

	// Initialise the threads and the exit condition
	/**
	 * @brief setup all the member variables correctly.
	 */
	void init();

	/**
	 * @brief This the infinite loop that looks for jobs to execute per thread
	 * 
	 * @param thread_id is the id of the thread running the function
	 */
	void zombie_loop(uint32_t thread_id=0);

	/**
	 * @brief This function is used to stop the thread pool dead in its tracks
	 * 
	 */
	void force_stop();

	// Getters
	void stop_processing(bool con = false);
	
	// Setters
	void set_possible_threads(uint32_t possible_threads);

	// Member Variables
	std::vector<std::thread> m_threads;
	std::vector<ThreadInfo> m_thread_info;
	std::queue<std::function<void()>> m_function_queue;
	std::recursive_mutex m_queue_mutex;							// Slightly slower than std::recursive_mutex
	std::condition_variable_any m_threadpool_notifier;
	std::condition_variable_any m_wait_execution_notifier;
	uint32_t m_total_possible_threads;
	bool m_stop_processing;		
	bool m_emergency_stop;
	bool m_paused;
};


// Stats: 
// simple is_prime function with std::recursive_mutex run 100 times on numbers 1-1000
// average execution time: 
//			run 1: 			091.35 ms
//			run 2:			146.01 ms
//			run 3:			126.60 ms
//			run 4:			095.98 ms
//			run 5:			162.16 ms
//
// simple is_prime function with std::recursive_mutex run 100 times on nubmers 1-1000
// average execution time:
//			run 1:			087.85 ms
//			run 2:			198.72 ms
//			run 3:			228.73 ms
//			run 4:			155.20 ms
//			run 5:			113.52 ms
//
// Conclustion: While std::recursive_mutex is overall faster when it is, but, more often
// 				than not, it will have a greater degree of variability during
//				its execution. As such, I'll be using std::recursive_mutex
