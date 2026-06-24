#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
{   // <----------- 19.1 ------------>
    // Static memory allocation happens for static and global variables
    // Automatic memory allocation happens for function parameters and local variables
    // Both have two things in common: The size of the variable / array must be known at compile time.

    new int; // dynamically allocate an integer (and discard the result)
    int* ptr{ new int }; // dynamically allocate an integer and assign the address to ptr so we can access it later
    *ptr = 7; // assign value of 7 to allocated memory
    int* ptr1{ new int (5) }; // use direct initialization
    int* ptr2{ new int { 6 } }; // use uniform initialization

    int* otherPtr{ ptr }; // otherPtr is now pointed at that same memory location
    delete ptr; // return the memory pointed to by ptr to the operating system. ptr is now a dangling pointer.
    ptr = nullptr; // set ptr to be a null pointer
    // however, otherPtr is still a dangling pointer!
    std::cout << *ptr; // Dereferencing a dangling pointer will cause undefined behavior
    delete ptr; // trying to deallocate the memory again will also lead to undefined behavior.

    int* value { new (std::nothrow) int{} }; // value will be set to a null pointer if the integer allocation fails
    if (!value) // handle case where new returned null
    { std::cerr << "Could not allocate memory\n"; } // Do error handling here

    // Deleting a null pointer is okay, and does nothing
    int value = 5;
    int* ptr{ new int{} }; // allocate memory
    ptr = &value; // old address lost, memory leak results
    ptr = new int{}; // old address lost, memory leak results
}
{   // <----------- 19.2 ------------>
    std::size_t length{};
    std::cin >> length;
    int* array{ new int[length]{} }; // use array new.  Note that length does not need to be constant!
    array[0] = 5; // set element 0 to value 5
    delete[] array; // use array delete to deallocate array
    // array new[] keeps track of how much memory allocated, so array delete[] can delete the proper amount
    int* array{ new int[5]{ 9, 7, 5, 3, 1 } }; // initialize a dynamic array since C++11
}
{   // <----------- 19.3 ------------>
    // if you use the std::exit() function, your program will terminate and no destructors will be called
}
{   // <----------- 19.4 ------------>
    int** ptrptr; // pointer to a pointer to an int, two asterisks
    int value { 5 };
    int* ptr { &value };
    int** ptrptr { &ptr };
    std::cout << **ptrptr << '\n'; // dereference to get pointer to int, dereference again to get int value
    int** ptrptr { &&value }; // not valid - address of operator (operator&) requires an lvalue, but &value is an rvalue

    int** array { new int*[10] }; // allocate an array of 10 int pointers
    int** array { new int[10][5] }; // won’t work!
    int x { 7 }; // non-constant
    int (*array)[5] { new int[x][5] }; // rightmost dimension must be constexpr
    int** array { new int*[10] }; // allocate an array of 10 int pointers — these are our rows
    for (int count { 0 }; count < 10; ++count)
        array[count] = new int[5]; // these are our columns
        array[count] = new int[count+1]; // these are our columns - non rectangle 2d array

    for (int count { 0 }; count < 10; ++count)
        delete[] array[count];
    delete[] array; // this needs to be done last
}
{   // <----------- 19.5 ------------>
    void* ptr {}; // ptr is a void pointer
    // A void pointer can point to objects of any data type:
    int nValue {};
    float fValue {};
    struct Something { int n; float f; };
    Something sValue {};
    void* ptr {};
    ptr = &nValue; // valid
    ptr = &fValue; // valid
    ptr = &sValue; // valid

    // void pointer does not know what type of object it is pointing to, dereferencing a void pointer is illegal
    int value{ 5 };
    void* voidPtr{ &value };
    std::cout << *voidPtr << '\n'; // illegal: dereference of void pointer
    int* intPtr{ static_cast<int*>(voidPtr) }; // however, if we cast our void pointer to an int pointer...
    std::cout << *intPtr << '\n'; // then we can dereference the result

    enum class Type {
        tInt, // note: we can't use "int" here because it's a keyword, so we'll use "tInt" instead
        tFloat,
        tCString
    };
    void printValue(void* ptr, Type type){
        switch (type){
        case Type::tInt:
            std::cout << *static_cast<int*>(ptr) << '\n'; // cast to int pointer and perform indirection
            break;
        case Type::tFloat:
            std::cout << *static_cast<float*>(ptr) << '\n'; // cast to float pointer and perform indirection
            break;
        case Type::tCString:
            std::cout << static_cast<char*>(ptr) << '\n'; // cast to char pointer (no indirection)
            // std::cout will treat char* as a C-style string
            // if we were to perform indirection through the result, then we'd just print the single char that ptr is pointing to
            break;
        }
    }
    int nValue{ 5 };
    float fValue{ 7.5f };
    char szValue[]{ "Mollie" };
    printValue(&nValue, Type::tInt);
    printValue(&fValue, Type::tFloat);
    printValue(szValue, Type::tCString);

    void* ptr{ nullptr }; // ptr is a void pointer that is currently a null pointer
}
    return 0;
}