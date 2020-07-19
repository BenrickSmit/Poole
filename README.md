# Poole
A C++ class which implements threadpooling for all kinds of functions using the standard C++ std::thread objects.

Poole can accept normal void functions (functions with no return type) and functions which don't have parameters. Additionally, the function can accept lambdas, which naturally allow all kinds of functions (i.e. functions with return types and parameters, as long as you know how.).

# Lambdas
This class can only natively use void functions with no input parameters due to focusing primarily on simplicity. The only way to get around it, is to use lambdas.

Lambdas (Lambda experssions) are convenient ways of defining anonymous functions objects (closures) at the exact point where it is invoked or passed to a function without all the hassles of normal function declarations.

Using the below code example, it is possible to create different kinds of lambdas for use with the class
<code>
    [<input parameters>](){/*Your code;*/}
</code>

NOTE: It might be necessary to pass in either a this parameter, or any other parameters used by the lambda for the function to execute properly.
<code>
    [this, int_var](){m_int = int_var;}
</code>

# How to use
The class is rather simple to use. It has five public member functions, namely: get_possible_threads(), force_shutdown(), wait(), is_busy(), and add_function(...).

<b>get_possible_threads():</b> obtains and returns the total number of threads possible on your machine.
<b>force_shutdown():</b> force closes all functions currently executing by stopping the threads themselves. As such, the code might not finish executing.
<b>wait():</b> forces the program to wait for all functions passed to the class to finish executing, even stopping the main class to do so.
<b>is_busy():</b> determines whether there is at least one thread still busy executing a function. Will return false only when the pool has no active threads.
<b>add_function([](){/*Your code*/})</b> this is the main part of the class. It takes lambdas, or simple void functions.

NOTE: when using threads with CMAKE, ensure to add the parameter set(CMAKE_CXX_FLAGS "-pthread")

# Examples
<code>
    void function(){
        std::cout << "This is a void function" << std::endl;
    }

    int function1(int input){
        std::cout << "The square of the value is: " << input*input << std::endl;
        return input*input;
    }

    int function3(){
        int TOTAL_ELEMENTS = 10000;
        std::vector<int> random_numbers;
        for(auto i = 0; i < TOTAL_ELEMENTS; ++i>){
            random_number.push_back(rand() % 1000000);
        }

        for(auto i = 0; i < TOTAL_ELEMENTS; ++i>){
            for(auto j = 0; j < TOTAL_ELEMENTS; ++j>){
                if(random_numbers.at(i) < random_numberss.at(j)){
				auto temp = random_numberss.at(j);
				random_numbers[j] = random_numbers.at(i);
				random_numbers[i] = temp;
			}
            }
        }
    }

    int main(){
        // Declare the thread pool object
        Poole thread_pool;
        int square = 2;
        int input = 2;

        // Add the functions. 
        thread_pool.add_function(function());
        thread_pool.add_function([](){square = function1(input);});
        thread_pool.add_function([](){function3()});

        // Wait until all functions execute. If not, the sorting algorithm might not complete before the program ends
        thread_pool.wait();

        return 0;
    }
</code>

# License
This project is published under the [Apache 2.0 License](LICENSE)

# Contributions
At this point in time, contributions in the form of bug reports would do nicely.