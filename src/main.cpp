#include <iostream>
#include <chrono>
#include <string>

#include "include/Poole/Poole.h"

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

int main(){
	Poole thread_pool;
	std::cout << "<START MAIN>" << std::endl;
	std::cout << "Possible Threads: " << thread_pool.get_possible_threads() << std::endl;
	int i=10, j = 10;

	//Add the functions
	thread_pool.add_function(function);
	thread_pool.add_function([](){std::cout << "This was a passed LAMBDA function." << std::endl;}); 
	thread_pool.add_function([](){function1(1234);});
	thread_pool.add_function([](){function2("Saluton Mondo!");});
	thread_pool.add_function([i,j](){function3(i, j);});

	std::cout << std::endl;
	//std::cout << "TOTAL SUMMATION: " << summation() << std::endl;

	thread_pool.stop_pool();
	std::cout << "<FINISH MAIN>" << std::endl;
	return 0;
}