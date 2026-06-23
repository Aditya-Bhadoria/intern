#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    // !!!!!!!!!!! VERY IMP BUT NOT ASKED MUCH !!!!!!!!!!!!

{   // <----------- 16.1 ------------>
    // not considered to be containers by the C++ standard: C-style arrays, std::string, std::vector<bool>
}
{   // <----------- 16.2 ------------>
	// Value initialization (uses default constructor)
	std::vector<int> empty{}; // vector containing 0 int elements
	// List construction (uses list constructor)
	std::vector<int> primes{ 2, 3, 5, 7 };          // vector containing 4 int elements with values 2, 3, 5, and 7
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o', and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).

    // Copy init
    std::vector<int> v1 = 10;     // 10 not an initializer list, copy init won't match explicit constructor: compilation error
    // Direct init
    std::vector<int> v2(10);      // 10 not an initializer list, matches explicit single-argument constructor
    // List init
    std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor
    // Copy list init
    std::vector<int> v4 = { 10 }; // { 10 } interpreted as initializer list, matches list constructor
    std::vector<int> v5({ 10 });  // { 10 } interpreted as initializer list, matches list constructor
    // Default init
    std::vector<int> v6 {};       // {} is empty initializer list, matches default constructor
    std::vector<int> v7 = {};     // {} is empty initializer list, matches default constructor

    // When a std::vector is a member of a class type
    struct Foo{
        std::vector<int> v1(8); // compile error: direct initialization not allowed for member default initializers
        std::vector<int> v{ std::vector<int>(8) }; // ok
    };
    const std::vector<int> prime { 2, 3, 5, 7, 11 }; // prime and its elements cannot be modified
}
{   // <----------- 16.3 ------------>
    std::cout << "length: " << prime.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
    std::cout << "length: " << std::size(prime); // C++17, returns length as type `size_type` (alias for `std::size_t`)
    std::cout << "length: " << std::ssize(prime); // C++20, returns length as a large signed integral type
    
    std::vector prime{ 2, 3, 5, 7, 11 };
    std::cout << prime[3];  // print the value of element with index 3 (7)
    std::cout << prime[9]; // invalid index (undefined behavior)
    std::cout << prime.at(3); // print the value of element with index 3
    std::cout << prime.at(9); // invalid index (throws exception)
    std::cout << prime[3] << '\n';     // okay: 3 converted from int to std::size_t, not a narrowing conversion
    int index { 3 };                   // non-constexpr
    std::cout << prime[index] << '\n'; // possible warning: index implicitly converted to std::size_t, narrowing conversion
}
{   // <----------- 16.4 ------------>
    void passByRef(const std::vector& arr){} // compile error: CTAD can't be used to infer function parameters

    template <typename T>
    void passByRef(const T& arr){} // will accept any type of object that has an overloaded operator[]
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)
    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)
    void passByRef(const auto& arr){} // abbreviated function template
}
{   // <----------- 16.5 ------------>
    // something in the way
}
{   // <----------- 16.6 ------------>
    // something in the way
}
{   // <----------- 16.7 ------------>
    template <typename T>
    void printArray(const std::vector<T>& arr){
        // typename keyword prefix required for dependent type
        for (typename std::vector<T>::size_type index { 0 }; index < arr.size(); ++index)
            std::cout << arr[index] << ' ';
    }
    // decltype keyword - returns the type of its parameter
    // arr is some non-reference type
    for (decltype(arr)::size_type index { 0 }; index < arr.size(); ++index) // decltype(arr) resolves to std::vector<int>
    // But when arr passed as reference
    template <typename T>
    void printArray(const std::vector<T>& arr){
        // arr can be a reference or non-reference type
        for (typename std::remove_reference_t<decltype(arr)>::size_type index { 0 }; index < arr.size(); ++index)
            std::cout << arr[index] << ' ';
    }
    // std::ptrdiff_t - signed counterpart to std::size_t
    using Index = std::ptrdiff_t;
    for (Index index{ 0 }; index < static_cast<Index>(arr.size()); ++index) // Sample loop using index
    // Z suffix can be used to define a literal of the type that is the signed counterpart to std::size_t (probably std::ptrdiff_t)
    for (auto index{ 0Z }; index < static_cast<std::ptrdiff_t>(arr.size()); ++index)

    auto length { static_cast<Index>(arr.size()) };  // in C++20, prefer std::ssize()
    for (auto index{ length - 1 }; index >= 0; --index)
        std::cout << arr.data()[index] << ' ';       // use data() to avoid sign conversion warning
}
{   // <----------- 16.8 ------------>
    for (int num : fibonacci) // iterate over array fibonacci and copy each value into `num`
       std::cout << num << ' '; // print the current value of `num`

    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    for (auto num : fibonacci) // compiler will deduce type of num to be `int`
       std::cout << num << ' ';
    for (const auto& word : words) // word is now a const reference
        std::cout << word << ' ';
    for (const auto& word : std::views::reverse(words)) // create a reverse view
        std::cout << word << ' ';
}
{   // <----------- 16.9 ------------>
    namespace Students{
        enum Names{
            kenny, // 0
            kyle, // 1
            stan, // 2
            butters, // 3
            cartman, // 4
            max_students // 5
        };
    }
    std::vector testScores { 78, 94, 66, 77, 14 };
    testScores[Students::stan] = 76; // we are now updating the test score belonging to stan
    Students::Names name { Students::stan }; // non-constexpr
    testScores[name] = 76; // may trigger a sign conversion warning if Student::Names defaults to a signed underlying type

    enum Names : unsigned int // explicitly specifies the underlying type is unsigned int
    { /*code*/ };
    Students::Names name { Students::stan }; // non-constexpr
    testScores[name] = 76; // not a sign conversion since name is unsigned

    namespace Students{
        enum Names{
            kenny, // 0
            kyle, // 1
            stan, // 2
            butters, // 3
            cartman, // 4
            // add future enumerators here
            max_students // 5
        };
    }
    std::cout << "The class has " << Students::max_students << " students\n";
    // Ensure the number of test scores is the same as the number of students
    assert(std::size(testScores) == Students::max_students);
    // If your array is constexpr, then you should static_assert instead. std::vector doesn’t support constexpr, but std::array (and C-style arrays) do.

    enum class StudentNames { // now an enum class{
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
    // compile error: no conversion from StudentNames to std::size_t
    std::vector<int> testScores(StudentNames::max_students);
    // compile error: no conversion from StudentNames to std::size_t
    testScores[StudentNames::stan] = 76;
    // compile error: no conversion from StudentNames to any type that operator<< can output
    std::cout << "The class has " << StudentNames::max_students << " students\n";
    // Fix -> we can static_cast the enumerator to an integer
    // OR
    // Overload the unary + operator to convert StudentNames to the underlying type
    constexpr auto operator+(StudentNames a) noexcept {
        return static_cast<std::underlying_type_t<StudentNames>>(a);
    }
    std::vector<int> testScores(+StudentNames::max_students);
    testScores[+StudentNames::stan] = 76;
    std::cout << "The class has " << +StudentNames::max_students << " students\n";
}
{   // <----------- 16.10 ------------>
    // Both std::array and C-style arrays are fixed-size array types
    v.resize(5);              // resize to 5 elements
    // Vector indexing is based on length, not capacity
    void printCapLen(const std::vector<int>& v){
        std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
    }
	std::vector<int> v(1000); // allocate room for 1000 elements
	printCapLen(v); // 1000, 1000
	v.resize(0); // resize to 0 elements
	printCapLen(v); // 1000, 0
	v.shrink_to_fit(); // tries to reduce capacity to len, may ignore it or partially reduce capacity
	printCapLen(v); // 0, 0
    // GCC and Clang doubles the current capacity, when pushing triggers reallocation
    // Visual Studio 2022 multiplies the current capacity by 1.5
	stack.reserve(6); // reserve space for 6 elements (but do not change length)
	stack.push_back(1); // {1}       len = 1, cap = 6
	stack.push_back(2); // {1, 2}    len = 2, cap = 6
	stack.push_back(3); // {1, 2, 3} len = 3, cap = 6
    // resize() member function changes the length of the vector, and the capacity (if necessary).

    class Foo{
    private:
        std::string m_a{};
        int m_b{};
    public:
        Foo(std::string_view a, int b) : m_a { a }, m_b { b } {}
        explicit Foo(int b) : m_a {}, m_b { b } {};
    };
	std::vector<Foo> stack{};
	// When we already have an object, push_back and emplace_back are similar in efficiency
	Foo f{ "a", 2 };
	stack.push_back(f);    // prefer this one
	stack.emplace_back(f);
	// When we need to create a temporary object to push, emplace_back is more efficient
	stack.push_back({ "a", 2 }); // creates a temporary object, and then copies it into the vector
	stack.emplace_back("a", 2);  // forwards the arguments so the object can be created directly in the vector (no copy made)
	// push_back won't use explicit constructors, emplace_back will
	stack.push_back({ 2 }); // compile error: Foo(int) is explicit (stops implicit conversions)
	stack.emplace_back(2);  // ok
}
{   // <----------- 16.11 ------------>
    // something in the way
}
{   // <----------- 16.12 ------------>
    // std::vector<bool> is not a vector (not required to be contiguous in memory)
    // nor does it hold bool values (holds a collection of bits), nor does it meet C++’s definition of a container
    // prefer not to use it, use bitset or vector<char> or 3rd party dynamic bitsets instead
}
    return 0;
}