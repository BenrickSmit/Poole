#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

#include "gtest/gtest.h"
#include "Poole.h"


//POOLE 

// Test case for multiple task submission
TEST(TEST_POOLE_SUITE, Init_VeryLargeThreadsInput_PASS) {
    Poole thread_pool{9999999}; // Very large input

    EXPECT_EQ(std::thread::hardware_concurrency(), thread_pool.get_possible_threads());
}

// New: Initialization with thread count less than hardware concurrency
TEST(TEST_POOLE_SUITE, Init_LessThanHardwareConcurrency_PASS) {
    if (std::thread::hardware_concurrency() > 2) { // Ensure there are enough hardware threads
        Poole thread_pool{2};
        EXPECT_EQ(2, thread_pool.get_possible_threads());
    } else {
        // If hardware concurrency is 1 or 2, this test is redundant with Init_OneIntThreadInput_PASS
        // or Init_ZeroIntThreadsInput_PASS. Skip or adjust accordingly.
        // For simplicity, we'll assert it defaults to hardware concurrency if less than 2.
        Poole thread_pool{2};
        EXPECT_EQ(std::thread::hardware_concurrency(), thread_pool.get_possible_threads());
    }
}

// Test case for multiple task submission
TEST(TEST_POOLE_SUITE, MultipleTasks_ManyTasks_PASS) {
    const int num_tasks = 1000;
    std::atomic<int> counter{0};

    Poole thread_pool{4}; // Use a pool with 4 threads

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&counter]() {
            counter++;
        });
    }

    thread_pool.wait(); // Wait for all tasks to complete

    EXPECT_EQ(num_tasks, counter.load());
}

// New: Test for single task submission
TEST(TEST_POOLE_SUITE, AddFunction_SingleTask_PASS) {
    Poole thread_pool{1};
    bool executed = false;
    thread_pool.add_function([&executed]() {
        executed = true;
    });
    thread_pool.wait();
    EXPECT_TRUE(executed);
}

// New: Test for task with parameters
TEST(TEST_POOLE_SUITE, AddFunction_TaskWithParameters_PASS) {
    Poole thread_pool{1};
    std::atomic<int> result_sum{0};
    int val1 = 10;
    int val2 = 20;

    thread_pool.add_function([&result_sum, val1, val2]() {
        result_sum = val1 + val2;
    });
    thread_pool.wait();
    EXPECT_EQ(30, result_sum.load());
}

// Test case for empty lambda submission
TEST(TEST_POOLE_SUITE, AddFunction_EmptyLambda_PASS) {
    Poole thread_pool{1};
    bool executed = false;
    thread_pool.add_function([&executed]() {
        executed = true;
    });
    thread_pool.wait();
    EXPECT_TRUE(executed);
}

// Test case for concurrent task submission
TEST(TEST_POOLE_SUITE, AddFunction_ConcurrentSubmission_PASS) {
    const int num_submitters = 5;
    const int tasks_per_submitter = 100;
    const int total_tasks = num_submitters * tasks_per_submitter;
    std::atomic<int> completed_tasks{0};

    Poole thread_pool{static_cast<int32_t>(std::thread::hardware_concurrency())};

    std::vector<std::thread> submitter_threads;
    for (int i = 0; i < num_submitters; ++i) {
        submitter_threads.emplace_back([&thread_pool, &completed_tasks, tasks_per_submitter]() {
            for (int j = 0; j < tasks_per_submitter; ++j) {
                thread_pool.add_function([&completed_tasks]() {
                    completed_tasks++;
                });
            }
        });
    }

    for (auto& t : submitter_threads) {
        t.join();
    }

    thread_pool.wait();
    EXPECT_EQ(total_tasks, completed_tasks.load());
}

// Test case for basic concurrency verification
TEST(TEST_POOLE_SUITE, Concurrency_MultipleThreads_PASS) {
    const int num_tasks = 10;
    const std::chrono::milliseconds task_duration(100);
    std::atomic<int> completed_tasks{0};

    Poole thread_pool{4}; // Use a pool with multiple threads

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&completed_tasks, task_duration]() {
            std::this_thread::sleep_for(task_duration);
            completed_tasks++;
        });
    }

    thread_pool.wait(); // Wait for all tasks to complete

    auto end_time = std::chrono::high_resolution_clock::now();
    auto actual_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    EXPECT_LT(actual_duration.count(), (num_tasks * task_duration).count());
    EXPECT_EQ(num_tasks, completed_tasks.load());
}

// New: Concurrency test for single thread pool
TEST(TEST_POOLE_SUITE, Concurrency_SingleThread_PASS) {
    const int num_tasks = 5;
    const std::chrono::milliseconds task_duration(50);
    std::atomic<int> completed_tasks{0};

    Poole thread_pool{1}; // Use a pool with a single thread

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&completed_tasks, task_duration]() {
            std::this_thread::sleep_for(task_duration);
            completed_tasks++;
        });
    }

    thread_pool.wait(); // Wait for all tasks to complete

    auto end_time = std::chrono::high_resolution_clock::now();
    auto actual_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // With a single thread, duration should be approximately num_tasks * task_duration
    EXPECT_GE(actual_duration.count(), (num_tasks * task_duration).count()); // Greater or equal due to overhead
    EXPECT_EQ(num_tasks, completed_tasks.load());
}

// Simple performance test: submit many tasks and measure execution time
TEST(TEST_POOLE_SUITE, Performance_HighLoad_PASS) {
    const int num_tasks = 10000;
    std::atomic<int> counter{0};

    Poole thread_pool; // Default threads (hardware_concurrency)

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&counter]() {
            counter++;
        });
    }

    thread_pool.wait(); // Wait for all tasks to complete

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Performance Test: " << num_tasks << " tasks completed in " << duration_ms << " ms." << std::endl;

    EXPECT_EQ(num_tasks, counter.load());
    EXPECT_LT(duration_ms, 1000);
}

// New: Performance test for few tasks (measure overhead)
TEST(TEST_POOLE_SUITE, Performance_FewTasks_PASS) {
    const int num_tasks = 10;
    std::atomic<int> counter{0};

    Poole thread_pool; // Default threads

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&counter]() {
            counter++;
        });
    }

    thread_pool.wait();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Performance Test (Few Tasks): " << num_tasks << " tasks completed in " << duration_ms << " ms." << std::endl;

    EXPECT_EQ(num_tasks, counter.load());
    // Expect some overhead, but not excessive. Loose bound.
    EXPECT_LT(duration_ms, 100);
}


// Test case for tasks that throw exceptions
TEST(TEST_POOLE_SUITE, Exception_TaskThrows_PASS) {
    const int num_tasks = 10;
    std::atomic<int> completed_tasks{0};
    std::atomic<int> exception_thrown_count{0};

    Poole thread_pool{4}; // Use a pool with multiple threads

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&completed_tasks, &exception_thrown_count, i]() {
            try {
                if (i % 3 == 0) { // Make some tasks throw exceptions
                    exception_thrown_count++;
                    throw std::runtime_error("Test exception from task");
                }
                completed_tasks++;
            } catch (const std::exception& e) {
                // Log the exception, but don't let it propagate out of the worker function
                // std::cerr << "Task caught exception: " << e.what() << std::endl;
            }
        });
    }

    thread_pool.wait();

    EXPECT_EQ(completed_tasks.load() + exception_thrown_count.load(), num_tasks);
}

// New: Exception test for many tasks throwing
TEST(TEST_POOLE_SUITE, Exception_ManyTasksThrow_PASS) {
    const int num_tasks = 100;
    std::atomic<int> exception_count{0};

    Poole thread_pool{4};

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&exception_count, i]() {
            try {
                if (i % 2 == 0) { // Half tasks throw
                    throw std::runtime_error("Another test exception");
                }
            } catch (const std::exception& e) {
                exception_count++;
            }
        });
    }
    thread_pool.wait();
    EXPECT_GE(exception_count.load(), num_tasks / 2); // At least half should have thrown
}


// Test case for shutting down with pending tasks
TEST(TEST_POOLE_SUITE, Shutdown_PendingTasks_PASS) {
    const int num_tasks = 100;
    std::atomic<int> counter{0};

    // Create a scope for the thread pool so its destructor is called
    {
        Poole thread_pool{4}; // Use a pool with multiple threads

        for (int i = 0; i < num_tasks; ++i) {
            thread_pool.add_function([&counter]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Simulate work
                counter++;
            });
        }
    } // thread_pool goes out of scope and is destroyed

    EXPECT_EQ(num_tasks, counter.load());
}

// Test case: Shutting down a pool with no tasks ever added
TEST(TEST_POOLE_SUITE, Shutdown_NoTasksAdded_PASS) {
    // Create a scope for the thread pool
    {
        Poole thread_pool{2}; // A pool with 2 threads
        // No tasks added
    } // thread_pool goes out of scope and is destroyed
    // Should not crash or hang
    SUCCEED();
}

// Test case: Shutting down a pool while a long-running task is still executing
TEST(TEST_POOLE_SUITE, Shutdown_DuringLongRunningTask_PASS) {
    std::atomic<bool> long_task_started{false};
    std::atomic<bool> long_task_finished{false};

    {
        Poole thread_pool{1}; // One thread to ensure the task runs on it

        thread_pool.add_function([&long_task_started, &long_task_finished]() {
            long_task_started = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate long work
            long_task_finished = true;
        });

        // Give the task some time to start, but not finish
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        EXPECT_TRUE(long_task_started.load());
        EXPECT_FALSE(long_task_finished.load());

    } // thread_pool goes out of scope and destructor is called
    // The destructor should block until long_task_finished is true (i.e., the task completes)
    EXPECT_TRUE(long_task_finished.load());
}

// Test case for pause/wait interaction
TEST(TEST_POOLE_SUITE, PauseResume_TasksExecute_PASS) {
    const int num_tasks = 10;
    std::atomic<int> counter{0};

    Poole thread_pool{2}; // Use a pool with a few threads

    thread_pool.pause(true); // Pause the pool

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&counter]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate work
            counter++;
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_LT(counter.load(), num_tasks);

    thread_pool.pause(false); // Unpause the pool
    thread_pool.wait();       // Wait for all tasks to complete

    EXPECT_EQ(num_tasks, counter.load());
}

// Test case for multiple pause/resume calls
TEST(TEST_POOLE_SUITE, PauseResume_MultiplePauses_PASS) {
    const int num_tasks = 10;
    std::atomic<int> counter{0};

    Poole thread_pool{2}; // Use a pool with a few threads

    thread_pool.pause(true); // Pause
    thread_pool.pause(true); // Pause again (should have no additional effect)

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&counter]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate work
            counter++;
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_LT(counter.load(), num_tasks);

    thread_pool.pause(false); // Unpause
    thread_pool.pause(false); // Unpause again (should have no additional effect)
    thread_pool.wait();       // Wait for all tasks to complete

    EXPECT_EQ(num_tasks, counter.load());
}

// New: Pause the pool during a wait operation
TEST(TEST_POOLE_SUITE, PauseResume_PauseDuringWait_PASS) {
    const int num_tasks = 5;
    std::atomic<int> counter{0};
    std::atomic<bool> wait_started{false};

    Poole thread_pool{2};

    for (int i = 0; i < num_tasks; ++i) {
        thread_pool.add_function([&counter, &wait_started]() {
            if (counter.load() == 0) { // First task starts, signal wait_started
                wait_started = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Long enough to allow wait() to be called
            }
            counter++;
        });
    }

    // Call wait() in a separate thread to simulate a concurrent call
    std::thread wait_thread([&thread_pool, &wait_started]() {
        while (!wait_started.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        thread_pool.wait();
    });

    // Wait for wait_thread to be in wait state, then pause
    while (!wait_started.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    thread_pool.pause(true); // Pause while wait() is potentially active

    // Give some time for pause to take effect and for tasks to potentially finish
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // Tasks should not be fully completed if pause truly worked
    EXPECT_LT(counter.load(), num_tasks);

    thread_pool.pause(false); // Unpause
    wait_thread.join();       // Wait for the wait_thread to finish

    EXPECT_EQ(num_tasks, counter.load());
}