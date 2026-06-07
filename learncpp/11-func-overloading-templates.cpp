#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
{   // <----------- 11.1 ------------>
    int add(int x, int y){ // integer version
        return x + y;
    }
    double add(double x, double y){ // floating point version
        return x + y;
    }
    std::cout << add(1, 2); // calls add(int, int)
    std::cout << add(1.2, 3.4); // calls add(double, double)
}
{   // <----------- 11.2 ------------>
    typedef int Height; // typedef
    using Age = int; // type alias
    void print(int value);
    void print(Age value); // not differentiated from print(int)
    void print(Height value); // not differentiated from print(int)
    void print(const int); // not differentiated from print(int)
    void foo(int x, ...); // differentiated from foo(int, int) (ellipse)
   
    int getRandomValue();
    double getRandomValue(); // error - differs only by return type
}
{   // <----------- 11.3 ------------>
    void foo(const int) {}
    void foo(const double&) {} // double& is a reference to a double
    int x { 1 };
    foo(x); // x trivially converted from int to const int
    double d { 2.3 };
    foo(d); // d trivially converted from double to const double& (non-ref to ref conversion)
    void foo(int) {}
    void foo(const int&) {} // int& is a reference to a int
    foo(x); // ambiguous match with foo(int) and foo(const int&)

    foo('a');  // promoted to match foo(int)
    foo(true); // promoted to match foo(int)
    foo(4.5f); // promoted to match foo(double)

    void foo(double) {}
    void foo(std::string) {}
    foo('a'); // 'a' converted to match foo(double)

    class X { // this defines a new type called X
    public:
        operator int() { return 0; } // Here's a user-defined conversion from X to int
    };
    X x; // Here, we're creating an object of type X (named x)
    foo(x); // x is converted to type int using the user-defined conversion from X to int

    void foo(int) {}
    void foo(double) {}
    foo(5L); // err - ambiguous call - could be foo(double) or foo(int)
    
    void foo(unsigned int) {}
    void foo(float) {} // err below
    foo(0);       // int can be numerically converted to unsigned int or to float - err
    foo(3.14159); // double can be numerically converted to unsigned int or to float - err
    foo(static_cast<unsigned int>(x)); // will call foo(unsigned int) - fine

    void print(char, int) { std::cout << 'a' << '\n'; }
    void print(char, double) { std::cout << 'b' << '\n'; }
    void print(char, float) { std::cout << 'c' << '\n'; }
    print('x', 'a'); // chooses print(char, int) - unambiguously the best match
}
{   // <----------- 11.4 ------------>
    void printInt(int x) { std::cout << x << '\n'; }
    void printInt(char) = delete; // calls to this function will halt compilation
    void printInt(bool) = delete; // calls to this function will halt compilation
    
    printInt(97);   // okay
    printInt('a');  // compile error: function deleted
    printInt(true); // compile error: function deleted
    printInt(5.0);  // compile error: ambiguous match <------!

    // This function template will take precedence for arguments of other types
    // Since this function template is deleted, calls to it will halt compilation
    template <typename T>
    void printInt(T x) = delete;
    printInt(97);   // okay
    printInt('a');  // compile error
    printInt(true); // compile error
}
{   // <----------- 11.5 ------------>
    void print(int x, int y=4) {} // 4 is the default argument
    print(1, 2); // y will use user-supplied argument 2
    print(3); // y will use default argument 4, as if we had called print(3, 4)
    void foo(int x = 5);   // ok
    void goo(int x ( 5 )); // compile error
    void boo(int x { 5 }); // compile error

    void print(int x=10, int y=20, int z=30) {}
    print(1, 2); // rightmost argument defaulted
    print(1); // two rightmost arguments defaulted
    print(); // all arguments defaulted

    void print(int x=10, int y); // not allowed
    void print(std::string_view sv="Hello", double d=10.0);
    print(20.0); // error: does not match above function (cannot skip argument for sv)

    void print(int x, int y=4); // forward declaration
    void print(int x, int y=4){ // compile error: redefinition of default argument
        // some code
    }
    void print(int x, int y); // forward declaration, no default argument
    int main(){ print(3); }
    // compile error: default argument for y hasn't been defined yet
    void print(int x, int y=4){ /* some code */ }

    void print(std::string_view s) {}
    void print(char c = ' ') {}
    print("Hello, world"); // resolves to print(std::string_view)
    print('a');            // resolves to print(char)
    print();               // resolves to print(char)
    void foo(int x = 0) {}
    void foo(double d = 0.0) {}
    foo(); // err - ambiguous function call
    void print(int x);                  // signature print(int)
    void print(int x, int y = 10);      // signature print(int, int)
    void print(int x, double y = 20.5); // signature print(int, double)
    print(1); // err - ambiguous function call
}
{   // <----------- 11.6 ------------>
    template <typename T> // template parameter declaration defining T as a type template parameter
    T max(T x, T y){ // function template definition for max<T>
        return (x < y) ? y : x;
    }
}
{   // <----------- 11.7 ------------>
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)

    // when we call max<int>(1, 2), the function specialization that gets instantiated looks something like this:
    // a declaration for our function template (we don't need the definition any more)
    template <typename T>
    T max(T x, T y);

    template<> // ignore this for now
    int max<int>(int x, int y){/*code*/} // the generated function max<int>(int, int)

    template<>
    double max<double>(double x, double y){/*code*/} // the generated function max<double>(double, double)

    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)
    std::cout << max<>(1, 2) << '\n'; // deduces max<int>(int, int) (non-template functions not considered)
    std::cout << max(1, 2) << '\n'; // calls max(int, int)
    
    // T is a type template parameter
    // double is a non-template parameter
    // We don't need to provide names for these parameters since they aren't used
    template <typename T>
    int someFcn(T, double) { return 5; }
    someFcn(1, 3.4); // matches someFcn(int, double)
    someFcn(1, 3.4f); // matches someFcn(int, double) -- the float is promoted to a double
    someFcn(1.2, 3.4); // matches someFcn(double, double)
    someFcn(1.2f, 3.4); // matches someFcn(float, double)
    someFcn(1.2f, 3.4f); // matches someFcn(float, double) -- the float is promoted to a double

    // Instantiated functions may not always compile
    template <typename T>
    T addOne(T x);

    template<>
    std::string addOne<std::string>(std::string x) { return x + 1; }
    std::string hello{ "Hello, world!" }; 
    std::cout << addOne(hello) << '\n'; // err, x is string
    std::cout << addOne("Hello, world!") << '\n'; // "ello, world!" (c string)
    // Use function template specialization to tell the compiler that addOne(const char*) should emit a compilation error
    // const char* will match a string literal    
    template <>
    const char* addOne(const char* x) = delete;
    std::cout << addOne("Hello, world!") << '\n'; // compile error
    // each func instantiated will have a separate version of the static local variable
    void printIDAndValue(T value){
        static int id{ 0 };
        std::cout << ++id << ") " << value << '\n';
    }
    printIDAndValue(12); // print 1) 12
    printIDAndValue(13); // print 2) 13
    printIDAndValue(14.5); // print 1) 14.5
}
{   // <----------- 11.8 ------------>
    T max(T x, T y) {/*code*/}
    std::cout << max(2, 3.5) << '\n';  // compile error - parameter 'T' is ambiguous
    // type conversion only when resolving function overloads, not when performing template argument deduction.
    std::cout << max(static_cast<double>(2), 3.5) << '\n'; // convert our int to a double so we can call max(double, double)
    // we've explicitly specified type double, so the compiler won't use template argument deduction
    std::cout << max<double>(2, 3.5) << '\n';

    template <typename T, typename U> // We're using two template type parameters named T and U
    T max(T x, U y){ // x can resolve to type T, and y can resolve to type U
        return (x < y) ? y : x; // uh oh, we have a narrowing conversion problem here
    }
    std::cout << max(2, 3.5) << '\n'; // resolves to max<int, double>
    // prints 3 (as return type is int)
    auto max(T x, U y) {} // ask compiler can figure out what the relevant return type is

    auto max(auto x, auto y) {} // from c++ 20 and new
    // equivalent to
    template <typename T, typename U>
    auto max(T x, U y) {}
    
    // Add two values with matching types
    template <typename T>
    auto add(T x, T y) {}
    // Add two values with non-matching types
    // As of C++20 we could also use auto add(auto x, auto y)
    template <typename T, typename U>
    auto add(T x, U y) {}
    // Add three values with any type
    // As of C++20 we could also use auto add(auto x, auto y, auto z)
    template <typename T, typename U, typename V>
    auto add(T x, U y, V z) {}
    std::cout << add(1.2, 3.4) << '\n'; // instantiates and calls add<double>()
    std::cout << add(5.6, 7) << '\n';   // instantiates and calls add<double, int>()
    std::cout << add(8, 9, 10) << '\n'; // instantiates and calls add<int, int, int>()
    // add(1.2, 3.4) -> compiler prefer add<T>(T, T) over add<T, U>(T, U), as more restrictive/specialized
}
{   // <----------- 11.9 ------------>
    template <int N> // declare a non-type template parameter of type int named N
    void print(){ std::cout << N; } // use value of N here
    print<5>(); // 5 is our non-type template argument
    print<'c'>(); // 'c' converted to type int, prints 99  <!---!> only certain conversion allowed

    template <double D> // requires C++20 for floating point non-type parameters
    double getSqrt(){
        static_assert(D >= 0.0, "getSqrt(): D must be non-negative");
        if constexpr (D >= 0) // ignore the constexpr here for this example
            return std::sqrt(D); // strangely, std::sqrt isn't a constexpr function (until C++26)
        return 0.0;
    }
    std::cout << getSqrt<5.0>() << '\n';
    std::cout << getSqrt<-5.0>() << '\n';

    template <int N> // int non-type template parameter
    void print() {}
    template <char N> // char non-type template parameter
    void print() {}
    print<5>();   // ambiguous match with int N = 5 and char N = 5
    print<'c'>(); // ambiguous match with int N = 99 and char N = 'c'
    // After instantiating :-
    template <auto N> // deduce non-type template parameter from template argument
    void print() {}
    template <>
    void print<5>() {} // note that this is print<5> and not print<int>
    template <>
    void print<'c'>() {} // note that this is print<`c`> and not print<char>
}
{   // <----------- 11.10 ------------>
    template <typename T> // in main.cpp
    T addOne(T x); // function template forward declaration
    std::cout << addOne(1) << '\n'; // err - linker

    template <typename T> // in add.cpp, instead add ts in add.h
    T addOne(T x) {/*code */} // function template definition
}
    return 0;
}