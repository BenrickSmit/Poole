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
 * @brief: This is the main class which gives some function examples and how to use them with the Thread Pool class
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

void function(){
	std::cout << "This is a normal function with no arguments" << std::endl;
}

void function1(int i){
	std::cout << "This is a normal function with 1 arguments: " << i << std::endl;
}

void function2(std::string val){
	std::cout << "This is a normal function with 1 arguments: " << "\"" << val<< "\"" << std::endl;
}

void function3(long i, long j){
	std::cout << "This is a normal function with two arguments: " << i << ", " << j << std::endl;
}	

uint64_t summation(){
	uint64_t total = 0;
	for (auto i = 0; i < 1000; i++){
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		total += i;
	}
	return total;
}

uint64_t factorial(uint64_t input){
	if (input == 1){
		return 1;
	}else{
		return static_cast<uint64_t>(input * factorial(input-1));
	}
}

void wait_function(){
	std::this_thread::sleep_for(std::chrono::seconds(15));
}

uint64_t fibonacci(int value){
	if ((value==1) || (value == 0)){
		return value;
	}else {
		return static_cast<long long>(fibonacci(value-1) + fibonacci(value-2));
	}
}

void sorting(){
	srand(time(0));
	std::vector<uint64_t> randoms;
	for(auto i = 0; i < 10000; i++){
		randoms.push_back(rand() % 1000000);
	}

	//Sort the random numbers
	for(auto i = 0; i < randoms.size(); i++){
		for(auto j = 0; j < randoms.size(); j++){
			if(randoms.at(i) < randoms.at(j)){
				auto temp = randoms.at(j);
				randoms[j] = randoms.at(i);
				randoms[i] = temp;
			}
		}
	}
}

std::vector<int> get_digits(uint64_t input){
	// This function converts an input number into individual digits
	// and then converts this into a vector
	std::vector<int> to_return;
	std::string s_input = "";
	std::string s_digit = "";

	// Convert the input number to a string
	s_input = std::to_string(input);

	// Convert the string into individual digits which are converted to
	// digits again
	for (auto i = 0; i < s_input.size(); i++){
		s_digit = "";
		s_digit.push_back(s_input.at(i));
		to_return.push_back(std::stoll(s_digit));
	}

	return to_return;
}

bool is_prime(uint64_t input, std::list<uint64_t> &prev_primes){
	bool to_return = false;
	std::vector<int> input_num_digits = get_digits(input);
	double square = std::sqrt(input);
	// No divisible by 5, potentially a prime
	if(input % 5 != 0){
		// The ones should not be 0,2,4,6,8
		if (input_num_digits.at(input_num_digits.size()-1) % 2 != 0) {
			// Take the sum of the digits, if sum is divisible by 3, not a prime
			uint64_t sum = 0;
			for (auto i : input_num_digits){
				sum += i;
			}
			if (sum % 3 != 0) {
				// Divide the number by the primes below it's square
				for (auto prev_prime : prev_primes) {
					if (prev_prime < square) {
						if (input % prev_prime != 0) {
							to_return = true;
						} else {
							to_return = false;
							break;
						}
					}
				}
			}
		}else{
			to_return = false;
			return to_return;
		}
	}

	// Add the prime number to the list of primes automatically
	if (to_return){
		prev_primes.push_back(input);
	}

	return to_return;
}

bool is_prime_brute_force(uint64_t input_num){
	// This function only checks to see whether a value has more than 2 factors
	bool to_return = true;
	std::set<uint64_t> factors;
	factors.emplace(1);	// Primes should only have 1 and themselves as factors
	factors.emplace(input_num);

	// Determine whether the input number is 0/1. 0 is undefined, thus not a prime
	// and 1 is a prime. so no worries there
	if (input_num == 0 || input_num == 1) {
		to_return = false;
	} else {
		// a factor means that there is a clean division with a remainder of 0
		// thus use the following
		for (auto to_div_by = 1; to_div_by < input_num; to_div_by++){
			// Find the factors
			if (input_num % to_div_by == 0) {
				// found a factor
				factors.emplace(to_div_by);
			}
			// Check number of factors
			if (factors.size() > 2){
				to_return = false;
				break;
			}
		}
	}

	return to_return;
}



uint64_t summation_value = 0;
uint64_t factorial_value = 0;
uint64_t fibonacci_value = 0;


int main(){
	std::cout << "<STARTING EXECUTION>" << std::endl;
	Poole thread_pool;
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
	// scan the prime_list for true primes
	for(auto i = 0; i < 102; i++){
		//if(is_prime(i, prime_list)){
		//	prime_list.push_back(i);
		//}
		is_prime(i, prime_list);
	}
	for(auto i = 0; i < 102; i++){
		if(is_prime_brute_force(i)){
			prime_brute_list.push_back(i);
		}
	}
	
	std::cout << "Brute Forced:" << std::endl;
	std::cout << "=================" << std::endl;
	for(auto i : prime_brute_list){
		std::cout << i << std::endl;
	}
	std::cout << "" << std::endl;
	std::cout << "Elegant Method:" << std::endl; 
	std::cout << "=================" << std::endl;
	for (auto i : prime_list) {
		std::cout << i << std::endl;
	}

	std::cout << "<FINISHED EXECUTION>" << std::endl;
	return 0;
}