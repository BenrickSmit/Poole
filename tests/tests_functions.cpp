#include <vector>
#include <list>

#include "gtest/gtest.h"
#include "test_functions.h"

// NOTE: Suites follow the class they are located in, and then the method under
// scrutiny, the state of the method, and then the expected outcome
// i.e. TEST_FUNCTIONS_SUITE, SUMMARY_NEGATIVE_NUMBER_FAIL
// which tests the test function Summary in the test functions header file
// with a negative number. We expect this function to fail, etc

// Test Google Test
TEST(TEST_SUIT_BASIC_TEST, GOOGLE_TEST_ALIVE_TEST) {
  EXPECT_EQ(1, 1);
}

// Test the Test Functions
// SUMMATION FUNCTION:
// Statement Coverage: ~ 100.0%
// Branch Coverage: ~100.0%
TEST(TEST_FUNCTIONS_SUITE, Summation_PositiveIntInput_PASS) {
  EXPECT_EQ(21, summation(6));
}

TEST(TEST_FUNCTIONS_SUITE, Summation_NegativeIntInput_PASS) {
  EXPECT_EQ(0, summation(-1));
}

TEST(TEST_FUNCTIONS_SUITE, Summation_DoubleNoDecimalInput_PASS) {
  EXPECT_EQ(21, summation(6.0));
}

// FACTORIAL FUNCTION:
// Statement Coverage: ~ 100.0%
// Branch Coverage: ~ 100.0%
TEST(TEST_FUNCTIONS_SUITE, Factorial_ZeroInput_PASS) {
  EXPECT_EQ(1, factorial(0));
}

TEST(TEST_FUNCTIONS_SUITE, Factorial_PositiveIntInput_PASS) {
  EXPECT_EQ(5040, factorial(7));
}

TEST(TEST_FUNCTIONS_SUITE, Factorial_NegativeIntInput_PASS) {
  EXPECT_EQ(-5040, factorial(-7));
}

TEST(TEST_FUNCTIONS_SUITE, Factorial_DoubleNoDecimalInput_PASS) {
  EXPECT_EQ(5040, factorial(7.0));
}

TEST(TEST_FUNCTIONS_SUITE, Factorial_NegativeDoubleNoDecimalInput_PASS) {
  EXPECT_EQ(-5040, factorial(-7.0));
}


// FIBONACCI FUNCTION
// Statement Coverage: ~ 100.0%
// Branch Coverage: ~ 100.0%
TEST(TEST_FUNCTIONS_SUITE, Fibonacci_ZeroInput_PASS) {
  EXPECT_EQ(0, fibonacci(0)); 
}

TEST(TEST_FUNCTIONS_SUITE, Fibonacci_OneInput_PASS) {
  EXPECT_EQ(1, fibonacci(1));
}

TEST(TEST_FUNCTIONS_SUITE, Fibonacci_PositiveIntInput_PASS) {
  EXPECT_EQ(5, fibonacci(5));
}


// GET_DIGITS FUNCTION
// Statement Coverage: ~ 100.0%
// Branch Coverage: ~ 100.0%
TEST(TEST_FUNCTIONS_SUITE, get_digits_BetweenZeroAndTenInput_PASS) {
  std::vector<int> result;
  result.push_back(7);

  EXPECT_EQ(result, get_digits(7));
}

TEST(TEST_FUNCTIONS_SUITE, get_digits_BetweenTenAndHundredInput_PASS) {
  std::vector<int> result;
  result.push_back(6);
  result.push_back(9);

  EXPECT_EQ(result, get_digits(69));
}


// IS_PRIME FUNCTION
// Statement Coverage: ~ 100.0%
// Branch Coverage: ~ 100.0%
TEST(TEST_FUNCTIONS_SUITE, is_prime_ZeroInputReturnTest_PASS) {
  std::list<uint64_t> prev_primes;
  EXPECT_EQ(false, is_prime(0, prev_primes));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_ZeroInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  std::list<uint64_t> test_result;
  is_prime(0, test_result);

  EXPECT_EQ(correct_result, test_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_OneInputReturnTest_PASS) {
  std::list<uint64_t> prev_primes;
  EXPECT_EQ(false, is_prime(1, prev_primes));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_OneInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  std::list<uint64_t> test_result;
  is_prime(1, test_result);

  EXPECT_EQ(correct_result, test_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_TwoInputReturnTest_PASS) {
  std::list<uint64_t> prev_primes;
  EXPECT_EQ(true, is_prime(2, prev_primes));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_TwoInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  std::list<uint64_t> test_result;
  correct_result.push_back(2);

  is_prime(2, test_result);

  EXPECT_EQ(correct_result, test_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_FourInputReturnTest_PASS) {
  std::list<uint64_t> prev_primes;
  prev_primes.push_back(2);
  prev_primes.push_back(3);
  EXPECT_EQ(false, is_prime(4, prev_primes));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_FourInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);
  

  is_prime(4, test_result);

  EXPECT_EQ(correct_result, test_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_TenInputReturnTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  correct_result.push_back(5);
  correct_result.push_back(7);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);
  test_result.push_back(5);
  test_result.push_back(7);

  EXPECT_EQ(false, is_prime(10, test_result));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_TenInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  correct_result.push_back(5);
  correct_result.push_back(7);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);
  test_result.push_back(5);
  test_result.push_back(7);

  is_prime(10, test_result);

  EXPECT_EQ(correct_result, test_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_ElevenInputReturnTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  correct_result.push_back(5);
  correct_result.push_back(7);
  correct_result.push_back(11);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);
  test_result.push_back(5);
  test_result.push_back(7);

  is_prime(11, test_result);

  EXPECT_EQ(true, is_prime(11, test_result));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_ElevenInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  correct_result.push_back(5);
  correct_result.push_back(7);
  correct_result.push_back(11);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);
  test_result.push_back(5);
  test_result.push_back(7);

  is_prime(11, test_result);

  EXPECT_EQ(correct_result, test_result);
}


// IS_PRIME_BRUTE_FORCE
// Statement Coverage: ~ 0.0%
// Branch Coverage: ~ 0.0%
TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_ZeroInputResultTest_PASS) {
  std::list<uint64_t> correct_result;
  std::list<uint64_t> test_result;
  
  EXPECT_EQ(false, is_prime_brute_force(0, test_result));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_ZeroInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  std::list<uint64_t> test_result;

  is_prime_brute_force(0, correct_result);

  EXPECT_EQ(test_result, correct_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_OneInputResultTest_PASS) {
  std::list<uint64_t> correct_result;
  std::list<uint64_t> test_result;
  
  EXPECT_EQ(false, is_prime_brute_force(1, test_result));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_OneInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  std::list<uint64_t> test_result;

  is_prime_brute_force(1, test_result);

  EXPECT_EQ(test_result, correct_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_TwoInputResultTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  std::list<uint64_t> test_result;
  
  EXPECT_EQ(true, is_prime_brute_force(2, test_result));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_TwoInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  std::list<uint64_t> test_result;

  is_prime_brute_force(2, test_result);

  EXPECT_EQ(test_result, correct_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_ThreeInputResultTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  std::list<uint64_t> test_result;
  
  EXPECT_EQ(true, is_prime_brute_force(3, test_result));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_ThreeInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  std::list<uint64_t> test_result;
  test_result.push_back(2);

  is_prime_brute_force(3, test_result);

  EXPECT_EQ(test_result, correct_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_FourInputResultTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);

  EXPECT_EQ(false, is_prime_brute_force(4, test_result));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_FourInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);

  is_prime_brute_force(4, test_result);

  EXPECT_EQ(test_result, correct_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_TenInputResultTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  correct_result.push_back(5);
  correct_result.push_back(7);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);
  test_result.push_back(5);
  test_result.push_back(7);

  EXPECT_EQ(false, is_prime_brute_force(10, test_result));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_TenInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  correct_result.push_back(5);
  correct_result.push_back(7);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);
  test_result.push_back(5);
  test_result.push_back(7);

  is_prime_brute_force(10, test_result);

  EXPECT_EQ(test_result, correct_result);
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_ElevenInputResultTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  correct_result.push_back(5);
  correct_result.push_back(7);
  correct_result.push_back(11);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);
  test_result.push_back(5);
  test_result.push_back(7);

  EXPECT_EQ(true, is_prime_brute_force(11, test_result));
}

TEST(TEST_FUNCTIONS_SUITE, is_prime_brute_force_ElevenInputReferenceTest_PASS) {
  std::list<uint64_t> correct_result;
  correct_result.push_back(2);
  correct_result.push_back(3);
  correct_result.push_back(5);
  correct_result.push_back(7);
  correct_result.push_back(11);
  std::list<uint64_t> test_result;
  test_result.push_back(2);
  test_result.push_back(3);
  test_result.push_back(5);
  test_result.push_back(7);

  is_prime_brute_force(11, test_result);

  EXPECT_EQ(test_result, correct_result);
}