#include <thread>

#include "gtest/gtest.h"
#include "Poole.h"


//POOLE 
TEST(TEST_POOLE_SUITE, Init_ZeroIntThreadsInput_PASS) {
    Poole thread_pool{0};

    EXPECT_EQ(std::thread::hardware_concurrency(), thread_pool.get_possible_threads());
}

TEST(TEST_POOLE_SUITE, Init_OneIntThreadInput_PASS) {
    Poole thread_pool{1};

    EXPECT_EQ(1, thread_pool.get_possible_threads());
}

TEST(TEST_POOLE_SUITE, Init_ThousandIntThreadInput_PASS) {
    Poole thread_pool{1000};

    EXPECT_EQ(std::thread::hardware_concurrency(), thread_pool.get_possible_threads());
}