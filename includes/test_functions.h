#pragma once

#include <list>
#include <set>
#include <vector>
#include <stdint.h>
#include <string>
#include <cmath>

/**
 * @brief a function that creates the sum value of each number up to the specified number
 * 
 * @param to_number the upper-limit number up to which to sum
 * @return uint64_t return a long long value
 */
uint64_t summation(uint64_t to_number);

/**
 * @brief calculates the factorial up to the specified input number
 * 
 * @param input the number up to which we should calculate the factorial
 * @return uint64_t returns the factorial value
 */
uint64_t factorial(uint64_t input);

/**
 * @brief This function finds the fibonacci value at the position of the input number recursively
 * 
 * @param value the position to which we should find the fibonacci value
 * @return uint64_t the fibonacci value
 */
uint64_t fibonacci(int value);

/**
 * @brief Get the individual digits on the input number
 * 
 * @param input the number which digits we want
 * @return std::vector<int> of digits that make up the number
 */
std::vector<int> get_digits(uint64_t input);

/**
 * @brief An "elegant" method of calculating prime numbers
 * 
 * @param input the nubmer to test
 * @param prev_primes a list of previous prime values
 * @return true if input is a prime
 * @return false if input is not a prime
 */
bool is_prime(uint64_t input, std::list<uint64_t> &prev_primes);

/**
 * @brief the brute force method of determining whether a number is a prime
 * 
 * @param input_num the input number to test
 * @param prev_primes the input list of previous primes
 * @return true if the input_num is a prime
 * @return false if the input_num is not a prime
 */
bool is_prime_brute_force(uint64_t input_num, std::list<uint64_t> &prev_primes);