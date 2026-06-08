#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
{   // <----------- 12.1 ------------>
}
{   // <----------- 12.2 ------------>
    int return5() { return 5; }
    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression
    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)
    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression
    // rvalue as temporary values that are not identifiable objects
    std::cout << 1 + 2; // 1 and 2 are rvalues, operator+ returns an rvalue
    // Assignment requires the left operand to be a modifiable lvalue expression and the right operand to be an rvalue expression
    x = 5; // valid: x is a modifiable lvalue expression and 5 is an rvalue expression
    5 = x; // error: 5 is an rvalue expression and x is a modifiable lvalue expression
    x = y; // y is not an rvalue, but this is legal - lvalue-to-rvalue conversion

    // T& is an lvalue reference, so this overload will be preferred for lvalues
    template <typename T>
    constexpr bool is_lvalue(T&) { return true; }
    // T&& is an rvalue reference, so this overload will be preferred for rvalues
    template <typename T>
    constexpr bool is_lvalue(T&&) { return false; }
    // A helper macro (#expr prints whatever is passed in for expr as text)
    #define PRINTVCAT(expr) { std::cout << #expr << " is an " << (is_lvalue(expr) ? "lvalue\n" : "rvalue\n"); }
    int getint() { return 5; }
    PRINTVCAT(5);        // rvalue - 5 is an rvalue
    PRINTVCAT(getint()); // rvalue - getint() is an rvalue
    int x { 5 };
    PRINTVCAT(x);        // lvalue - x is an lvalue
    PRINTVCAT(std::string {"Hello"}); // rvalue - std::string {"Hello"} is an rvalue
    PRINTVCAT("Hello");  // lvalue - "Hello" is an lvalue
    PRINTVCAT(++x);      // lvalue - ++x is an lvalue
    PRINTVCAT(x++);      // rvalue - x++ is an rvalue
}
{   // <----------- 12.3 ------------>
    const int& // an lvalue reference to a const int object
    // & here not mean “address of”, it means “lvalue reference to”.
    int& invalidRef;   // error: references must be initialized
    int x { 5 };
    int& ref { x };         // okay: non-const lvalue reference bound to a modifiable lvalue
    const int y { 5 };
    int& invalidRef { y };  // invalid: non-const lvalue reference can't bind to a non-modifiable lvalue
    int& invalidRef2 { 0 }; // invalid: non-const lvalue reference can't bind to an rvalue
    double d { 6.0 };
    int& invalidRef { d };     // invalid: conversion of double to int is narrowing conversion, disallowed by list initialization
    double& invalidRef2 { x }; // invalid: non-const lvalue reference can't bind to rvalue (result of converting x to double)

    int x { 5 };
    int y { 6 };
    int& ref { x }; // ref is now an alias for x
    ref = y; // assigns 6 (the value of y) to x (the object being referenced by ref)
    // The above line does NOT change ref into a reference to variable y!
    std::cout << x << '\n'; // user is expecting this to print 5

    int x { 5 };
    { int& ref { x }; }   // ref is a reference to x
    // ref is destroyed after this -- x is unaware of this

    int& ref1{ var };  // an lvalue reference bound to var
    int& ref2{ ref1 }; // an lvalue reference bound to var
}
{   // <----------- 12.4 ------------>
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value
    std::cout << ref << '\n'; // okay: we can access the const object
    ref = 6;                  // error: we can not modify an object through a const reference

    int x { 5 };          // x is a modifiable lvalue
    const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue
    ref = 7;    // error: we can not modify an object through a const reference
    x = 6;      // okay: x is a modifiable lvalue, we can still modify it through the original identifier

    const int& ref { 5 }; // okay: 5 is an rvalue
    // case 1
    const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary
    std::cout << r1 << '\n'; // prints 5
    // case 2
    char c { 'a' };
    const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary
    std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)
    
    const int& ref { 5 }; // The temporary object holding value 5 has its lifetime extended to match ref

    int g_x { 5 };
    int main(){
        [[maybe_unused]] constexpr int& ref1 { g_x }; // ok, can bind to global
        static int s_x { 6 };
        [[maybe_unused]] constexpr int& ref2 { s_x }; // ok, can bind to static local
        int x { 6 };
        [[maybe_unused]] constexpr int& ref3 { x }; // compile error: can't bind to non-static object
        static const int s_x { 6 }; // a const int
        [[maybe_unused]] constexpr const int& ref2 { s_x }; // needs both constexpr and const
        return 0;
    }
}
{   // <----------- 12.5 ------------>
    void printValue(int& y) { std::cout << y << '\n'; }
    // y only accepts modifiable lvalues
    int x { 5 };
    printValue(x); // ok: x is a modifiable lvalue
    const int z { 5 };
    printValue(z); // error: z is a non-modifiable lvalue
    printValue(5); // error: 5 is an rvalue
}
{   // <----------- 12.6 ------------>
    void printSV(std::string_view sv) { std::cout << sv << '\n'; }
    void printS(const std::string& s) { std::cout << s << '\n'; }
    std::string s{ "Hello, world" };
    std::string_view sv { s };

    // Pass to `std::string_view` parameter
    printSV(s);              // ok: inexpensive conversion from std::string to std::string_view
    printSV(sv);             // ok: inexpensive copy of std::string_view
    printSV("Hello, world"); // ok: inexpensive conversion of C-style string literal to std::string_view

    // pass to `const std::string&` parameter
    printS(s);              // ok: inexpensive bind to std::string argument
    printS(sv);             // compile error: cannot implicit convert std::string_view to std::string
    printS(static_cast<std::string>(sv)); // bad: expensive creation of std::string temporary
    printS("Hello, world"); // bad: expensive creation of std::string temporary
}
{   // <----------- 12.7 ------------>
    int* ptr1, ptr2;   // incorrect: ptr1 is a pointer to an int, but ptr2 is just a plain int!
    int* ptr3, * ptr4; // correct: ptr3 and ptr4 are both pointers to an int
    int* ptr;        // an uninitialized pointer (holds a garbage address)
    int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
    int* ptr3{ &x }; // a pointer initialized with the address of variable x

    int i{ 5 };
    double d{ 7.0 };
    int* iPtr{ &i };     // ok: a pointer to an int can point to an int object
    int* iPtr2 { &d };   // not okay: a pointer to an int can't point to a double object
    double* dPtr{ &d };  // ok: a pointer to a double can point to a double object
    double* dPtr2{ &i }; // not okay: a pointer to a double can't point to an int object
    int* ptr{ 5 }; // not okay
    int* ptr{ 0x0012FF7C }; // not okay, 0x0012FF7C is treated as an integer literal

    int x{ 4 };
	std::cout << typeid(x).name() << '\n';  // print the type of x - int
	std::cout << typeid(&x).name() << '\n'; // print the type of &x - int *
    // assume 32 bit archi
    char* chPtr{};        // chars are 1 byte
    int* iPtr{};          // ints are usually 4 bytes
    long double* ldPtr{}; // long doubles are usually 8 or 12 bytes
    std::cout << sizeof(chPtr) << '\n'; // prints 4
    std::cout << sizeof(iPtr) << '\n';  // prints 4
    std::cout << sizeof(ldPtr) << '\n'; // prints 4

    int x{ 5 };
    int* ptr{ &x };
    { int y{ 6 }; ptr = &y; }  // y goes out of scope, and ptr is now dangling
    std::cout << *ptr << '\n'; // undefined behavior from dereferencing a dangling pointer
}
{   // <----------- 12.8 ------------>
    int* ptr {}; // ptr is now a null pointer, and is not holding an address
    int* ptr { nullptr }; // can use nullptr to initialize a pointer to be a null pointer
    int x { 5 };
    ptr = &x; // ptr now pointing at object x (no longer a null pointer)
    ptr = nullptr; // Can assign nullptr to make the pointer a null pointer
    someFunction(nullptr); // we can also pass nullptr to a function that has a pointer parameter
    int* nullPtr {};
    std::cout << "nullPtr is " << (nullPtr==nullptr ? "null\n" : "non-null\n"); // explicit test for equivalence
    std::cout << "nullPtr is " << (nullPtr ? "non-null\n" : "null\n"); // implicit conversion to Boolean
    float* ptr { 0 };  // ptr is now a null pointer (for example only, don't do this)
    
    #include <cstddef> // for NULL
    double* ptr { NULL }; // ptr is a null pointer
}
{   // <----------- 12.9 ------------>
    
}
{   // <----------- 12.10 ------------>

}
{   // <----------- 12.11 ------------>

}
{   // <----------- 12.12 ------------>

}
{   // <----------- 12.13 ------------>

}
{   // <----------- 12.14 ------------>

}
{   // <----------- 12.15 ------------>

}
    return 0;
}