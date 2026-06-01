#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    #ifndef ONLINE_JUDGE
    freopen("/Users/Adity/Downloads/CP/input.txt", "r", stdin);
    freopen("/Users/Adity/Downloads/CP/output.txt", "w", stdout);
    #endif
    // <----------- 5.1 ------------>
{   int x { 4 }; // x is a non-constant variable
    const double gravity; // error: const variables must be initialized
}
    // <----------- 5.2 ------------>
{   float f { 4.1 }; // warning: 4.1 is a double literal, not a float literal
    float f { 4.1f }; // use 'f' suffix so the literal is a float and matches variable type of float
    double d { 4.1 }; // change variable to type double so it matches the literal type double
}
    // <----------- 5.3 ------------>
{   int x{ 012 }; // 0 before the number means this is octal
    int x{ 0xF }; // 0x before the number means this is hexadecimal
    int bin { 0b1011'0010 };  // assign binary 1011 0010 to the variable
    long value { 2'132'673'462 }; // much easier to read than 2132673462
    int bin { 0b'1011'0010 };  // error: ' used before first digit of value
    std::cout << x << '\n'; // decimal (by default)
    std::cout << std::hex << x << '\n'; // hexadecimal
    std::cout << x << '\n'; // now stays hexadecimal
    std::cout << std::oct << x << '\n'; // octal
    std::cout << std::dec << x << '\n'; // return to decimal
    std::cout << x << '\n'; // decimal

    // std::bitset<8> means we want to store 8 bits
	std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101
	std::bitset<8> bin2{ 0xC5 }; // hexadecimal literal for binary 1100 0101

	std::cout << bin1 << '\n' << bin2 << '\n';
	std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it
}
    // <----------- 5.4 ------------>
    // The following are non-constants:
    // Not recommended
{   [[maybe_unused]] int a { 5 };

    // The following are compile-time constants:
    [[maybe_unused]] const int b { 5 };
    [[maybe_unused]] const double c { 1.2 };
    [[maybe_unused]] const int d { b };       // b is a compile-time constant

    // The following are runtime constants:
    [[maybe_unused]] const int e { a };       // a is non-const
    [[maybe_unused]] const int f { e };       // e is a runtime constant
    [[maybe_unused]] const int g { five() };  // return value isn't known until runtime
    [[maybe_unused]] const int h { pass(5) }; // return value isn't known until runtime
}
    // <----------- 5.5 ------------>
{   
}
    return 0;
}