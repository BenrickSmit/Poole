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

long summation(){
	long total = 0;
	for (auto i = 0; i < 1000; i++){
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		total += i;
	}
	return total;
}

long long factorial(int input){
	if (input == 1){
		return 1;
	}else{
		return static_cast<long long>(input * factorial(input-1));
	}
}

void wait_function(){
	std::this_thread::sleep_for(std::chrono::seconds(15));
}

long long fibonacci(int value){
	if ((value==1) || (value == 0)){
		return value;
	}else {
		return static_cast<long long>(fibonacci(value-1) + fibonacci(value-2));
	}
}

void sorting(){
	srand(time(0));
	std::vector<int> randoms;
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


long summation_value = 0;
long long factorial_value = 0;
long long fibonacci_value = 0;


int main(){
	Poole thread_pool;
	
	int number = 40;

	thread_pool.add_function([](){function();});
	thread_pool.add_function([](){function1(777);});
	thread_pool.add_function([](){function2("INPUT");});
	thread_pool.add_function([](){function3(40,40);});
	thread_pool.add_function([](){summation_value = summation(); std::cout << ">> SUMMATION: " << summation() << std::endl;});
	thread_pool.add_function([number](){factorial_value = factorial(number); std::cout << ">> FACTORIAL("<<number<<"): " << factorial(number) << std::endl;});
	thread_pool.add_function([number](){fibonacci_value = fibonacci(number); std::cout << ">> FIBONACCI("<<number<<"): " << fibonacci_value << std::endl;});
	thread_pool.add_function([](){std::cout << ">> SORTING RANDOMS" << std::endl; sorting();});

	thread_pool.wait();
	thread_pool.force_shutdown();

	std::cout << "Summation Result: " << summation_value << std::endl;
	std::cout << "Factorial Result: " << factorial_value << std::endl;
	std::cout << "Fibonacci Result: " << fibonacci_value << std::endl;

	return 0;
}