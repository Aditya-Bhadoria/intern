#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
{   // <----------- 14.1 ------------>
    struct Date {
        int day{};
        int month{};
        int year{};
    };
    void printDate(const Date& date){
        std::cout << date.day << '/' << date.month << '/' << date.year; // assume DMY format
    }
    Date date{ 4, 10, 21 }; // initialize using aggregate initialization
    printDate(date);        // can pass entire struct to function
}
{   // <----------- 14.2 ------------>
}
{   // <----------- 14.3 ------------>
    struct Date {
        int year {};
        int month {};
        int day {};
        void print(){ // defines a member function named print
            std::cout << year << '/' << month << '/' << day;
        }
    };
    Date today { 2020, 10, 14 }; // aggregate initialize our struct
    today.day = 16; // member variables accessed using member selection operator (.)
    today.print();  // member functions also accessed using member selection operator (.)

    struct Foo{
        int z() { return m_data; } // We can access data members before they are defined
        int x() { return y(); }    // We can access member functions before they are defined

        int m_data { y() };        // This even works in default member initializers (see warning below)
        int y() { return 5; }
        // however
        /*Data members are initialized in order of declaration. If the initialization of a data member accesses another data member 
        that isn’t declared until later (and thus hasn’t been initialized yet), the initialization will result in undefined behavior.*/
        int m_bad1 { m_data }; // undefined behavior: m_bad1 initialized before m_data
        int m_bad2 { fcn() };  // undefined behavior: m_bad2 initialized before m_data (accessed through fcn())

        int m_data { 5 };
        int fcn() { return m_data; }
    };

    struct Foo{
        int z() { return m_data; } // m_data not declared yet
        int x() { return y(); }    // y not declared yet
        int y() { return 5; }
        int m_data{};
    };
    // It will compile the equivalent of this:
    // member function is implicitly forward declared, definition is moved immediately after the end of the class definition
    struct Foo{
        int z(); // forward declaration of Foo::z()
        int x(); // forward declaration of Foo::x()
        int y(); // forward declaration of Foo::y()
        int m_data{};
    };
    int Foo::z() { return m_data; } // m_data already declared above
    int Foo::x() { return y(); }    // y already declared above
    int Foo::y() { return 5; }
}
{   // <----------- 14.4 ------------>
    struct Date{
        int year {};
        int month {};
        int day {};
        void incrementDay() { ++day; }
        void print() {}
        void print2() const { // now a const member function
            ++day; // compile error: const function can't modify member, call non-const member functions
            // they can modify non-members and call non-member functions per usual
        }
    };
    const Date today { 2020, 10, 14 }; // const class type object
    today.day += 1;        // compile error: can't modify member of const object
    today.incrementDay();  // compile error: can't call member function that modifies member of const object
    today.print();  // compile error: const object can't call non-const member function
    today.print2();  // ok: const object can call const member function
    Date today2 { 2020, 10, 14 }; // non-const
    today2.print2();  // ok: can call const member function on non-const object

    struct Something {
        void print() { std::cout << "non-const "; }
        void print() const { std::cout << "const "; }
    };
    Something s1{};
    s1.print(); // calls print()
    const Something s2{};
    s2.print(); // calls print() const
    // prints - non-const const
}
{   // <----------- 14.5 ------------>
    // public private bs
}
{   // <----------- 14.6 ------------>
    // getter setter bs
}
{   // <----------- 14.7 ------------>
    class Employee{
        std::string m_name{};
    public:
        void setName(std::string_view name) { m_name = name; }
        const std::string& getName() const { return m_name; } //  getter returns by const reference
    };
	Employee joe{}; // joe exists until end of function
	joe.setName("Joe");
	std::cout << joe.getName(); // returns joe.m_name by reference

    // createEmployee() returns an Employee by value (which means the returned value is an rvalue)
    Employee createEmployee(std::string_view name){
        Employee e;
        e.setName(name);
        return e;
    }
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName();
	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref; // undefined behavior
	// Case 3: okay: copy referenced value to local variable for use later
	std::string val { createEmployee("Hans").getName() }; // makes copy of referenced member
	std::cout << val; // okay: val is independent of referenced member

    class Foo {
    private:
        int m_value{ 4 }; // private member
    public:
        int& value() { return m_value; } // returns a non-const reference (don't do this)
    };
    Foo f{};                // f.m_value is initialized to default value 4
    f.value() = 5;          // The equivalent of m_value = 5, able to change a private member
    std::cout << f.value(); // prints 5
}
{   // <----------- 14.8 ------------>
    // Allows to maintain invariants
    class Employee { // members are private by default
        std::string m_name{};
        char m_firstInitial{};
    public:
        void setName(std::string_view name){
            m_name = name;
            m_firstInitial = name.front(); // use std::string::front() to get first letter of `name`
        }
        void print() const {}
    };
    Employee e{};
    e.setName("John");
    e.print();
    e.setName("Mark");
    e.print();

    // Allows to change implementation details without breaking existing programs
    class Something{
    private:
        int m_value1 {};
        int m_value2 {};
        int m_value3 {};
    public:
        void setValue1(int value) { m_value1 = value; }
        int getValue1() const { return m_value1; }
    };
    // changed to
    class Something{
    private:
        int m_value[3]; // note: we changed the implementation of this class!
    public:
        // We have to update any member functions to reflect the new implementation
        void setValue1(int value) { m_value[0] = value; }
        int getValue1() const { return m_value[0]; }
    };

    class Yogurt {
        std::string m_flavor{ "vanilla" };
    public:
        const std::string& getFlavor() const { return m_flavor; }
        // Worst: member function print() uses direct access to m_flavor when getter exists
        void print() const {
            std::cout << "The yogurt has flavor " << m_flavor << '\n';
        }
        // Better: member function print() has no direct access to members
        void print(std::string_view prefix) const {
            std::cout << prefix << ' ' << getFlavor() << '\n';
        }
    };
    // Best: non-member function print() is not part of the class interface
    void print(const Yogurt& y) {
        std::cout << "The yogurt has flavor " << y.getFlavor() << '\n';
    }
    // Declare public members first, protected members next, and private members last. 
    // This spotlights the public interface and de-emphasizes implementation details.
}
{   // <----------- 14.9 ------------>
    class Foo // Foo is not an aggregate (has private members)
    { int m_x {}; int m_y {}; };
    Foo foo { 6, 7 }; // compile error: can not use aggregate initialization

    class Foo {
    public:
        Foo(int x, int y) {} // constructors must be non-const
    };
    Foo foo{ 'a', true }; // will match Foo(int, int) constructor
    const Something s{}; // const object, implicitly invokes (non-const) constructor
}
{   // <----------- 14.10 ------------>
    Foo(int x, int y)
        : m_x { x }, m_y { y } // here's our member initialization list
    { std::cout << "Foo(" << x << ", " << y << ") constructed\n"; }

    // members in a member initializer list are always initialized in the order in which they are
    // defined inside the class (not in the order they are defined in the member initializer list).
    class Foo {
    private:
        int m_x{}; int m_y{};
    public:
        Foo(int x, int y)
            : m_y { std::max(x, y) }, m_x { m_y } // issue on this line
        {} // as m_x is defined first, its initialized first
        void print() const {}
    };
    Foo foo { 6, 7 };
    foo.print(); // prints (garbage, 7)

    private:
        int m_x {};    // default member initializer (will be ignored)
        int m_y { 2 }; // default member initializer (will be used)
        int m_z;      // no initializer
    public:
        Foo(int x) : m_x { x } // member initializer list
        {}
        void print() const {}
    Foo foo { 6 }; // prints (6, 2, garbage)

    // Once the member initializer list has finished executing, the object is considered initialized
    Foo(int x, int y){
        m_x = x; // incorrect: this is an assignment, not an initialization
        m_y = y; // incorrect: this is an assignment, not an initialization
    }
    // Although throw exceptions best, for now we use optional
    class Fraction {
    private:
        int m_numerator { 0 };
        int m_denominator { 1 };
        // private constructor can't be called by public
        Fraction(int numerator, int denominator):
            m_numerator { numerator }, m_denominator { denominator }
        {}
    public:
        // Allow this function to access private members
        friend std::optional<Fraction> createFraction(int numerator, int denominator);
    };
    std::optional<Fraction> createFraction(int numerator, int denominator){
        if (denominator == 0) return {};
        return Fraction{numerator, denominator};
    }
    auto f1 { createFraction(0, 1) };
    if (f1) { std::cout << "Fraction created\n"; }
    auto f2 { createFraction(0, 0) };
    if (!f2) { std::cout << "Bad fraction\n"; }
}
{   // <----------- 14.11 ------------>
    Foo() // default constructor
    { std::cout << "Foo default constructed\n"; }
    Foo(int x, int y) : m_x { x }, m_y { y } // non-default constructor
    { std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n"; }
    Foo foo{}; // No initialization values, calls Foo's default constructor
    Foo foo2{6, 7}; // Calls Foo(int, int) constructor

    // If all of the parameters in a constructor have default arguments, the
    // constructor is a default constructor (because it can be called with no arguments).
    Foo(int x=0, int y=0) : m_x { x }, m_y { y } {} // has default arguments

    Foo() {} // default constructor
    Foo(int x=1, int y=2) : m_x { x }, m_y { y } {} // default constructor
    Foo foo{}; // compile error: ambiguous constructor function call

    // If no user-declared constructors, compiler will generate a public default constructor
    // (so that the class can be value or default initialized). It's called an implicit default constructor.
    public:
        Foo() {} // implicitly generated default constructor

    Foo() = default; // generates an explicitly defaulted default constructor
    Foo(int x, int y) : m_x { x }, m_y { y } {}
    Foo foo{}; // calls Foo() default constructor

    int m_a;
    int m_b {};
    public:
        User() {} // user-defined empty constructor
    public:
        Default() = default; // explicitly defaulted default constructor
    public:
        // implicit default constructor
    User user{}; // default initialized
    std::cout << user.a() << ' ' << user.b() << '\n';
    Default def{}; // zero initialized, then default initialized
    std::cout << def.a() << ' ' << def.b() << '\n';
    Implicit imp{}; // zero initialized, then default initialized
    std::cout << imp.a() << ' ' << imp.b() << '\n';
    // prints (garbage, 0) (0, 0) (0, 0)

    public:
        Employee(std::string_view name, int id)
            : m_name{ name }
            , m_id{ id }
        {}
    Employee e2 {}; // compile error: no matching constructor
}
{   // <----------- 14.12 ------------>
    Employee(std::string_view name, int id) // Employees must have a name and an id
        : m_name{ name }, m_id { id }
    { std::cout << "Employee " << m_name << " created\n"; }
    Employee(std::string_view name, int id, bool isManager) // They can optionally be a manager
        : m_name{ name }, m_id{ id }, m_isManager { isManager }
    { std::cout << "Employee " << m_name << " created\n"; }
    // too much code, change to :-
    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id } // this constructor initializes name and id
    {}
    Employee(std::string_view name, int id, bool isManager)
        : m_isManager { isManager } // this constructor initializes m_isManager
    {
        // Call Employee(std::string_view, int) to initialize m_name and m_id
        Employee(name, id); // this doesn't work as expected!
        // creates a temporary obj
    }
    // what to do?
    Employee(std::string_view name)
        : Employee{ name, 0 } // delegate initialization to Employee(std::string_view, int) constructor
    {}
    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id } // actually initializes the members
    { std::cout << "Employee " << m_name << " created\n"; }
    // OR
    Employee(std::string_view name, int id = 0) // default argument for id
        : m_name{ name }, m_id{ id } {}
}
{   // <----------- 14.13 ------------>
    void print(IntPair p){ std::cout << "(" << p.x() << ", " << p.y() << ")\n"; }
    // Case 1: Pass variable
    IntPair p { 3, 4 };
    print(p);
    // Case 2: Construct temporary IntPair and pass to function
    print(IntPair { 5, 6 } );
    // Case 3: Implicitly convert { 7, 8 } to a temporary Intpair and pass to function
    print( { 7, 8 } );

    Foo (1, 2); // temporary Foo, direct-initialized with (1, 2) (similar to `Foo { 1, 2 }`)

    Foo * bar();  /* (with no additional parenthesis) groups the * with Foo by default. 
            Foo* bar(); is the declaration of a function named bar that has no parameters and returns a Foo*. */
    Foo (*bar)(); /* explicitly groups the * with bar. This defines a function pointer named bar that
            holds the address of a function that takes no parameters and returns a Foo. */
    Foo (* bar()); // is the same as Foo * bar(); -- the parentheses are superfluous in this case.
    (Foo *) bar(); /* You might expect this to be the same as Foo* bar(), but this is actually an expression statement
            that calls function bar(), C-style casts the return value to type Foo*, and then discards it! */
    
    // Case 1: Create named variable and return
    IntPair ret1(){
        IntPair p { 3, 4 };
        return p; // returns temporary object (initialized using p)
    }
    // Case 2: Create temporary IntPair and return
    // returns temporary object (initialized using another temporary object)
    IntPair ret2() { return IntPair { 5, 6 }; }
    // Case 3: implicitly convert { 7, 8 } to IntPair and return
    // returns temporary object (initialized using another temporary object)
    IntPair ret3() { return { 7, 8 }; }
}
{   // <----------- 14.14 ------------>
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {}
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // What constructor is used here?
    f.print();      // prints 5,3
    fCopy.print();  // prints 5,3

    // Copy constructor
    Fraction(const Fraction& fraction)
        // Initialize our members using the corresponding member of the parameter
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n"; // just to prove it works
    }
    void printFraction(Fraction f) // f is pass by value
    { f.print(); }
    Fraction generateFraction(int n, int d){
        Fraction f{ n, d };
        return f;
    }
    Fraction f2 { generateFraction(1, 2) }; // Fraction is returned using copy constructor
    printFraction(f2); // f2 is copied into the function parameter using copy constructor

    // Explicitly request default copy constructor
    Fraction(const Fraction& fraction) = default;
    // Delete the copy constructor so no copies can be made
    Fraction(const Fraction& fraction) = delete;
}
{   // <----------- 14.15 ------------>
    // Default constructor
    Foo() {}
    // Normal constructor
    Foo(int x) {}
    // Copy constructor
    Foo(const Foo&) {}
    // Calls Foo() default constructor
    Foo f1;           // default initialization
    Foo f2{};         // value initialization (preferred)

    // Calls foo(int) normal constructor
    Foo f3 = 3;       // copy initialization (non-explicit constructors only)
    Foo f4(4);        // direct initialization
    Foo f5{ 5 };      // direct list initialization (preferred)
    Foo f6 = { 6 };   // copy list initialization (non-explicit constructors only)

    // Calls foo(const Foo&) copy constructor
    Foo f7 = f3;      // copy initialization
    Foo f8(f3);       // direct initialization
    Foo f9{ f3 };     // direct list initialization (preferred)
    Foo f10 = { f3 }; // copy list initialization

    // Copy elision is a compiler optimization technique that allows the compiler to remove unnecessary copying of objects
    class Something{
    public:
        Something() = default;
        Something(const Something&) { std::cout << "Copy constructor called\n"; }
    };
    Something rvo() {
        return Something{}; // calls Something() and copy constructor
    }
    Something nrvo(){
        Something s{}; // calls Something()
        return s;      // calls copy constructor
    }
	std::cout << "Initializing s1\n";
	Something s1 { rvo() }; // calls copy constructor
	std::cout << "Initializing s2\n";
	Something s2 { nrvo() }; // calls copy constructor
    // In C++14 or older, with copy elision disabled, this would call copy constructor 4 times
    // GCC elides all 4
    // Visual Studio 2022 elides 3 cases (doesn’t elide nrvo() returns by value)
}
{   // <----------- 14.16 ------------>
    Foo(int x) : m_x{ x } {}
    void printFoo(Foo f) { std::cout << f.getX(); } // has a Foo parameter
    printFoo(5); // Implicitly convert int value 5 into a Foo
    
    Employee(std::string_view name) : m_name{ name } {}
    void printEmployee(Employee e) { std::cout << e.getName(); } // has an Employee parameter
    printEmployee("Joe"); // we're supplying an string literal argument
    // compile err - only one user-defined conversion may be applied to perform an implicit conversion
    // here's 2, C string to sv, and sv to Employee

    // explicit - constructor should not be used as a converting constructor.
    explicit Dollars(int d) : m_dollars{ d } {} // now explicit
    print(5); // compilation error because Dollars(int) is explicit
    Dollars d1(5); // ok
    print(Dollars{5}); // ok: explicitly create a Dollars

    explicit Foo() {} // note: explicit (just for sake of example)
    explicit Foo(int x) {} // note: explicit
    Foo getFoo(){
        // explicit Foo() cases
        return Foo{ };   // ok
        return { };      // error: can't implicitly convert initializer list to Foo

        // explicit Foo(int) cases
        return 5;        // error: can't implicitly convert int to Foo
        return Foo{ 5 }; // ok
        return { 5 };    // error: can't implicitly convert initializer list to Foo
    }
}
{   // <----------- 14.17 ------------>
    struct Pair{
        int m_x {};
        int m_y {};
        int greater() const{
            return (m_x > m_y  ? m_x : m_y);
        }
    };
    Pair p { 5, 6 };                  // inputs are constexpr values
    constexpr int g { p.greater() };  // compile error: greater() not constexpr

    constexpr int greater() const {} // can evaluate at either compile-time or runtime
    Pair p { 5, 6 };
    constexpr int g { p.greater() };  // compile error: p not constexpr
    constexpr Pair p2 { 5, 6 };        // now constexpr
    std::cout << p2.greater() << '\n'; // p.greater() evaluates at runtime or compile-time
    constexpr int g { p2.greater() };  // p.greater() must evaluate at compile-time

    class Pair { // Pair is no longer an aggregate
    private:
        int m_x {};
        int m_y {};
    public:
        Pair(int x, int y): m_x { x }, m_y { y } {}
        constexpr int greater() const { return (m_x > m_y  ? m_x : m_y); }
    };
    constexpr Pair p { 5, 6 }; // compile error: p is not a literal type
    // no longer an aggregate (due to having private data members and a constructor).

    // make your member functions and constructor constexpr
    class Pair {
    private:
        int m_x {};
        int m_y {};
    public:
        constexpr Pair(int x, int y): m_x { x }, m_y { y } {} // now constexpr
        constexpr int greater() const { return (m_x > m_y  ? m_x : m_y); } // this too
    };
    constexpr Pair p { 5, 6 }; // works!!

    class Pair {
    public:
        constexpr int greater() const {} // constexpr and const
        constexpr void reset() // constexpr but non-const
        { m_x = m_y = 0; } // non-const member function can change members
        constexpr const int& getX() const { return m_x; }
        // The constexpr indicates that the member function can be evaluated at compile-time. 
        // The const int& is the return type of the function. 
        // The rightmost const means the member-function itself is const so it can be called on const objects.
    };
    // This function is constexpr
    constexpr Pair zero(){
        Pair p { 1, 2 }; // p is non-const
        p.reset();       // okay to call non-const member function on non-const object
        return p;
    }
    Pair p1 { 3, 4 };
    p1.reset();                     // okay to call non-const member function on non-const object
    std::cout << p1.getX() << '\n'; // prints 0

    Pair p2 { zero() };             // zero() will be evaluated at runtime
    p2.reset();                     // okay to call non-const member function on non-const object
    std::cout << p2.getX() << '\n'; // prints 0

    constexpr Pair p3 { zero() };   // zero() will be evaluated at compile-time
    //  p3.reset();                 // Compile error: can't call non-const member function on const object

    // A member function that returned a const pointer to const
    constexpr const int* const getXPtr() const { return &m_x; }
}
    return 0;
}