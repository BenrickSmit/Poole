# Poole
Poole is a simple threadpool project designed to make concurrency rather easy with the use of lambdas and (in future) template and static functions. It should help in many different scenarios including, but not limited to, graphics, and scientific data.

# Description
Poole was made with simplicity in mind. It should provide a lot of information about the jobs it performed, while still being relatively easy to use and without fuss, which is why I settled on using C++ lambdas.
Simply create the <code>Poole</code> object and start adding jobs to it. The automatic build process also creates static and shared libraries for use in other projects should you prefer to use these libraries.

<code>init_documentation.sh</code> is used to create the documentation automatically
<code>run_all.sh</code> is used to run all tests and program execution, as well as to create the necessary documentation
<code>run_application.sh</code> is used to run only the application
<code>run_tests.sh</code> is used to run only the tests

<code>build_info</code> contains the build_name, build_version, and build_cxx_standard text files.
<code>build_name</code> contains the project name. <code>build_version</code> contains the project version number. <code>build_cxx_standard</code> contains
the CXX standard used, in this case C++17.

Find the project [here](https://github.com/BenrickSmit/Poole), if you did not find this project on my github.

# Features
In the present state (version 0.1.6) Poole contains the following functionality:
    -   The ability to change the number of threads created
    -   The ability to execute any function as long as its passed through a lambda
    -   The ability to determine whether any threads are still busy executing
    -   The ability to determine whether all threads are finished with their jobs
    -   The ability to obtain the max number of threads recommended on the hardware
    -   The ability to pause the execution of the threadpool
    -   The ability to wait for the completion of all the tasks in the threadpool
        before continuing with normal program execution
    -   The ability to tally the total number of jobs performed by each thread
    -   The ability to tally the total number of jobs performed by all threads
    -   The ability to see the uptime of each thread
    -   The ability to see the total uptime of the threads
    -   The ability to obtain a string with some threadpool statistics
    -   Optimized internal locking mechanism using `std::mutex` for improved performance.
    -   Uses Google Test 1.17.0 for comprehensive unit testing.

# Future Changes
In the near future I wish to implement some static functions that can simplify the process of using the threadpool - if possible. Additionally, I wish to add some template functions for adding functions that return values, once compiler compatibility is fully addressed.

# How to Use in Code
As stated previously, Poole is based on simplicity. Any function can be wrapped in a lambda and placed in the pool.

Currently, the way to use the class is to #include "Poole.h" at the top of the file, and then to use the following snipit of code to add functions to be executed.

<code>
    Poole thread_pool = Poole(6);   // Makes a threadpool with 6 threads
    
    //... some more code here
    
    thread_pool.add_function([&](){ /* Your void task here */ });
    
    //.. some more code here

    thread_pool.wait();
</code>

Using the class as a library is a bit different in that you can either dynamically link it like you would gtest (as it is done in this project), or you can use the static library created by CMake - which you can find in the bin/ folder.

# How to Run
If you've already built the application, then simply navigate to bin/ and the resulting folders to find the test application and library. It is also possible to run the test application through the terminal via run_application.sh. This is, however OS dependent, and ideally you want to use the library in other projects

Additionally, it can be run as part of the run_all.sh script which runs all the additional scripts as well.

# How to Run Unit Tests
The project already comes with quite a few tests, most testing the functionality of the test functions and making sure the threadpool behaves as expected in most situations. This includes tests for multiple task submission, concurrency verification, and a basic performance benchmark. The tests can be run by either navigating to them in your build directory after CMake builds them, or you can use the OS-dependent script run_tests.sh.

Additionally, it can be run as part of the run_all.sh script which runs all the additional scripts as well.

# Key Dependencies
This library is dependent only on the standard library and pthread. It requires a C++17 compliant compiler and CMake 3.20 or newer to build. As such, pthread is necessary for the successful compilation of this project.

# How to contribute
Should you have any contributions, be it bugfixes, possible extensions to the codebase, or even monetary, please use the GitHub issues and pull request system for any and all communication.

[To Add Monetary Contributions]


# License
Poole is currently licensed under the [ Apache 2.0 Licence](LICENSE).

