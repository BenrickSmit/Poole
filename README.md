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
    -   Optimized internal locking mechanism using `std::mutex` for improved performance and corrected synchronization logic.
    -   Uses Google Test 1.17.0 for a comprehensive unit testing suite, covering various initialization edge cases, concurrent task submission, shutdown scenarios, exception handling, and pause/resume behavior.
    -   Robust handling of tasks that throw exceptions, ensuring the thread pool does not crash.
    -   Graceful shutdown mechanism, even with pending or long-running tasks.

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
The project already comes with a comprehensive suite of tests that verify the functionality and expected behavior of the thread pool in various scenarios. This includes:
    -   **Initialization Tests**: Covering valid, zero, negative, and excessively large thread counts.
    -   **Task Submission Tests**: Verifying single, multiple, and concurrently submitted tasks, including empty lambdas and tasks with parameters.
    -   **Concurrency Tests**: Ensuring tasks execute in parallel and comparing performance against sequential execution.
    -   **Performance Benchmarks**: Basic tests to measure execution efficiency under high and low loads.
    -   **Exception Handling Tests**: Confirming the thread pool's robustness when tasks throw exceptions.
    -   **Shutdown Tests**: Verifying graceful termination with pending, running, or no tasks.
    -   **Pause/Resume Tests**: Checking correct behavior for pausing, unpausing, and interactions with `wait()`.

The tests can be run by either navigating to them in your build directory after CMake builds them, or you can use the OS-dependent script run_tests.sh.

Additionally, it can be run as part of the run_all.sh script which runs all the additional scripts as well.

# Key Dependencies
This library is dependent only on the standard library and pthread. It requires a C++17 compliant compiler and CMake 3.20 or newer to build. As such, pthread is necessary for the successful compilation of this project.

# Integrating Poole with CMake Projects
Poole is designed to be easily integrated into other CMake-based projects. There are two primary methods for consumption:

## 1. Using `find_package` (Recommended for deployed/installed libraries)
This is the standard approach for consuming a library that has been built and installed.

**Steps:**
1.  **Build and Install Poole:** First, build and install the Poole library to a known location.
    ```bash
    mkdir build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=<install_path> # e.g., ../_install
    cmake --build . --config Release # or Debug
    cmake --install . --config Release # or Debug
    ```
2.  **Configure Your External Project:** In your external project's `CMakeLists.txt`, use `find_package`. Ensure CMake can locate Poole's installed configuration files (`PooleConfig.cmake`).
    ```cmake
    cmake_minimum_required(VERSION 3.20) # Match Poole's minimum or higher
    project(YourExternalProject LANGUAGES CXX)

    # Option A: Set CMAKE_PREFIX_PATH environment variable before configuring CMake
    # e.g., In your shell: export CMAKE_PREFIX_PATH="/path/to/Poole/_install"
    # Then run cmake as usual.

    # Option B: Pass PATHS to find_package (less common for widely distributed libraries)
    # find_package(Poole CONFIG REQUIRED PATHS /path/to/Poole/_install)

    # Assuming CMAKE_PREFIX_PATH is set or Poole is in a system path
    find_package(Poole CONFIG REQUIRED)

    add_executable(YourApplication main.cpp)
    target_link_libraries(YourApplication PRIVATE Poole::Poole_lib)
    ```
    This method automatically handles finding include directories, library paths, and links for both static and shared library builds based on how Poole was built.

## 2. Using `add_subdirectory` (for tighter coupling or development with `FetchContent`)
If you want to integrate Poole directly from its source code (e.g., from a Git submodule or fetched via `FetchContent`), you need to add the *root directory of the `Poole` project*.

### Direct `add_subdirectory`:
If the Poole source code is, for example, in a subfolder `YourExternalProject/libs/Poole`:
```cmake
cmake_minimum_required(VERSION 3.20) # Match Poole's minimum or higher
project(YourExternalProject LANGUAGES CXX)

add_subdirectory(libs/Poole) # Points to the root CMakeLists.txt of Poole

add_executable(YourApplication main.cpp)
target_link_libraries(YourApplication PRIVATE Poole_lib) # Link against Poole_lib
```

### Using `FetchContent`:
`FetchContent` is a convenient way to download a project and then `add_subdirectory` it.
```cmake
cmake_minimum_required(VERSION 3.20) # Match Poole's minimum or higher
project(YourExternalProject LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  Poole_Project # A unique internal name for your fetched content
  GIT_REPOSITORY "https://github.com/BenrickSmit/Poole.git" # Replace with actual URL
  GIT_TAG "master" # Or a specific tag like "v0.1.6"
  # Add other FetchContent options as needed
)

FetchContent_MakeAvailable(Poole_Project)

# Poole's targets (like Poole_lib) are now available directly
add_executable(YourApplication main.cpp)
target_link_libraries(YourApplication PRIVATE Poole_lib)
```
**Important:** When using `add_subdirectory` or `FetchContent`, always point to the *root directory* of the `Poole` project (where its main `CMakeLists.txt` resides), not just a subdirectory like `src`.

# How to contribute
Should you have any contributions, be it bugfixes, possible extensions to the codebase, or even monetary, please use the GitHub issues and pull request system for any and all communication.

[To Add Monetary Contributions]


# License
Poole is currently licensed under the [ Apache 2.0 Licence](LICENSE).

