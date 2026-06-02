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
{   constexpr int x { expr }; // Because variable x is constexpr, expr must be evaluatable at compile-time
    // The return value of a non-constexpr function is a runtime expression
    // even when the return expression is a constant expression
    int five(){
        return 5; // this return expression is a constant expression
    }
    // Operators without constant expression operands can only be used in runtime expressions
    std::cout << 5; // runtime expression (std::cout isn't a constant expression operand)
    int d { 5 };            // d is not usable in constant expressions (d is non-const)
    const int e { d };      // e is not usable in constant expressions (initializer is not a constant expression)
    const double f { 1.2 }; // f is not usable in constant expressions (not a const integral variable)
    
    const int x { 3 + 4 }; // constant expression 3 + 4 must be evaluated at compile-time
    int y { 3 + 4 };       // constant expression 3 + 4 may be evaluated at compile-time or runtime
}

{   // <----------- 5.6 ------------>
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not constexpr
    
    constexpr int cmax(int x, int y) // this is a constexpr function
    {
        if (x > y)
            return x;
        else
            return y;
    }
    int m4 { cmax(5, 6) };           // ok: may evaluate at compile-time or runtime
    const int m5 { cmax(5, 6) };     // ok: may evaluate at compile-time or runtime
    constexpr int m6 { cmax(5, 6) }; // okay: must evaluate at compile-time
}

{   // <----------- 5.7 ------------>
    std::string name { "Alex" }; // initialize name with string literal "Alex"
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name
    // >> std::ws -> ignores leading whitespaces
    getline(cin, name, '\n'); // delimiter (which char to end with)

    using namespace std::string_literals; // easy access to the s suffix
    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal

    constexpr std::string name{ "Alex"s }; // compile error
}

{   // <----------- 5.8 ------------>
    std::string_view s{ "Hello, world!" }; // a read-only access
    void printString(std::string str) {
        std::cout << str << '\n';
    }
    std::string_view sv{ "Hello, world!" };
	// printString(sv);   // compile error: won't implicitly convert std::string_view to a std::string
	std::string s{ sv }; // okay: we can create std::string using std::string_view initializer
	printString(s);      // and call the function with the std::string
	printString(static_cast<std::string>(sv)); // okay: we can explicitly cast a std::string_view to a std::string

    using namespace std::string_view_literals; // access the sv suffix
    std::cout << "moo\n"sv; // sv suffix is a std::string_view literal
    
    constexpr std::string_view s{ "Hello, world!" }; // s is a string symbolic constant
}

{   // <----------- 5.9 ------------> (Part 2)
    void printSV(std::string_view str){ // now a std::string_view, creates a view of the argument
        std::cout << str << '\n';
    }
    std::string_view sv{};
    {
        std::string s{ "Hello, world!" }; // create a std::string local to this nested block
        sv = s; // sv is now viewing s
    } // s is destroyed here, so sv is now viewing an invalid string
    std::cout << sv << '\n'; // undefined behavior
    
    std::string_view name { getName() }; // name initialized with return value of function
    std::cout << name << '\n'; // undefined behavior
    
    std::string_view name { "Alex"s }; // "Alex"s creates a temporary std::string
    std::cout << name << '\n'; // undefined behavior

    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is now viewing s
    s = "Hello, a!";    // modifies s, which invalidates sv (s is still valid)
    std::cout << sv << '\n';   // undefined behavior
    sv = s;                    // revalidate sv: sv is now viewing s again
    std::cout << sv << '\n';   // prints "Hello, a!"

    std::string_view getBoolName(bool b){
        std::string t { "true" };  // local variable
        std::string f { "false" }; // local variable
        if (b) return t;  // return a std::string_view viewing t
        return f; // return a std::string_view viewing f
    } // t and f are destroyed at the end of the function
    std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // undefined behavior

    std::string_view getBoolName(bool b){
        if (b) return "true";  // return a std::string_view viewing "true"
        return "false"; // return a std::string_view viewing "false"
    } // "true" and "false" are not destroyed at the end of the function

    std::string_view firstAlphabetical(std::string_view s1, std::string_view s2){
        if (s1 < s2)
            return s1;
        return s2;
    }
    std::string a { "World" };
    std::string b { "Hello" };
    std::cout << firstAlphabetical(a, b) << '\n'; // prints "Hello"

    std::string_view str{ "Nigga" };
	std::cout << str << '\n';
	// Remove 1 character from the left side of the view
	str.remove_prefix(1);
	std::cout << str << '\n'; // prints igga
	// Remove 2 characters from the right side of the view
	str.remove_suffix(2);
	std::cout << str << '\n'; // prints ga
    str = "Nigga"; // reset the view
}
    return 0;
}