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
    
}
{   // <----------- 14.12 ------------>

}
{   // <----------- 14.13 ------------>

}
{   // <----------- 14.14 ------------>

}
{   // <----------- 14.15 ------------>

}
{   // <----------- 14.16 ------------>

}
{   // <----------- 14.17 ------------>

}
    return 0;
}