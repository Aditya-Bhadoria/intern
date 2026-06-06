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

}
{   // <----------- 11.8 ------------>

}
{   // <----------- 11.9 ------------>

}
{   // <----------- 11.10 ------------>

}
    return 0;
}