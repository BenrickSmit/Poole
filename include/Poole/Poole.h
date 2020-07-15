// ADD LICENSE
// ADD Author etc.

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
    Poole();
    ~Poole();

	// Main interface with the program
    void add_function(std::function<void ()> function);    
	
	// Determines whether all the functions have finished executing
	bool is_busy();

	// Waits the execution of the main thread until all threads have finished computing.
	void wait();

	// Forces the shutdown of the threads if necessary
	void force_shutdown();

	// Display the total possible threads for the system
	int get_possible_threads();

private:
	// Delete certain functions
	Poole(const Poole*) = delete;
	Poole(const Poole&&) = delete;

	// Initialise the threads and the exit condition
	void init();
	// Ensure a safe ending for the threads
	void force_thread_stop();

	// The infinite loops that ensure the functions get executed
	void infinite_event_loop(int id = 0);

    // The Poole of threads and their information
    std::map<int, std::thread> m_worker_threads;
	std::map<int, ThreadInfo> m_worker_thread_info;
	//std::vector<std::thread> m_worker_threads;
 
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