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
 * @modified: 29 December 2025
 *
 * @brief: This contains the header information and interface for the Poole
 * 			class which enables concurrency in C++11/14
 */

#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <vector>

#include "ThreadInfo.h"

class Poole {
 public:
  // Ctor and Dtor
  /**
   * @brief Construct a new Poole object
   */
  Poole(int32_t total_threads = -1);
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
   * @brief This function checks the available thread info to determine whether
   * 			all threads are finished executing
   *
   * @return true if at least one thread is busy
   * @return false if no threads are busy
   */
  bool is_done();

  /**
   * @brief this function checks the available thread info to determine whether
   * 			any thread is still executing
   *
   * @return true if all threads are finished
   * @return false if at least one thread is busy
   */
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
  void init(int32_t total_threads);

  /**
   * @brief This the infinite loop that looks for jobs to execute per thread
   *
   * @param thread_id is the id of the thread running the function
   */
  void zombie_loop(uint32_t thread_id = 0);

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
  std::mutex m_queue_mutex;
  std::condition_variable m_threadpool_notifier;
  std::condition_variable m_wait_execution_notifier;
  uint32_t m_total_possible_threads;
  bool m_stop_processing;
  bool m_emergency_stop;
  bool m_paused;
};
