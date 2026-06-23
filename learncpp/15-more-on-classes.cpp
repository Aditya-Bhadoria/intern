#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
{   // <----------- 15.1 ------------>
    void print() const { std::cout << m_id; }       // implicit use of this
    void print() const { std::cout << this->m_id; } // explicit use of this

    simple.setID(2); // when complied changed to -
    Simple::setID(&simple, 2); // note that simple has been changed from an object prefix to a function argument!
    void setID(int id) { m_id = id; }
    static void setID(Simple* const this, int id) { this->m_id = id; }
    Simple b{2}; // this = &b inside the Simple constructor
    a.setID(3); // this = &a inside member function setID()

    struct Something {
        int data{}; // not using m_ prefix because this is a struct
        void setData(int data) {
            this->data = data; // this->data is the member, data is the local parameter
        }
    };

    std::cout << "Hello, " << userName; // evaluates to
    (std::cout << "Hello, ") << userName; // after printing hello, it goes
    (std::cout) << userName; // operator<< returns the stream object that was passed in
    public:
        Calc& add(int value) { m_value += value; return *this; }
        Calc& sub(int value) { m_value -= value; return *this; }
        Calc& mult(int value) { m_value *= value; return *this; }
        int getValue() const { return m_value; }
        void reset() { *this = {}; } // value initialize a new object and overwrite the implicit object
    Calc calc{};
    calc.add(5).sub(3).mult(4); // method chaining
    std::cout << calc.getValue() << '\n'; // (((0 + 5) - 3) * 4)
    calc.reset();
    std::cout << calc.getValue() << '\n'; // prints 0
    // With const member functions, this is a const pointer to a const value
    // Attempting to call a non-const member function on a const object generate error :-
    // 'int Something::getValue(void)': cannot convert 'this' pointer from 'const Something' to 'Something &'
}
{   // <----------- 15.2 ------------>
    class Date {
    public:
        Date(int year, int month, int day); // constructor declaration
        void print() const; // print function declaration
    };
    Date::Date(int year, int month, int day) // constructor definition
        : m_year{ year }, m_month{ month }, m_day{ day }
    {}
    void Date::print() const { // print function definition
        std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
    };
    // Member functions defined inside the class definition are implicitly inline, thus exempt from (ODR) one-definition rule.
}
{   // <----------- 15.3 ------------>
    class Fruit{
    public:
        enum Type { apple, banana, cherry };
    private:
        Type m_type {};
        int m_percentageEaten { 0 };
    public:
        Fruit(Type type) : m_type { type } {}
        Type getType() { return m_type;  }
        int getPercentageEaten() { return m_percentageEaten;  }
        bool isCherry() { return m_type == cherry; } // Inside members of Fruit, we no longer need to prefix enumerators with FruitType::
    };
	// Note: Outside the class, we access the enumerators via the Fruit:: prefix now
    Fruit apple { Fruit::apple };
    if (apple.getType() == Fruit::apple) std::cout << "I am an apple";
    else std::cout << "I am not an apple";

    class Employee{
    public:
        using IDType = int;
        class Printer {
        public:
            void print(const Employee& e) const {
                // Printer can't access Employee's `this` pointer
                // so we can't print m_name and m_id directly
                // Instead, we have to pass in an Employee object to use
                // Because Printer is a member of Employee,
                // we can access private members e.m_name and e.m_id directly
                std::cout << e.m_name << " has id: " << e.m_id << '\n';
            }
        };
    };
    
    class outer;         // okay: can forward declare non-nested type
    class outer::inner1; // error: can't forward declare nested type prior to outer class definition
    class outer{
    public:
        class inner1;   // okay: forward declaration inside the enclosing class okay
        class inner1{}; // okay: definition of forward declared type inside the enclosing class
        class inner2;   // okay: forward declaration inside the enclosing class okay
    };
    class outer::inner1; // okay (but redundant) since nested type has already been declared as part of outer class definition
}
{   // <----------- 15.4 ------------>
    ~Simple() // here's our destructor
    { std::cout << "Destructing Simple " << m_id << '\n'; }
    int main(){
        // Allocate a Simple
        Simple simple1{ 1 };
        { Simple simple2{ 2 }; } // simple2 dies here
        return 0;
    } // simple1 dies here

	~NetworkData() { sendData(); } // make sure all data is sent before object is destroyed
}
{   // <----------- 15.5 ------------>
    template <typename T>
    struct Pair {
        T first{};
        T second{};
    };
    // Here's a deduction guide for our Pair (required in C++17 or older)
    // Pair objects initialized with arguments of type T and T should deduce to Pair<T>
    template <typename T>
    Pair(T, T) -> Pair<T>;
    Pair<int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    Pair<double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    Pair<double> p3{ 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    
    template <typename T>
    class Pair {
    private:
        T m_first{};
        T m_second{};
    public:
        // When we define a member function inside the class definition,
        // the template parameter declaration belonging to the class applies
        Pair(const T& first, const T& second) : m_first{ first } , m_second{ second } {}
        bool isEqual(const Pair<T>& pair);
    };
    // When we define a member function outside the class definition,
    // we need to resupply a template parameter declaration
    template <typename T>
    bool Pair<T>::isEqual(const Pair<T>& pair) // note the parameter has type Pair, not Pair<T>
    { /*code*/ }
    Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>
    std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
    std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';
}
{   // <----------- 15.6 ------------>
    struct Something {
        static int s_value; // declare s_value as static (initializer moved below)
    };
    int Something::s_value{ 1 }; // define and initialize s_value to 1 (we'll discuss this section below)
    Something first{};
    Something second{};
    first.s_value = 2;
    std::cout << first.s_value << " " << second.s_value << '\n'; // prints 2 2
    // static members are global variables that live inside the scope region of the class
    // not subject to access controls
    // note: we're not instantiating any objects of type Something
    Something::s_value = 2;
    std::cout << Something::s_value << '\n';

    class Whatever{
    public:
        static const int s_value{ 4 }; // a static const int can be defined and initialized directly
        static inline int s_value{ 4 }; // a static inline variable can be defined and initialized directly
        static constexpr double s_value{ 2.2 }; // ok
        static constexpr std::string_view s_view{ "Hello" }; // this even works for classes that support constexpr initialization
        
        auto m_x { 5 };           // auto not allowed for non-static members
        std::pair m_v { 1, 2.3 }; // CTAD not allowed for non-static members
        static inline auto s_x { 5 };           // auto allowed for static members
        static inline std::pair s_v { 1, 2.3 }; // CTAD allowed for static members
    };
}
{   // <----------- 15.7 ------------>
    private: // now private
        static inline int s_value { 1 };
    std::cout << Something::s_value; // error: s_value is private and can't be accessed directly outside the class
    public:
        static int getValue() { return s_value; } // static member function
    std::cout << Something::getValue() << '\n';
    // pure static classes - (also called “monostates) - all static members
    // static class is preferable if static data members and/or need access controls. Otherwise, prefer a namespace.

    struct Chars {
        char first{}; char second{}; char third{}; char fourth{}; char fifth{};
    };
    struct MyClass {
        static inline Chars s_mychars { 'a', 'e', 'i', 'o', 'u' }; // initialize static variable at point of definition
    };
    std::cout << MyClass::s_mychars.third; // print i
}
{   // <----------- 15.8 ------------>
    class Accumulator{
    private:
        int m_value { 0 };
    public:
        void add(int value) { m_value += value; }
        // Here is the friend declaration that makes non-member function void print(const Accumulator& accumulator) a friend of Accumulator
        friend void print(const Accumulator& accumulator);
    };
    void print(const Accumulator& accumulator){
        // Because print() is a friend of Accumulator
        // it can access the private members of Accumulator
        std::cout << accumulator.m_value;
    }
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator
    print(acc); // call the print() non-member function

    public:
        // Friend functions defined inside a class are non-member functions
        friend void print(const Accumulator& accumulator){
            // Because print() is a friend of Accumulator
            // it can access the private members of Accumulator
            std::cout << accumulator.m_value;
        }
    print(acc); // call the print() non-member function
    
    public:
        bool isEqualToMember(const Value& v) const;
        friend bool isEqualToNonmember(const Value& v1, const Value& v2);
    bool Value::isEqualToMember(const Value& v) const { return m_value == v.m_value; }
    bool isEqualToNonmember(const Value& v1, const Value& v2) { return v1.m_value == v2.m_value; }
    std::cout << v1.isEqualToMember(v2) << '\n';
    std::cout << isEqualToNonmember(v1, v2) << '\n';
    
    // Multiple friends 
    class Humidity; // forward declaration of Humidity
    class Temperature {
        friend void printWeather(const Temperature& temperature, const Humidity& humidity); // forward declaration needed for this line
    };
    class Humidity {
        friend void printWeather(const Temperature& temperature, const Humidity& humidity);
    };
    void printWeather(const Temperature& temperature, const Humidity& humidity) {}
    Humidity hum { 10 };
    Temperature temp { 12 };
    printWeather(temp, hum);
}
{   // <----------- 15.9 ------------>
    class Storage {
    private:
        int m_nValue {}; double m_dValue {};
    public:
        Storage(int nValue, double dValue) : m_nValue { nValue }, m_dValue { dValue }{}
        // Make the Display class a friend of Storage
        friend class Display;
    };
    class Display {
    private:
        bool m_displayIntFirst {};
    public:
        Display(bool displayIntFirst) : m_displayIntFirst { displayIntFirst } {}
        // Because Display is a friend of Storage, Display members can access the private members of Storage
        void displayStorage(const Storage& storage) {
            if (m_displayIntFirst)
                std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
            else // display double first
                std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
        }
        void setDisplayIntFirst(bool b){ m_displayIntFirst = b; }
    };
    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);
    display.setDisplayIntFirst(true);
    display.displayStorage(storage);
    // friendship is not reciprocal - if Display is a friend of Storage, does not mean Storage is also a friend of Display
    // Nor is friendship inherited. If class A makes B a friend, classes derived from B are not friends of A.

    class Display; // forward declaration for class Display
    class Storage{
        // Make the Display::displayStorage member function a friend of the Storage class
        friend void Display::displayStorage(const Storage& storage); // error: Storage hasn't seen the full definition of class Display
    };

    // To fix ts - Write definition of Display before Storage
    // However... 
    class Display {
    public:
        Display(bool displayIntFirst) : m_displayIntFirst { displayIntFirst } {}
        void displayStorage(const Storage& storage){ /*code*/ } // compile error: compiler doesn't know what a Storage is
    };
    class Storage {
    public:
        // Make the Display::displayStorage member function a friend of the Storage class
        friend void Display::displayStorage(const Storage& storage); // okay now
    };

    // Final fix - 
    class Storage; // forward declaration for class Storage
    class Display {
    public:
        void displayStorage(const Storage& storage); // forward declaration for Storage needed for reference here
    };
    class Storage { // full definition of Storage class
    public:
        // Make the Display::displayStorage member function a friend of the Storage class
        // Requires seeing the full definition of class Display (as displayStorage is a member)
        friend void Display::displayStorage(const Storage& storage);
    };
    // Now we can define Display::displayStorage
    // Requires seeing the full definition of class Storage (as we access Storage members)
    void Display::displayStorage(const Storage& storage) { /*code*/ }
    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);
}
{   // <----------- 15.10 ------------>
    class Employee{
        public:
        const std::string& getName() const &  { return m_name; } //  & qualifier overloads function to match only lvalue implicit objects, returns by reference
        std::string        getName() const && { return m_name; } // && qualifier overloads function to match only rvalue implicit objects, returns by value
    };
    // createEmployee() returns an Employee by value (which means the returned value is an rvalue)
    Employee createEmployee(std::string_view name){ Employee e { name }; return e; }
    Employee joe { "Joe" };
    std::cout << joe.getName() << '\n'; // Joe is an lvalue, so this calls std::string& getName() & (returns a reference)
    std::cout << createEmployee("Frank").getName() << '\n'; // Frank is an rvalue, so this calls std::string getName() && (makes a copy)
}
    return 0;
}