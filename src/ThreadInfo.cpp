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
 * @brief: This contains the implementations of the ThreadInfo class
 *
 */

#include "ThreadInfo.h"  

#include <cstdint>

//Constructor
ThreadInfo::ThreadInfo(){
    // This function really doesn't have to do much
    set_busy(false);
    set_ID(0);
    set_uptime();
    set_tasks(0);
}

// Getters
bool ThreadInfo::is_busy() const {
    return m_thread_is_busy;
}

uint32_t ThreadInfo::get_ID() const {
    return m_thread_ID;
}

bool ThreadInfo::is_done() const {
    return m_thread_is_done;
}

uint32_t ThreadInfo::get_uptime() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - 
            get_start_time()).count();
}

uint64_t ThreadInfo::get_tasks() const {
    return m_total_tasks;
}


// Setters
void ThreadInfo::set_busy(bool con) {
    // m_thread_is_done and m_thread_is_finished are mutually exclusive. Setting one, also sets the
    // other.
    m_thread_is_busy = con;
    m_thread_is_done = !con;
}

void ThreadInfo::set_done(bool con) {
    // m_thread_is_done and m_thread_is_finished are mutually exclusive. Setting one, also sets the
    // other.
    m_thread_is_done = con;
    m_thread_is_busy = !con;
}

void ThreadInfo::set_ID(uint16_t id) {
    // This is supposed to contain a number as the thread ID to be used in other areas of the Poole
    m_thread_ID = id;
}

void ThreadInfo::add_task(uint32_t total_tasks_to_add) {
    // This function only increments the total number of tasks based on the number, nothing else
    #if defined(__GNUC__) || defined(__clang__)
    const uint64_t MAX_NUMBER = __UINT32_MAX__;
#else
    const uint64_t MAX_NUMBER = UINT32_MAX;
#endif

    // Check for overflow
    if((total_tasks_to_add + get_tasks()) == 0){
        set_tasks(MAX_NUMBER);
    }else{
        set_tasks(get_tasks() + total_tasks_to_add);
    }
}

std::string ThreadInfo::to_string() {
    // This function converts all the internal data into a string format
    std::string to_return = "";

    to_return = "Thread ";
    if(get_ID() < 100){
        to_return += "00";
    }
    to_return += std::to_string(get_ID());
    to_return += ": " + std::to_string(get_tasks()) + " tasks";
    to_return += "; " + std::to_string(get_uptime()) + " ms";

    return to_return;
}

std::chrono::system_clock::time_point ThreadInfo::get_start_time() const {
    return m_start_time_ms;
}

void ThreadInfo::set_uptime() {
    m_start_time_ms = std::chrono::system_clock::now();
}

void ThreadInfo::set_tasks(uint32_t total_tasks) {
    m_total_tasks = total_tasks;
}
