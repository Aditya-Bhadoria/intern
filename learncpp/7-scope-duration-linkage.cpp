#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    #ifndef ONLINE_JUDGE
    freopen("/Users/Adity/Downloads/CP/input.txt", "r", stdin);
    freopen("/Users/Adity/Downloads/CP/output.txt", "w", stdout);
    #endif
{   // <----------- 7.2 ------------>
    namespace Foo{ // define a namespace named Foo
        // This doSomething() belongs to namespace Foo
        int doSomething(int x, int y){
            return x + y;
        }
        void print(){ // this print() lives in the Foo namespace
            std::cout << "Hello";
        }
        void printHelloThere(){
            print();   // calls print() in Foo namespace
            ::print(); // calls print() in global namespace
        }
    }
    namespace Goo{ // define a namespace named Goo
        // This doSomething() belongs to namespace Goo
        int doSomething(int x, int y){
            return x - y;
        }
    }
    void print(){ // this print() lives in the global namespace
        std::cout << " there\n";
    }
    namespace Foo{
        namespace Goo{ // Goo is a namespace inside the Foo namespace
            int add(int x, int y){
                return x + y;
            }
        }
    }
    namespace Foo::Goo // Goo is a namespace inside the Foo namespace (C++17 style)
    int main(){
        std::cout << Foo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Foo
        std::cout << Goo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Goo
        ::print();    // call print() in global namespace
        namespace Active = Foo::Goo; // active now refers to Foo::Goo
        std::cout << Active::add(1, 2) << '\n';
        namespace Active = V2; // active now refers to V2

        return 0;
    }
}
{   // <----------- 7.6 ------------>
    static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword
    static int g_x{ 1 };     // defines initialized internal global variable
    const int g_y{ 1 }; // const globals have internal linkage by default
    constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default
    [[maybe_unused]] constexpr int g_x { 2 }; // this internal g_x is only accessible within a.cpp
    static int foo() {};     // defines internal function
}
{   // <----------- 7.7 ------------>
    void sayHi(){ // this function has external linkage, and can be seen by other files
        std::cout << "Hi!\n";
    }
    void sayHi(); // forward declaration for function sayHi, makes sayHi accessible in this file
    
    // Global variable forward declarations (extern w/ no initializer):
    extern int g_y;                 // forward declaration for non-constant global variable
    extern const int g_y;           // forward declaration for const global variable
    extern constexpr int g_y;       // not allowed: constexpr variables can't be forward declared

    // External global variable definitions (no extern)
    int g_x;                        // defines non-initialized external global variable (zero initialized by default)
    int g_x { 1 };                  // defines initialized external global variable

    // External const global variable definitions (extern w/ initializer)
    extern const int g_x { 2 };     // defines initialized const external global variable
    extern constexpr int g_x { 3 }; // defines initialized constexpr external global variable
}

{   // <----------- 7.9 ------------>
    inline int min(int x, int y){ // inline keyword means this function is an inline function
        return (x < y) ? x : y;
    }
}
{   // <----------- 7.11 ------------>
    void incrementAndPrint(){
        static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
        ++s_value;
        std::cout << s_value << '\n';
    } // s_value is not destroyed here, but becomes inaccessible because it goes out of scope
    incrementAndPrint(); incrementAndPrint(); incrementAndPrint();
    // prints 2 3 4
    int generateID(){
        static int s_itemID{ 0 };
        return s_itemID++; // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
    }
}
    return 0;
}