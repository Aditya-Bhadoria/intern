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
    const int x { 5 }; // x is now const
    int* ptr { &x };   // compile error: cannot convert from const int* to int*
    const int* ptr { &x }; // okay: ptr is pointing to a "const int"
    *ptr = 6; // not allowed: we can't change a const value
    const int y{ 6 };
    ptr = &y; // okay: ptr now points at const int y
    int x{ 5 }; // non-const
    const int* ptr { &x }; // ptr points to a "const int"
    *ptr = 6;  // not allowed: ptr points to a "const int" so we can't change the value through ptr
    x = 6; // allowed: the value is still non-const when accessed through non-const identifier x
    
    int* const ptr { &x }; // const after the asterisk means this is a const pointer
    ptr = &y; // error: once initialized, a const pointer can not be changed.
    *ptr = 6; // okay: the value being pointed to is non-const
    const int* const ptr { &value }; // a const pointer to a const value

    int v{ 5 };
    int* ptr0 { &v };             // points to an "int" but is not const itself.  We can modify the value or the address.
    const int* ptr1 { &v };       // points to a "const int" but is not const itself.  We can only modify the address.
    int* const ptr2 { &v };       // points to an "int" and is const itself.   We can only modify the value.
    const int* const ptr3 { &v }; // points to a "const int" and is const itself.  We can't modify the value nor the address.
    // if the const is on the left side of the *, the const belongs to the value
    // if the const is on the right side of the *, the const belongs to the pointer
}
{   // <----------- 12.10 ------------>
    void printByAddress(const std::string* ptr){ // The function parameter is a pointer that holds the address of str
        std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
    }
    std::string str{ "Hello, world!" };
    printByAddress(&str); // pass str by address, does not make a copy of str

    void changeValue(int* ptr){ // note: ptr is a pointer to non-const in this example
        *ptr = 6; // change the value to 6
    }
    int x{ 5 };
    changeValue(&x); // we're passing the address of x to the function
    void changeValue(const int* ptr){ // note: ptr is now a pointer to a const
        *ptr = 6; // error: can not change const value
    }
    void print(const int* ptr){ // now a pointer to a const int
        assert(ptr); // fail the program in debug mode if a null pointer is passed (since this should never happen)
        // (optionally) handle this as an error case in production mode so we don't crash if it does happen
        if (!ptr) return;
    }
    printByAddress(&5);  // error: can't take address of r-value
}
{   // <----------- 12.11 ------------>
    void nullify([[maybe_unused]] int* ptr2){
        ptr2 = nullptr; // Make the function parameter a null pointer
    }
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x
    nullify(ptr);
    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n"); // ptr is non-null

    void nullify(int*& refptr){ // refptr is now a reference to a pointer
        refptr = nullptr; // Make the function parameter a null pointer
    }
    nullify(ptr);
    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n"); // ptr is null

    void print(int x) {} // this function accepts an integer
    void print(int* ptr) {} // this function accepts an integer pointer
	print(ptr);  // always calls print(int*) because ptr has type int* (good)
	print(0);    // always calls print(int) because 0 is an integer literal (hopefully this is what we expected)
	print(NULL); // this statement could do any of the following:
	// call print(int) (Visual Studio does this)
	// call print(int*)
	// result in an ambiguous function call compilation error (gcc and Clang do this)
	print(nullptr); // always calls print(int*)

    void print(std::nullptr_t) {}
    void print(int*) {}
    print(nullptr); // calls print(std::nullptr_t)
    print(ptr); // calls print(int*)
    ptr = nullptr;
    print(ptr); // calls print(int*) (since ptr has type int*)
}
{   // <----------- 12.12 ------------>
    std::string&       returnByReference(); // returns a reference to an existing std::string (cheap)
    const std::string& returnByReferenceToConst(); // returns a const reference to an existing std::string (cheap)
    const std::string& getProgramName(){ // returns a const reference
        static const std::string s_programName { "Calculator" }; // has static duration, destroyed at end of program
        return s_programName;
    }

    const std::string& getProgramName(){
        const std::string programName { "Calculator" }; // now a non-static local variable, destroyed when function ends
        return programName;
    }
    std::cout << getProgramName(); // undefined behavior - dangling reference
    
    // returns const reference to temporary object
    const int& returnByConstReference(){ return 5; }
    const int& ref { returnByConstReference() };
    std::cout << ref; // undefined behavior

    const int& getNextId(){
        static int s_x{ 0 }; // note: variable is non-const
        ++s_x; // generate the next id
        return s_x; // and return a reference to it
    }
    const int& id1 { getNextId() }; // id1 is a reference
    const int& id2 { getNextId() }; // id2 is a reference
    std::cout << id1 << id2 << '\n'; // prints - 22
    // IF :-
    const int id1 { getNextId() }; // id1 is a normal variable now and receives a copy of the value returned by reference from getNextId()
    const int id2 { getNextId() }; // id2 is a normal variable now and receives a copy of the value returned by reference from getNextId()
    std::cout << id1 << id2 << '\n'; // prints - 12

    // Takes two std::string objects, returns the one that comes first alphabetically
    const std::string& firstAlphabetical(const std::string& a, const std::string& b){
        return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
    }

    const std::string& foo(const std::string& s) { return s; }
    std::string getHello() { return "Hello"; }
    // implicit conversion to std::string
    const std::string s{ foo(getHello()) };
    // okay for an rvalue passed by const reference to be returned by const reference

    // takes two integers by non-const reference, and returns the greater by reference
    int& max(int& x, int& y) { return (x > y) ? x : y; }
    int a{ 5 };
    int b{ 6 };
    max(a, b) = 7; // sets the greater of a or b to 7
}
{   // <----------- 12.13 ------------>
    // return by value
    [[maybe_unused]] int x{ getByValue() }; // can use to initialize object
    std::cout << getByValue() << '\n';      // can use temporary return value in expression
    // return by out parameter
    int y{};                // must first allocate an assignable object
    getByReference(y);      // then pass to function to assign the desired value
    std::cout << y << '\n'; // and only then can we use that value
}
{   // <----------- 12.14 ------------>
    const double a { 7.8 }; // a has type const double
    auto b { a };           // b has type double (const dropped)
    constexpr double c { 7.8 }; // c has type const double (constexpr implicitly applies const)
    auto d { c };               // d has type double (const dropped)

    std::string& getRef(); // some function that returns a reference
    auto ref { getRef() }; // type deduced as std::string (not std::string&)
    auto& ref2 { getRef() }; // std::string& (reference dropped, reference reapplied)

    const int x;    // this const applies to x, so it is top-level
    int* const ptr; // this const applies to ptr, so it is top-level
    // references don't have a top-level const syntax, as they are implicitly top-level const
    const int& ref; // this const applies to the object being referenced, so it is low-level
    const int* ptr; // this const applies to the object being pointed to, so it is low-level
    const int* const ptr; // the left const is low-level, the right const is top-level
    
    const std::string& getConstRef(); // some function that returns a reference to const
    auto ref1{ getConstRef() }; // std::string (reference dropped, then top-level const dropped from result)
    auto ref1{ getConstRef() };        // std::string (reference and top-level const dropped)
    const auto ref2{ getConstRef() };  // const std::string (reference dropped, const dropped, const reapplied)
    auto& ref3{ getConstRef() };       // const std::string& (reference dropped and reapplied, low-level const not dropped)
    const auto& ref4{ getConstRef() }; // const std::string& (reference dropped and reapplied, low-level const not dropped)

    // Constexpr is not part of an expression’s type, so it is not deduced by auto.
    constexpr const std::string_view& getConstRef() {} // function is constexpr, returns a const std::string_view&
    auto ref1{ getConstRef() };                  // std::string_view (reference dropped and top-level const dropped)
    constexpr auto ref2{ getConstRef() };        // constexpr const std::string_view (reference dropped and top-level const dropped, constexpr applied, implicitly const)
    auto& ref3{ getConstRef() };                 // const std::string_view& (reference reapplied, low-level const not dropped)
    constexpr const auto& ref4{ getConstRef() }; // constexpr const std::string_view& (reference reapplied, low-level const not dropped, constexpr applied)

    std::string* getPtr(); // some function that returns a pointer
    auto ptr1{ getPtr() };      // std::string*
    auto* ptr2{ getPtr() };     // std::string*
    auto ptr3{ *getPtr() };     // std::string (because we dereferenced getPtr())
    auto* ptr4{ *getPtr() };    // does not compile (initializer not a pointer)

    const auto ptr1{ getPtr() };  // std::string* const
    auto const ptr2 { getPtr() }; // std::string* const
    const auto* ptr3{ getPtr() }; // const std::string*
    auto* const ptr4{ getPtr() }; // std::string* const

    std::string s{};
    const std::string* const ptr { &s };
    auto ptr1{ ptr };  // const std::string*
    auto* ptr2{ ptr }; // const std::string*
    auto const ptr3{ ptr };  // const std::string* const
    const auto ptr4{ ptr };  // const std::string* const
    auto* const ptr5{ ptr }; // const std::string* const
    const auto* ptr6{ ptr }; // const std::string*
    const auto const ptr7{ ptr };  // error: const qualifer can not be applied twice
    const auto* const ptr8{ ptr }; // const std::string* const
}
{   // <----------- 12.15 ------------>
    // std::numeric_limits<T>::lowest() returns most -ve value for type T
    // std::numeric_limits<T>::max() largest +ve for type T
    // Our function now optionally returns an int value
    std::optional<int> doIntDivision(int x, int y){
        if (y == 0) return {}; // or return std::nullopt
        return x / y;
    }
    std::optional<int> result1 { doIntDivision(20, 5) };
    std::optional<int> result2 { doIntDivision(5, 0) };
    if (result1) // if the function returned a value
        std::cout << "Result 1: " << *result1 << '\n'; // get the value
    else std::cout << "Result 1: failed\n";
    // prints - 4, Result 2: failed

    if (o1.has_value()) // call has_value() to check if o1 has a value
    if (o2)             // use implicit conversion to bool to check if o2 has a value
    std::cout << *o1;             // dereference to get value stored in o1 (undefined behavior if o1 does not have a value)
    std::cout << o2.value();      // call value() to get value stored in o2 (throws std::bad_optional_access exception if o2 does not have a value)
    std::cout << o3.value_or(42); // call value_or() to get value stored in o3 (or value `42` if o3 doesn't have a value)

    void printIDNumber(std::optional<const int> id = std::nullopt){
        if (id)
            std::cout << "Your ID number is " << *id << ".\n";
        else
            std::cout << "Your ID number is not known.\n";
    }
    printIDNumber(); // we don't know the user's ID yet
    int userid { 34 };
    printIDNumber(userid); // we know the user's ID now
    printIDNumber(62); // we can also pass an rvalue -> can't do this if parameter of type const int *

    struct Employee{
        std::string name{}; // expensive to copy
        int id;
    };
    void printEmployeeID(std::optional<std::reference_wrapper<Employee>> e=std::nullopt){
        if (e) std::cout << "Your ID number is " << e->get().id << ".\n";
        else std::cout << "Your ID number is not known.\n";
    }
    // std::optional doesn’t support references directly, can use std::reference_wrapper to mimic reference
}
    return 0;
}