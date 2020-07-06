
#pragma once

#include <functional>
#include <map>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#include <iostream>

class ThreadInfo {
	public:
	int id() {return m_id;}
	int busy_status(){return m_busy;};
	int completed_status(){return m_completed;}

	void set_id(int value) {m_id = value;}
	void set_busy_status(int value) {m_busy = value;}
	void set_completed_status(int value) {m_completed = value;}

	private:
	int m_id = -1;
	int m_busy = false;
	int m_completed = false;
};

class Poole  
{
	public:
		// Ctor and Dtor
		Poole();
		~Poole();
	
		// Getter
		int get_possible_threads();

		// Add a function
		int add_function(std::function<void()>);

		// shutdown the threads if not already turned off
		void stop_pool();					// Closes the threads

		
	private:
		// Get the total number of threads
		int m_possible_threads;

		// A queue of functions and threads
		std::queue<std::function<void()>> m_function_pool;
		std::map<int, std::thread> m_thread_pool;
		std::map<int, ThreadInfo> m_thread_info_pool;

		// Whether the threads have been destroyed once before
		bool m_shutdown_status;
		bool m_is_stopped;

		// Private Member Functions
		void init();									//Set up the class information

		void event_function_loop(int id);				// An infinite loop executing the functions
		ThreadInfo& find(int id);						// Obtain a threadinfo based on ID

		void shutdown();								// Stops the execution of the threads
		void set_pool_shutdown_status(bool value);		// Set's the shutdown condition
		bool get_pool_shutdown_status();				// Get the shutdown status
		std::mutex m_queue_mutex;
		std::condition_variable m_cond_var;
};