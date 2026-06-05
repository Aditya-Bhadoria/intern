#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
{   // <----------- 10.1 ------------>
    int n { 3 };                        // here's int value 3
    float f {};                         // here's our float variable
    std::memcpy(&f, &n, sizeof(float)); // copy the bits from n into f
    std::cout << f << '\n';             // print f (containing the bits from n)
    // prints 4.2039e-45
    double d{ 3 }; // int value 3 implicitly converted to type double
    if (5){} // int value 5 implicitly converted to type bool
    int x { "14" }; // invalid conversion from 'const char*' to 'int'
    int x { 3.5 }; // brace-initialization disallows conversions that result in data loss
}
{   // <----------- 10.4 ------------>
    double d{ 5.0 };
    someFcn(d); // bad: implicit narrowing conversion will generate compiler warning
    // good: we're explicitly telling the compiler this narrowing conversion is intentional
    someFcn(static_cast<int>(d)); // no warning generated
    int i { 3.5 }; // won't compile
    int i { static_cast<int>(d) }; // converts double to int, initializes i with int result

    constexpr int n1{ 5 };   // note: constexpr
    unsigned int u1 { n1 };  // okay: conversion is not narrowing due to exclusion clause
    constexpr int n2 { -5 }; // note: constexpr
    unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change
    constexpr double d { 0.1 };
    float f { d }; // not narrowing, even though loss of precision results
    float f { 1.23456789 }; // not a narrowing conversion, even though precision lost!
    
    // We can avoid static_casts
    constexpr int n{ 5 };
    double d { n };       // okay (we don't need a static_cast here)
    short s { 5 };        // okay (there is no suffix for short, we don't need a static_cast here)
}
{   // <----------- 10.6 ------------>
    double d = 10 / 4; // does integer division, initializes d with value 2.0
    double d = 10.0 / 4.0; // does floating point division, initializes d with value 2.5
    int x { 10 };
    int y { 4 };
    std::cout << (double)x / y << '\n'; // C-style cast of x to double
    std::cout << double(x) / y << '\n'; //  // function-style cast of x to double

    char c { 'a' };
    std::cout << static_cast<int>(c) << '\n'; // prints 97 rather than a
    // static cast x to a double so we get floating point division
    std::cout << static_cast<double>(x) / y << '\n'; // prints 2.5
    int x { static_cast<int>("Hello") }; // invalid: will produce compilation error
    int i { 48 };
    // explicit conversion from int to char, so that a char is assigned to variable ch
    char ch { static_cast<char>(i) };
    std::cout << double{x} / y << '\n'; // okay if int is 32-bit, error if x is 64-bit
    
    unsigned char c { 'a' };
    std::cout << unsigned int { c } << '\n'; // error
    using uint = unsigned int;
    std::cout << uint { c } << '\n'; // correct
}
{   // <----------- 10.7 ------------>
    using Distance = double; // define Distance as an alias for type double
    
    using Miles = long; // define Miles as an alias for type long
    using Speed = long; // define Speed as an alias for type long
    Miles distance { 5 }; // distance is actually just a long
    Speed mhz  { 3200 };  // mhz is actually just a long
    distance = mhz; // Ts is syntactically valid (but semantically meaningless)

    // The following aliases are identical
    typedef long Miles;
    using Miles = long;
    typedef Distance double; // incorrect (typedef name first)
    typedef double Distance; // correct (aliased type name first)

    typedef int (*FcnType)(double, char); // FcnType hard to find
    using FcnType = int(*)(double, char); // FcnType easier to find
    
    // uses
    #ifdef INT_2_BYTES
    using int8_t = char;
    using int16_t = int;
    using int32_t = long;
    #else
    using int8_t = char;
    using int16_t = short;
    using int32_t = int;
    #endif

    std::int8_t x{ 97 }; // int8_t is usually a typedef for signed char
}
    return 0;
}