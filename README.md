# Poole
Poole is a simple threadpool project designed to make concurrency rather easy with the use of lambdas and (in future) template and static functions. It should help in many different scenarios including, but not limited to, graphics, and scientific data.

# Description
Poole was made with simplicity in mind. It should provide a lot of information about the jobs it performed, while still being relatively easy to use and without fuss, which is why I settled on using C++ lambdas and templates (coming in the near future). 
Simply create the <code>Poole</code> object and start adding jobs to it. Later versions will also support static implementations of these functions. The automatic build process also creates static libraries for use in other projects should you prefer to use these libraries.

<code>init_documentation.sh</code> is used to create the documentation automatically
<code>run_all.sh</code> is used to run all tests and program execution, as well as to create the necessary documentation
<code>run_application.sh</code> is used to run only the application
<code>run_tests.sh</code> is used to run only the tests

<code>build_info</code> contains the build_name, build_version, and build_cxx_standard text files.
<code>build_name</code> contains the project name. <code>build_version</code> contains the project version number. <code>build_cxx_standard</code> contains
the CXX standard used, in this case C++17.

Find the project [here](https://github.com/BenrickSmit/Poole), if you did not find this project on my github.

# Features
In the present state (version 0.1.5) Poole contains the following functionality:
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

# Future Changes
In the near future I wish to implement some static functions that can simplify the process of using the threadpool - if possible. Additionally, I wish to add some template functions for adding functions without the use of lambdas.

# How to Use in Code
As stated previously, Poole is based on simplicity. Any function can be wrapped in a lambda and placed in the pool. This is also the case for functions that return values.

As an example. should you have a function that returns a value, it would be possible to access it outside of the lambda by doing the following:

<code>
    int value = 0;
    int to_sum_to = 1000;
    [this, value](){ value = summation(to_sum_to);}
</code>

The above will still ensure that even if the function is inside a lambda, you can still receive some data from them.

Currently, one of the only ways to use the class is to #include "Poole.h" at the top of the file, and then to use the following snipit of code to add functions to be executed.

<code>
    Poole thread_pool = Poole(6);   // Makes a threadpool with 6 threads
    
    //... some more code here
    
    thread_pool.add_function([this, result, input](){result = fibonacci(input);});
    
    //.. some more code here

    thread_pool.wait();
</code>

Using the class as a library is a bit different in that you can either dynamically link it like you would gtest (as it is done in this project), or you can use the static library created by CMake - which you can find in the bin/ folder.

# How to Run
If you've already built the application, then simply navigate to bin/ and the resulting folders to find the test application and library. It is also possible to run the test application through the terminal via run_application.sh. This is, however OS dependent, and ideally you want to use the library in other projects

Additionally, it can be run as part of the run_all.sh script which runs all the additional scripts as well.

# How to Run Unit Tests
The project already comes with quite a few tests, most testing the funcationality of the test functions and making sure the threadpool behaves as expected in most situations. The tests can be run by either navigating to them in your build directory after CMake builds them, or you can use the OS-dependent script run_tests.sh.

Additionally, it can be run as part of the run_all.sh script which runs all the additional scripts as well.

# Key Dependencies
This library is dependent only on the standard library and pthread. As such, pthread is necessary for the successful compilation of this project.

# How to contribute
Should you have any contributions, be it bugfixes, possible extensions to the codebase, or even monetary, please reach out to me for this at metatronicprogramming@hotmail.com for any and all communication.

[To Add Monetary Contributions]


# License
Poole is currently licensed under the [ Apache 2.0 Licence](LICENSE).

