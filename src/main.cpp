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
 * @modified: 2 December 2020
 * 
 * @brief: This is the main class which gives some function examples and how to 
 * use them with the Poole class to allow for concurrency.
 * 
 */ 

#include <iostream>
#include <chrono>
#include <string>
#include <cmath>
#include <ctime>
#include <random>
#include <list>
#include <set>

#include "Poole.h"
#include "test_functions.h"


int main(){
	std::cout << "<STARTING EXECUTION>" << std::endl;
	int32_t threads_wanted1 = 1;
	int32_t threads_wanted2 = -1;
	const int32_t TOTAL_NUMBERS = 100000;
	
	std::list<uint64_t> prime_list;
	std::list<uint64_t> prime_brute_list;
	/*
	int number = 65;

	// List of possible ways of executing functions in the thread_pool
	// note, it is necessary to use lambdas for all functions that are non-void
	// for the moment
	thread_pool.add_function([](){function();});
	thread_pool.add_function([](){function1(777);});
	thread_pool.add_function([](){function2("INPUT");});
	thread_pool.add_function([](){function3(40,40);});
	thread_pool.add_function([](){summation_value = summation(); std::cout << ">> SUMMATION: " << summation() << std::endl;});
	thread_pool.add_function([number](){factorial_value = factorial(number); std::cout << ">> FACTORIAL("<<number<<"): " << factorial(number) << std::endl;});
	thread_pool.add_function([number](){fibonacci_value = fibonacci(number); std::cout << ">> FIBONACCI("<<number<<"): " << fibonacci_value << std::endl;});
	thread_pool.add_function([](){std::cout << ">> SORTING RANDOMS" << std::endl; sorting();});
*/

	// Execution of the 1st 100000 prime numbers with one thread
	Poole thread_pool1{threads_wanted1};
	std::cout << "\nTotal Threads Asked For thread_pool1: " << threads_wanted1 << std::endl;
	std::cout << "Total Threads Created   thread_pool1: " << thread_pool1.get_possible_threads() << std::endl;
	std::cout << std::endl;
	std::cout << "thread_pool1 Statistics:" << std::endl;
	std::cout << "========================" << std::endl;
	for(auto i = 0; i < TOTAL_NUMBERS; i++){
		thread_pool1.add_function([i, prime_brute_list]() mutable {
			is_prime_brute_force(i, prime_brute_list);
		});
	}
	thread_pool1.wait();
	std::cout << thread_pool1.statistics() << std::endl;

	// Execution of the 1st 100000 prime numbers with as many as possible threads
	Poole thread_pool2{threads_wanted2};
	std::cout << "Total Threads Asked For thread_pool2: " << threads_wanted2 << std::endl;
	std::cout << "Total Threads Created   thread_pool2: " << thread_pool2.get_possible_threads() << std::endl;
	std::cout << std::endl;
	std::cout << "thread_pool2 Statistics:" << std::endl;
	std::cout << "========================" << std::endl;
	for(auto i = 0; i < TOTAL_NUMBERS; i++){
		thread_pool2.add_function([i, prime_brute_list]() mutable {
			is_prime_brute_force(i, prime_brute_list);
		});
	}
	thread_pool2.wait();
	std::cout << thread_pool2.statistics() << std::endl;

	
	

	std::cout << "<FINISHED EXECUTION>" << std::endl;
	return 0;
}