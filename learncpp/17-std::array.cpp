#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    // !!!!!!!!!!! OVERVIEW ONLY !!!!!!!!!!!!!
    
{   // <----------- 17.1 ------------>
    // Use std::array for constexpr arrays, and std::vector for non-constexpr arrays.
    #include <array>  // for std::array
    #include <vector> // for std::vector
    std::array<int, 5> a {};  // a std::array of 5 ints
    std::vector<int> b(5);    // a std::vector of 5 ints (for comparison)
    
    // The length of a std::array must be a constant expression
    std::array<int, 7> a {}; // Using a literal constant
    constexpr int len { 8 };
    std::array<int, len> b {}; // Using a constexpr variable
    enum Colors { red, green, blue, max_colors };
    std::array<int, max_colors> c {}; // Using an enumerator
    #define DAYS_PER_WEEK 7
    std::array<int, DAYS_PER_WEEK> d {}; // Using a macro (don't do this, use a constexpr variable instead)

    void foo(const int length) // length is a runtime constant
    { std::array<int, length> e {}; } // error: length is not a constant expression
    // using a non-const variable
    int numStudents{};
    std::cin >> numStudents; // numStudents is non-constant
    std::array<int, numStudents> {}; // error: numStudents is not a constant expression
    foo(7);
    std::array<int, 0> arr {}; // creates a zero-length std::array
    std::cout << arr.empty();  // true if arr is zero-length

    std::array<int, 6> fibonnaci = { 0, 1, 1, 2, 3, 5 }; // copy-list initialization using braced list
    std::array<int, 5> prime { 2, 3, 5, 7, 11 };         // list initialization using braced list (preferred)

    std::array<int, 5> a;   // Members default initialized (int elements are left uninitialized)
    std::array<int, 5> b{}; // Members value initialized (int elements are zero initialized) (preferred)
    std::vector<int> v(5);  // Members value initialized (int elements are zero initialized) (for comparison)

    std::array<int, 4> a { 1, 2, 3, 4, 5 }; // compile error: too many initializers
    std::array<int, 4> b { 1, 2 };          // b[2] and b[3] are value initialized
    constexpr std::array<int, 5> prime { 2, 3, 5, 7, 11 };
    // CTAD
    constexpr std::array a1 { 9, 7, 5, 3, 1 }; // The type is deduced to std::array<int, 5>
    constexpr std::array a2 { 9.7, 7.31 };     // The type is deduced to std::array<double, 2>
    // However
    constexpr std::array<int> a2 { 9, 7, 5, 3, 1 };     // error: too few template arguments (length missing)
    constexpr std::array<5> a2 { 9, 7, 5, 3, 1 };       // error: too few template arguments (type missing)
    // TAD
    constexpr auto myArray1 { std::to_array<int, 5>({ 9, 7, 5, 3, 1 }) }; // Specify type and size
    constexpr auto myArray2 { std::to_array<int>({ 9, 7, 5, 3, 1 }) };    // Specify type only, deduce size
    constexpr auto myArray3 { std::to_array({ 9, 7, 5, 3, 1 }) };         // Deduce type and size
}
{   // <----------- 17.2 ------------>
    // std::array is implemented as a template struct whose declaration looks like this:
    template<typename T, std::size_t N> // N is a non-type template parameter
    struct array;

    // the length of a std::array is constexpr
    std::array arr { 9, 7, 5, 3, 1 }; // note: not constexpr for this example
    constexpr int length{ std::size(arr) }; // ok: return value is constexpr std::size_t and can be converted to int, not a narrowing conversion
    
    // compile-time bounds checking when we have a constexpr index, we can use the std::get()
    constexpr std::array prime{ 2, 3, 5, 7, 11 };
    std::cout << std::get<3>(prime); // print the value of element with index 3
    std::cout << std::get<9>(prime); // invalid index (compile error)
}
{   // <----------- 17.3 ------------>
    void passByRef(const std::array<int, 5>& arr) // we must explicitly specify <int, 5> here
    { std::cout << arr[0] << '\n'; }
    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD deduces type std::array<int, 5>
    passByRef(arr);
    // CTAD doesn’t (currently) work with function parameters

    template <typename T, std::size_t N> // note that this template parameter declaration matches the one for std::array
    void passByRef(const std::array<T, N>& arr) {}
    std::array arr{ 9, 7, 5, 3, 1 }; // use CTAD to infer std::array<int, 5>
    passByRef(arr);  // ok: compiler will instantiate passByRef(const std::array<int, 5>& arr)
    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
    passByRef(arr2); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)
    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // ok: compiler will instantiate passByRef(const std::array<double, 5>& arr)

    template <std::size_t N> // note: only the length has been templated here
    void passByRef(const std::array<int, N>& arr) {} // we've defined the element type as int
    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // error: compiler can't find matching function
}
{   // <----------- 17.4 ------------>
    struct House {
        int number{};
        int stories{};
        int roomsPerStory{};
    };
    constexpr std::array houses // use CTAD to deduce template arguments <House, 3>
    { House{ 13, 1, 7 }, House{ 14, 2, 5 }, House{ 15, 2, 4 } };

    // The compiler knows that each element of houses is a House
    // so it will implicitly convert the right hand side of each assignment to a House
    houses[0] = { 13, 1, 7 };
    houses[1] = { 14, 2, 5 };
    houses[2] = { 15, 2, 4 };

    // std::array is defined as a struct that contains a single C-style array member 
    template<typename T, std::size_t N>
    struct array
    { T implementation_defined_name[N]; } // a C-style array with N elements of type T

    // doesn't work
    constexpr std::array<House, 3> houses { // we're telling the compiler that each element is a House
        { 13, 1, 7 }, // but not mentioning it here
        { 14, 2, 5 },
        { 15, 2, 4 }
    };
    // This will initialize the C-style array element 0 with { 13, 1, 7 } and the rest of the members will be zero-initialized
    // Then the compiler will discover we’ve provided two more initialization values - error telling us that we’ve provided too many initialization values
    // This works as expected
    constexpr std::array<House, 3> houses { // initializer for houses
        { // extra set of braces to initialize the C-style array member with implementation_defined_name
            { 13, 4, 30 }, // initializer for array element 0
            { 14, 3, 10 }, // initializer for array element 1
            { 15, 3, 40 }, // initializer for array element 2
        }
    };
    constexpr std::array<House, 3> houses {{ // note double braces
        { 13, 1, 7 },
        { 14, 2, 5 },
        { 15, 2, 4 }
    }};
}
{   // <----------- 17.5 ------------>
    int x { 1 };
    int y { 2 };
    [[maybe_unused]] std::array<int&, 2> refarr { x, y }; // compile error: cannot define array of references
    int& ref1 { x };
    int& ref2 { y };
    [[maybe_unused]] std::array valarr { ref1, ref2 }; // ok: this is actually a std::array<int, 2>, not an array of references
    
    #include <functional> // for std::reference_wrapper
    int x { 1 }, y { 2 }, z { 3 };
    std::array<std::reference_wrapper<int>, 3> arr { x, y, z };
    arr[1].get() = 5; // modify the object in array element 1
    std::cout << arr[1] << y << '\n'; // show that we modified arr[1] and y, prints 55

    int x { 5 };
    auto ref { std::ref(x) };   // C++11, deduces to std::reference_wrapper<int>
    auto cref { std::cref(x) }; // C++11, deduces to std::reference_wrapper<const int>
}
{   // <----------- 17.6 ------------>
    // Ensure the number of test scores is the same as the number of students
    static_assert(std::size(testScores) == max_students); // compile error: static_assert condition failed
    // something 🫩
}
{   // <----------- 17.7 ------------>
    int testScore[30] {};   // Defines a C-style array named testScore that contains 30 value-initialized int elements (no include required)
    // error if the array length is zero, negative, or a non-integral value
    // C-style arrays dynamically allocated on the heap are allowed to have length 0.
    int arr1[5];    // Members default initialized int elements are left uninitialized)
    int arr2[5] {}; // Members value initialized (int elements are zero uninitialized) (preferred)
    int a[4] { 1, 2, 3, 4, 5 }; // compile error: too many initializers
    int b[4] { 1, 2 };          // arr[2] and arr[3] are value initialized
    auto squares[5] { 1, 4, 9, 16, 25 }; // compile error: can't use type deduction on C-style arrays
    const int prime2[] { 2, 3, 5, 7, 11 };  // prime2 deduced by compiler to have length 5
    
    constexpr int squares[5] { 1, 4, 9, 16, 25 }; // an array of constexpr int
    const int prime[5] { 2, 3, 5, 7, 11 }; // an array of const int
    prime[0] = 17; // compile error: can't change const int
    std::cout << sizeof(prime); // prints 20 (assuming 4 byte ints)
    
    #include <iterator> // for std::size and std::ssize
    std::cout << std::size(prime) << '\n';  // C++17, returns unsigned integral value 5
    std::cout << std::ssize(prime) << '\n'; // C++20, returns signed integral value 5

    template <typename T, std::size_t N>
    constexpr std::size_t length(const T(&)[N]) noexcept { return N; }
	int arr[]{ 1, 1, 2, 3, 5, 8, 13, 21 };
	std::cout << "The array has: " << length(arr) << " elements\n";
    arr[0] = 4;            // assignment to individual elements is fine
    arr = { 5, 6, 7 };     // compile error: array assignment not valid

    #include <algorithm> // for std::copy
    int arr[] { 1, 2, 3 };
    int src[] { 5, 6, 7 };
    // Copy src into arr
    std::copy(std::begin(src), std::end(src), std::begin(arr));
}
{   // <----------- 17.8 ------------>
    int arr[5]{ 9, 7, 5, 3, 1 }; // our array has elements of type int
    auto ptr{ arr }; // evaluation causes arr to decay, type deduction should deduce type int*
    // A decayed array pointer does not know length of array

    // In C++, there are a few common cases where an C-style array doesn’t decay:
    // When used as an argument to sizeof() or typeid().
    // When taking the address of the array using operator&.
    // When passed as a member of a class type.
    // When passed by reference.

    const int* ptr{ arr };  // arr decays into a pointer
    std::cout << ptr[2];    // subscript ptr to get element 2, prints 5

    void printElementZero(const int* arr) // pass by const address
    { std::cout << arr[0]; }
    void printElementZero(const int arr[]) // treated the same as const int*
    { std::cout << arr[0]; }

    int arr[]{ 3, 2, 1 };
    std::cout << sizeof(arr) << '\n'; // prints 12 (assuming 4 byte ints)
    void printArraySize(int arr[]){
        std::cout << sizeof(arr) << '\n'; // prints 4 (assuming 32-bit addresses)
        std::cout << std::size(arr) << '\n'; // compile error: std::size() won't work on a pointer
    }

    void printElement2(const int arr[], int length); // just pass the length
    constexpr int a[]{ 3, 2, 1 };
    printElement2(a, static_cast<int>(std::size(a)));  // ok

    // Avoid C-style arrays whenever practical.
    // Prefer std::string_view for read-only strings (string literal symbolic constants and string parameters).
    // Prefer std::string for modifiable strings.
    // Prefer std::array for non-global constexpr arrays.
    // Prefer std::vector for non-constexpr arrays.

    // Use C-style for :-
    // To store constexpr global (or constexpr static local) program data
    // parameters to functions or classes that want to handle non-constexpr C-style string arguments directly
}
{   // <----------- 17.9 ------------>
    const int arr[] { 9, 8, 7, 6, 5 };
    // Set ptr to point at element 3
    const int* ptr { &arr[3] };
    // Prove that we're pointing at element 3
    std::cout << *ptr << ptr[0] << '\n'; // prints 66
    // Prove that ptr[-1] is element 2!
    std::cout << *(ptr-1) << ptr[-1] << '\n'; // prints 77
    
	for (auto e : arr)         // iterate from `begin` up to (but excluding) `end`
	{ std::cout << e << ' '; } // dereference our loop variable to get the current element
}
{   // <----------- 17.10 ------------>
    char str1[8]{};                    // an array of 8 char, indices 0 through 7
    const char str2[]{ "string" };     // an array of 7 char, indices 0 through 6
    constexpr char str3[] { "hello" }; // an array of 6 const char, indices 0 through 5
    // extra character for the implicit null terminator
    char rolls[255] {}; // declare array large enough to hold 254 characters + null terminator
    std::cin.getline(rolls, std::size(rolls));

    char str[]{ "string" }; // ok
    str = "rope";           // not ok!
    str[1] = 'p';           // works

    char str[255]{ "string" }; // 6 characters + null terminator
    std::cout << "length = " << std::size(str) << '\n'; // prints length = 255
    char *ptr { str };
    std::cout << "length = " << std::size(ptr) << '\n'; // compile error

    #include <cstring> // for std::strlen (excluding null terminator)
    char str[255]{ "string" }; // 6 characters + null terminator
    std::cout << "length = " << std::strlen(str) << '\n'; // prints length = 6
    char *ptr { str };
    std::cout << "length = " << std::strlen(ptr) << '\n';   // prints length = 6
    // slow, as it has to traverse through the whole array
}
{   // <----------- 17.11 ------------>
    const char name[] { "Alex" };        // case 1: const C-style string initialized with C-style string literal
    const char* const color{ "Orange" }; // case 2: const pointer to C-style string literal
    auto s1{ "Alex" };  // type deduced as const char*
    auto* s2{ "Alex" }; // type deduced as const char*
    auto& s3{ "Alex" }; // type deduced as const char(&)[5]

    int narr[]{ 9, 7, 5, 3, 1 };
    char carr[]{ "Hello!" };
    const char* ptr{ "Alex" };
    std::cout << narr << '\n'; // narr will decay to type int*   // prints - 003A4923
    std::cout << carr << '\n'; // carr will decay to type char*  // prints - Hello!
    std::cout << ptr << '\n'; // name is already type char*      // prints - Alex
    // if you pass std::cout an object of type char* or const char*, it will assume you’re intending to print a string
    char c{ 'Q' };
    std::cout << &c; // prints Q╠╠╠╠╜╡4;¿■A - it has type char* and std::cout tries to print a string
    // first print 'Q', then bunch of garbage, till a memory holding value 0

    const char* ptr{ "Alex" };
    std::cout << ptr << '\n';                           // print ptr as C-style string
    std::cout << static_cast<const void*>(ptr) << '\n'; // print address held by ptr
    // Avoid C-style string symbolic constants in favor of constexpr std::string_view.
}
{   // <----------- 17.12 ------------>
    int a[3][5]; // a 3-element array of 5-element arrays of int
    int array[3][5]{
        { 1, 2 },          // row 0 = 1, 2, 0, 0, 0
        { 6, 7, 8 },       // row 1 = 6, 7, 8, 0, 0
        { 11, 12, 13, 14 } // row 2 = 11, 12, 13, 14, 0
    };
    // can omit (only) the leftmost length specification
    int array[][5]; // compiler can do the math to figure out what the leftmost length is from the number of initializers
    // Omitting non-leftmost dimensions is not allowed:
    int array[][]; // error

    constexpr int numRows{ 10 };
    constexpr int numCols{ 10 };
    // Declare a 10x10 array
    int product[numRows][numCols]{};
    // Calculate a multiplication table
    // We don't need to calc row and col 0 since mult by 0 always is 0
    for (std::size_t row{ 1 }; row < numRows; ++row)
        for (std::size_t col{ 1 }; col < numCols; ++col)
            product[row][col] = static_cast<int>(row * col);

    for (std::size_t row{ 1 }; row < numRows; ++row){
        for (std::size_t col{ 1 }; col < numCols; ++col)
            std::cout << product[row][col] << '\t';
        std::cout << '\n';
    }
}
{   // <----------- 17.13 ------------>
    std::array<std::array<int, 4>, 3> arr {{  // note double braces
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    }};

    // An alias template for a two-dimensional std::array
    template <typename T, std::size_t Row, std::size_t Col>
    using Array2d = std::array<std::array<T, Col>, Row>;
    // Array2d<int, 3, 4> - for a 3x4 array

    // An alias template for a three-dimensional std::array
    template <typename T, std::size_t Row, std::size_t Col, std::size_t Depth>
    using Array3d = std::array<std::array<std::array<T, Depth>, Col>, Row>;

    // Fetch the number of rows from the Row non-type template parameter
    template <typename T, std::size_t Row, std::size_t Col>
    constexpr int rowLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
    { return Row; }
}
    return 0;
}