
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

