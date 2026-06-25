#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
{   // <----------- 20.1 ------------>
    int foo() { return 5; } // code starts at memory address 0x002717f0
    std::cout << foo << '\n'; // we meant to call foo(), but instead we're printing foo itself!
    // generally converts to bool, prints 1 (as non-null ptr), to print the function address -
    std::cout << reinterpret_cast<void*>(foo) << '\n'; // Tell C++ to interpret function foo as a void pointer (implementation-defined behavior)

    int (*fcnPtr)(); // fcnPtr is a pointer to a function that takes no arguments and returns an integer
    int (*const fcnPtr)(); // const function ptr
    const int (*fcnPtr)(); // function returning const int

    int (*fcnPtr)(){ &foo }; // fcnPtr points to function foo
    fcnPtr = &goo; // fcnPtr now points to function goo

    // function prototypes
    int foo();
    double goo();
    int hoo(int x);
    // function pointer initializers
    int (*fcnPtr1)(){ &foo };    // okay
    int (*fcnPtr2)(){ &goo };    // wrong -- return types don't match!
    double (*fcnPtr4)(){ &goo }; // okay
    fcnPtr1 = &hoo;              // wrong -- fcnPtr1 has no parameters, but hoo() does
    int (*fcnPtr3)(int){ &hoo }; // okay

    int foo();
    int (*fcnPtr5)() { foo }; // okay, foo implicitly converts to function pointer to foo
    void* vPtr { foo };       // not okay, though some compilers may allow
    int (*fcnptr)() { nullptr }; // okay

    (*fcnPtr)(5); // call function foo(5) through fcnPtr. - explicit dereference
    fcnPtr(5); // call function foo(5) through fcnPtr.    - implicit dereference
    if (fcnPtr) // make sure fcnPtr isn't a null pointer
        fcnPtr(5); // otherwise this will lead to undefined behavior

    // Default arguments don’t work for functions called through function pointers -
    void print(int x){ std::cout << "print(int)\n"; }
    void print(int x, int y = 10) { std::cout << "print(int, int)\n"; }
    //      print(1); // ambiguous function call
    // Deconstructed method
    using vnptr = void(*)(int); // define a type alias for a function pointer to a void(int) function
    vnptr pi { print }; // initialize our function pointer with function print
    pi(1); // call the print(int) function through the function pointer
    // Concise method
    static_cast<void(*)(int)>(print)(1); // call void(int) version of print with argument 1

    // Functions used as arguments to another function are sometimes called callback functions
    // Note our user-defined comparison is the third parameter
    void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int)){
        for () {
            for () {
                if (comparisonFcn(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
                { bestIndex = currentIndex; }
            }
            std::swap(array[startIndex], array[bestIndex]);
        }
    }
    // Here is a comparison function that sorts in ascending order
    bool ascending(int x, int y) {
        return x > y; // swap if the first element is greater than the second
    }
    // Here is a comparison function that sorts in descending order
    bool descending(int x, int y) {
        return x < y; // swap if the second element is greater than the first
    }
    int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };
    // Sort the array in descending order using the descending() function
    selectionSort(array, 9, descending);
    // Sort the array in ascending order using the ascending() function
    selectionSort(array, 9, ascending);
    bool evensFirst(int x, int y){
        // if x is even and y is odd, x goes first (no swap needed)
        if ((x % 2 == 0) && !(y % 2 == 0)) return false;
        // if x is odd and y is even, y goes first (swap needed)
        if (!(x % 2 == 0) && (y % 2 == 0)) return true;
        // otherwise sort in ascending order
        return ascending(x, y);
    }
    selectionSort(array, 9, evensFirst);

    // Note: If a function parameter is of a function type, it will be converted to a pointer to the function type
    void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
    void selectionSort(int* array, int size, bool comparisonFcn(int, int)) // both equivalent
    // but only for function parameters
    
    // Default the sort to ascending sort
    void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int) = ascending);

    using ValidateFunction = bool(*)(int, int);
    bool validate(int x, int y, bool (*fcnPtr)(int, int)); // ugly
    bool validate(int x, int y, ValidateFunction pfcn) // clean
    #include <functional>
    bool validate(int x, int y, std::function<bool(int, int)> fcn); // std::function method that returns a bool and takes two int parameters
    // std::function only allows calling the function via implicit dereference - fcnPtr()
	auto fcnPtr{ &foo }; // clean but info [lost] (linkin park reference btw)
}
{   // <----------- 20.2 ------------>
    // The call stack keeps track of all the active functions (those that have been called but have not yet terminated)
    // my stack overflowed
}
{   // <----------- 20.3 ------------>
    // A tail call is a function call that occurs at the tail (end) of a function
}
{   // <----------- 20.4 ------------>
    int main(int argc, char* argv[])
    // argc is an integer parameter containing a count of the number of arguments passed to the program
    // argv is where the actual argument values are stored
    
    #include <sstream> // for std::stringstream
    int main(int argc, char* argv[]) {
        if (argc <= 1) {
            // On some operating systems, argv[0] can end up as an empty string instead of the program's name.
            // We'll conditionalize our response on whether argv[0] is empty or not.
            if (argv[0]) std::cout << "Usage: " << argv[0] << " <number>" << '\n';
            else std::cout << "Usage: <program name> <number>" << '\n';
            return 1;
        }
        std::stringstream convert{ argv[1] }; // set up a stringstream variable named convert, initialized with the input from argv[1]
        int myint{};
        if (!(convert >> myint)) // do the conversion
            myint = 0; // if conversion fails, set myint to a default value
        std::cout << "Got integer: " << myint << '\n';
        return 0;
    }
    
    // strings passed in double quotes are considered to be part of the same string
    // MyArgs "Hello world!"
    // prints:
    // There are 2 arguments:
    // 0 C:\MyArgs
    // 1 Hello world!
    
    // MyArgs \"Hello world!\"
    // prints:
    // There are 3 arguments:
    // 0 C:\MyArgs
    // 1 "Hello
    // 2 world!"
}
{   // <----------- 20.5 ------------>
    // return_type function_name(argument_list, ...)

    #include <cstdarg> // needed to use ellipsis
    // The ellipsis must be the last parameter
    // count is how many additional arguments we're passing
    double findAverage(int count, ...){
        int sum{ 0 };
        std::va_list list; // We access the ellipsis through a va_list, so let's declare one

        // We initialize the va_list using va_start.  The first argument is the list to initialize.
        // The second argument is the last non-ellipsis parameter.
        va_start(list, count);

        // Loop through all the ellipsis values
        for (int arg{ 0 }; arg < count; ++arg){
            // We use va_arg to get values out of our ellipsis
            // The 1st arg is the va_list we're using, 2nd arg is the type of the value
            sum += va_arg(list, int);
        }
        va_end(list); // Cleanup the va_list when we're done.
        return static_cast<double>(sum) / count;
    }
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';
    // va_start() can be called again any time we want to reset the va_list to point to the first parameter in the ellipses again
    // ellipsis throw away number and type of parameters, thus need a count parameter

	// Loop indefinitely - don't need to pass count by using sentinel
	while (true) {
		// We use va_arg to get values out of our ellipsis
		// The 1st arg is the va_list we're using, 2nd arg is the type of the value
		int arg{ va_arg(list, int) };
		if (arg == -1) break; // If this parameter is our sentinel value, stop looping
		sum += arg;
		++count;
	}

    // Use a decoder string
    double findAverage(std::string_view decoder, ...){
    	for (auto codetype: decoder){
            switch (codetype) {
            case 'i':
                sum += va_arg(list, int);
                break;
            case 'd':
                sum += va_arg(list, double);
                break;
            }
        }
    }
}
{   // <----------- 20.6 ------------>
    // Lambda form -
    // [ captureClause ] ( parameters ) -> returnType
    // { statements; }
    [] {}; // a lambda with an omitted return type, no captures, and omitted parameters.

    constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };
    // Define the function right where we use it.
    auto found{ std::find_if(arr.begin(), arr.end(),
                           [](std::string_view str){ // here's our lambda, no capture clause
                             return str.find("nut") != std::string_view::npos;
                           }) };

    // Bad: We have to read the lambda to understand what's happening.
    return std::all_of(array.begin(), array.end(), [](int i){ return ((i % 2) == 0); });

    // Good: Instead, we can store the lambda in a named variable and pass it to the function.
    auto isEven{
        [](int i) { return (i % 2) == 0; }
    };
    return std::all_of(array.begin(), array.end(), isEven);
    // special kind of object called a functor - contain an overloaded operator() that make them callable like a function.

    // A regular function pointer. Only works with an empty capture clause (empty []).
    double (*addNumbers1)(double, double){ [](double a, double b) { return a + b; } };
    addNumbers1(1, 2);
    // Using std::function. The lambda could have a non-empty capture clause (discussed next lesson).
    std::function addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead
        [](double a, double b) { return a + b; }
    };
    addNumbers2(3, 4);
    // Using auto. Stores the lambda with its real type.
    auto addNumbers3{ [](double a, double b) { return a + b; } };

    // Case 1: use a `std::function` parameter
    void repeat1(int repetitions, const std::function<void(int)>& fn){
        for (int i{ 0 }; i < repetitions; ++i) fn(i);
    }
    // Case 2: use a function template with a type template parameter
    template <typename T>
    void repeat2(int repetitions, const T& fn) {
        for (int i{ 0 }; i < repetitions; ++i) fn(i);
    }
    // Case 3: use the abbreviated function template syntax (C++20)
    void repeat3(int repetitions, const auto& fn) {
        for (int i{ 0 }; i < repetitions; ++i) fn(i);
    }
    // Case 4: use function pointer (only for lambda with no captures)
    void repeat4(int repetitions, void (*fn)(int)) {
        for (int i{ 0 }; i < repetitions; ++i) fn(i);
    }
    auto lambda = [](int i) { std::cout << i << '\n'; };
    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);
    repeat4(3, lambda);

    constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
        "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
    };
    // Search for two consecutive months that start with the same letter.
    const auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                            [](const auto& a, const auto& b) { return a[0] == b[0]; }) };
    std::cout << *sameLetter << " and " << *std::next(sameLetter)

    // Constexpr lambda - count how many months consist of 5 letters
    constexpr auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
                    [](std::string_view str) { return str.length() == 5; }) }; // can't use auto here -> would be inferred as C-style string (const char*)
    std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";

    auto divide{ [](int x, int y, bool intDivision) { // note: no specified return type
        if (intDivision) return x / y; // return type is int
        else return static_cast<double>(x) / y; // ERROR: return type doesn't match previous return type
    } };
    // note: explicitly specifying this returns a double
    auto divide{ [](int x, int y, bool intDivision) -> double {
        if (intDivision) return x / y; // will do an implicit conversion of result to double
        else return static_cast<double>(x) / y;
    } };

    // Pass std::greater to std::sort
    std::sort(arr.begin(), arr.end(), std::greater{}); // note: need curly braces to instantiate object
}
{   // <----------- 20.7 ------------>
    std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };
    std::string search{}; std::cin >> search;
    auto found{ std::find_if(arr.begin(), arr.end(), [](std::string_view str) {
        // Search for @search rather than "nut".
        return str.find(search) != std::string_view::npos; // Error: search not accessible in this scope
    }) };
    // Can only access objects with static (or thread local) storage duration OR are constexpr
    // Capture @search                                vvvvvv
    auto found{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) 
    { return str.find(search) != std::string_view::npos; }) };
    // each variable that the lambda captures, a clone of that variable is made
    // operator() treats captures as const, meaning the lambda is not allowed to modify those captures.
    // To allow modifications of variables that were captured, we can mark the lambda as mutable:
    int ammo{ 10 };
    auto shoot{ [ammo]() mutable { // now mutable
        --ammo; // We're allowed to modify ammo now
        std::cout << "Pew! " << ammo << " shot(s) left.\n";
    }};
    shoot(); // print 9
    shoot(); // print 8
    std::cout << ammo << " shot(s) left\n"; // print 10 - lambda captured a copy of ammo

    auto shoot{ // We don't need mutable anymore
        [&ammo]() { // &ammo means ammo is captured by reference
        --ammo; // Changes to ammo will affect main's ammo
        std::cout << "Pew! " << ammo << " shot(s) left.\n";
    }};
    shoot(); // print 9
    std::cout << ammo << " shot(s) left\n"; // print 9 too

    int comparisons{ 0 };
    std::sort(cars.begin(), cars.end(),
        // Capture @comparisons by reference.
        [&comparisons](const auto& a, const auto& b) {
        ++comparisons; // We captured comparisons by reference. We can modify it without "mutable".
        return a.make < b.make; // Sort the cars by their make.
    });

    // Capture health and armor by value, and enemies by reference.
    [health, armor, &enemies](){};

    // To capture all used variables by value, use a capture value of =.
    // To capture all used variables by reference, use a capture value of &.
    auto found{ std::find_if(areas.begin(), areas.end(),
                    [=](int knownArea) { // will default capture width and height by value
                return width * height == knownArea; }) }; // because they're mentioned here
    
    [=, &enemies](){}; // Capture enemies by reference and everything else by value.
    [&, armor](){}; // Capture armor by value and everything else by reference.
    [&, &armor](){}; // Illegal, we already said we want to capture everything by reference.
    [=, armor](){}; // Illegal, we already said we want to capture everything by value.
    [armor, &health, &armor](){}; // Illegal, armor appears twice.
    [armor, &](){}; // Illegal, the default capture has to be the first element in the capture group.

    auto found{ std::find_if(areas.begin(), areas.end(),
            // Declare a new variable that's visible only to the lambda.
            // The type of userArea is automatically deduced to int.
            [userArea{ width * height }](int knownArea) { return userArea == knownArea; }) };

    // returns a lambda
    auto makeWalrus(const std::string& name){
        // Capture name by reference and return the lambda.
        return [&](){ std::cout << "My name is " << name << '\n'; }; // Undefined behavior
    }
    // In main() - Create a new walrus whose name is Roofus.
    // sayName is the lambda returned by makeWalrus.
    auto sayName{ makeWalrus("Roofus") };
    // Call the lambda function that makeWalrus returned.
    sayName();

    void myInvoke(const std::function<void()>& fn) { fn(); }
    int i{ 0 };
    // Increments and prints its local copy of @i.
    auto count{ [i]() mutable { std::cout << ++i << '\n'; } };
    myInvoke(count); 
    myInvoke(count);
    myInvoke(count); // prints 1 1 1, instead of 1 2 3 because copy of lambda made
    // option 1
    std::function count{ [i]() mutable { /*code */ }}; // lambda object stored in a std::function
    // option 2 - std::ref(count) ensures count is treated like a reference
    // thus, anything that tries to copy count will actually copy the reference
    // ensuring that only one count exists
    myInvoke(std::ref(count));
    myInvoke(std::ref(count));
    myInvoke(std::ref(count));
    // option 2 works even if myInvoke takes fn by value

    std::string favoriteFruit{ "grapes" };
    auto printFavoriteFruit
    { [=]() { std::cout << "I like " << favoriteFruit << '\n'; } };
    favoriteFruit = "bananas with chocolate";
    printFavoriteFruit(); // prints - I like grapes
}
{   // <----------- 20.x ------------>
    // hysterical and useless
}
    return 0;
}