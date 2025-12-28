
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
 * @date: 20 June 2020
 * @modified: 2 December 2020
 * 
 * @brief: This contains the interface and header information for the ThreadInfo
 * 			class responsible for storing statistics about the jobs performed
 * 			by the thread pool class Poole.
 * 
 */

#pragma once

#include <string>
#include <chrono>
#include <iostream>

/**
 * Current Functionality:
 * 	-	Thread is Busy
 *  -	Thread ID
 *  - 	Thread is Done
 *  - 	Thread Uptime
 *  -	Thread Total Tasks
 *  -	Add Completed Task
 * 
 */

class ThreadInfo{
	public:
	// Constructor
		ThreadInfo();

	// Getters
		bool is_busy();
		uint32_t get_ID();
		bool is_done();
		uint32_t get_uptime();
		uint64_t get_tasks();
		
	// Setters
		void set_busy(bool con = false);
		void set_done(bool con = false);
		void set_ID(uint16_t id);
		
	// Others
		void add_task(uint32_t total_tasks = 1);
		std::string to_string();

	protected:
	// Getters
		std::chrono::system_clock::time_point get_start_time();

	// Setters
		void set_uptime();
		void set_tasks(uint32_t total_tasks = 0);


	private:
	bool m_thread_is_busy;
	bool m_thread_is_done;
	int m_thread_ID;
	std::chrono::system_clock::time_point m_start_time_ms;
	unsigned long long m_total_tasks;
};

