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
 * @date: 1 December 2020
 * @modified: 2 December 2020
 * 
 * @brief: This contains the implementations of the test functions used
 * 			througout the main test class.
 * 
 */

#include "test_functions.h"

uint64_t summation(uint64_t to_number){
	uint64_t total = 0;
	for (auto i = 0; i < to_number; i++){
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


uint64_t fibonacci(int value){
	if ((value==1) || (value == 0)){
		return value;
	}else {
		return static_cast<long long>(fibonacci(value-1) + fibonacci(value-2));
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
		prev_primes.emplace_back(input);
	}

	return to_return;
}


bool is_prime_brute_force(uint64_t input_num, std::list<uint64_t> &prev_primes){
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

    // Add the prime number to the list of previous prime numbers
    if (to_return) {
        prev_primes.emplace_back(input_num);
    }

	return to_return;
}
