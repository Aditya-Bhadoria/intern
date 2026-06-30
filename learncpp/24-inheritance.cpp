#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    // !!!!!!!!!! VERY VERY IMP !!!!!!!!!!
    
{   // <----------- 24.1 ------------>
    // Inheritance - creating new objects by directly acquiring the attributes and 
    // behaviors of other objects and then extending or specializing them
}
{   // <----------- 24.2 ------------>
    // BaseballPlayer publicly inheriting Person
    class BaseballPlayer : public Person {
    public:
        double m_battingAverage{};
        int m_homeRuns{};
        BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
        : m_battingAverage{battingAverage}, m_homeRuns{homeRuns} {}
    };
    BaseballPlayer joe{};
    // Assign it a name (we can do this directly because m_name is public)
    joe.m_name = "Joe";
    // Print out the name
    std::cout << joe.getName() << '\n'; // use the getName() function we've acquired from the Person base class

    // Employee publicly inherits from Person
    class Employee: public Person {
    public:
        double m_hourlySalary{};
        long m_employeeID{};
        Employee(double hourlySalary = 0.0, long employeeID = 0)
            : m_hourlySalary{hourlySalary}, m_employeeID{employeeID} {}
        void printNameAndSalary() const
        { std::cout << m_name << ": " << m_hourlySalary << '\n'; }
    };
    Employee frank{20.25, 12345};
    frank.m_name = "Frank"; // we can do this because m_name is public
    frank.printNameAndSalary();

    class Supervisor: public Employee {
    public:
        // This Supervisor can oversee a max of 5 employees
        long m_overseesIDs[5]{};
    };
}
{   // <----------- 24.3 ------------>
    // When C++ constructs derived objects, it does so in phases - 
    // First, the most-base class (at the top of the inheritance tree)
    // Then each child class is constructed in order, until the most-child class (at the bottom of the inheritance tree) 

    class Base {
    public:
        int m_id {};
        Base(int id=0) : m_id { id } { std::cout << "Base\n"; }
    };
    class Derived: public Base {
    public:
        double m_cost {};
        Derived(double cost=0.0) : m_cost { cost } { std::cout << "Derived\n"; }
    };
    std::cout << "Instantiating Base\n";
    Base base;
    std::cout << "Instantiating Derived\n";
    Derived derived;    // this prints :-
    // Instantiating Base
    // Base
    // Instantiating Derived
    // Base
    // Derived

    class A {
    public:
        A() { std::cout << "A\n"; }
    };
    class B: public A {
    public:
        B() { std::cout << "B\n"; }
    };
    class C: public B {
    public:
        C() { std::cout << "C\n"; }
    };
    class D: public C {
    public:
        D() { std::cout << "D\n"; }
    };
    D d;
    // A
    // B
    // C
    // D
}
{   // <----------- 24.4 ------------>
    class Base {
    public:
        int m_id {};
        Base(int id=0) : m_id{ id } {}
        int getId() const { return m_id; }
    };
    class Derived: public Base {
    public:
        double m_cost {};
        Derived(double cost=0.0) : m_cost{ cost } {}
        double getCost() const { return m_cost; }
    };
    Derived derived{ 1.3 }; // use Derived(double) constructor

    // C++ prevents classes from initializing inherited member variables in the member initializer list of a constructor
    Derived(double cost=0.0, int id=0) : m_cost{ cost } , m_id{ id } {} // does not work
    // How to do?
    Derived(double cost=0.0, int id=0) : Base{ id } // Call Base(int) constructor with value id!
        , m_cost{ cost } {}
    // Derived constructor is calling a specific Base constructor to initialize the Base portion of the object
    
    // constructors can only call constructors from their immediate parent/base class
    // destructor is called in the reverse order of construction
}
{   // <----------- 24.5 ------------>
    // protected access specifier - allows class members, friends, and derived classes to access the member, not accessible from outside the class
    class Base {
    public: int m_public {}; // can be accessed by anybody
    protected: int m_protected {}; // can be accessed by Base members, friends, and derived classes
    private: int m_private {}; // can only be accessed by Base members and friends (but not derived classes)
    };
    class Derived: public Base {
    public:
        Derived(){
            m_public = 1; // allowed: can access public base members from derived class
            m_protected = 2; // allowed: can access protected base members from derived class
            m_private = 3; // not allowed: can not access private base members from derived class
        }
    };
    Base base;
    base.m_public = 1; // allowed: can access public members from outside class
    base.m_protected = 2; // not allowed: can not access protected members from outside class
    base.m_private = 3; // not allowed: can not access private members from outside class

    class Pub: public Base {};      // Inherit from Base publicly
    class Pro: protected Base {};   // Inherit from Base protectedly
    class Pri: private Base {};     // Inherit from Base privately
    class Def: Base {};             // Defaults to private inheritance

    // Access specifier 	Access specifier	  Access specifier	Access specifier
    // (in base)            (inherited publicly)  (privately)       (protectedly)
    // Public	            Public	              Private	        Protected
    // Protected	        Protected	          Private	        Protected
    // Private	            Inaccessible	      Inaccessible	    Inaccessible
}
{   // <----------- 24.6 ------------>
    // Adding new functionality to a derived class
}
{   // <----------- 24.7 ------------>
    class Base {
    public:
        Base() {}
        void identify() const { std::cout << "Base::identify()\n"; }
    };
    class Derived: public Base {
    public:
        Derived() {}
        void identify() const { std::cout << "Derived::identify()\n"; }
    };
    Base base {};
    base.identify();    // Base::identify()
    Derived derived {};
    derived.identify(); // Derived::identify()

    // Adding to existing functionality
    class Derived: public Base{
    public:
        Derived() {}
        void identify() const {
            std::cout << "Derived::identify()\n";
            Base::identify(); // note call to Base::identify() here
            identify(); // no scope resolution results in self-call and infinite recursion
        }
    };
    // friend function can't use scope resolution operator
    class Base{
    public:
        Base() {}
        friend std::ostream& operator<< (std::ostream& out, const Base&){
            out << "In Base\n";
            return out;
        }
    };
    class Derived: public Base {
    public:
        Derived() {}
        friend std::ostream& operator<< (std::ostream& out, const Derived& d){
            out << "In Derived\n";
            // static_cast Derived to a Base object, so we call the right version of operator<<
            out << static_cast<const Base&>(d);
            return out;
        }
    };
    Derived derived {};
    std::cout << derived << '\n';   // prints In Derived \n In Base

    // Overload resolution in derived classes
    class Base{
    public:
        void print(int)    { std::cout << "Base::print(int)\n"; }
        void print(double) { std::cout << "Base::print(double)\n"; }
    };
    class Derived: public Base{
    public:
        void print(double) { std::cout << "Derived::print(double)"; }
    };
    Derived d{};
    d.print(5); // calls Derived::print(double), not Base::print(int)

    class Derived: public Base{
    public:
        using Base::print; // make all Base::print() functions eligible for overload resolution
        void print(double) { std::cout << "Derived::print(double)"; }
    };
    d.print(5); // calls Base::print(int), which is the best matching function visible in Derived
}
{   // <----------- 24.8 ------------>
    class Base{
    private: int m_value {};
    public:
        Base(int value) : m_value { value } {}
    protected:
        void printValue() const { std::cout << m_value; }
    };
    class Derived: public Base{
    public:
        Derived(int value) : Base { value } {}
        // changing it to public via a using declaration
        using Base::printValue; // note: no parenthesis here
    };
    Derived derived { 7 };
    // printValue is public in Derived, so this is okay
    derived.printValue(); // prints 7
    // But still protected in Base

    // can only change the access specifiers of base members the derived class would normally be able to access
    // so you can't change private to protected or public

    class Base {
    public:
        int m_value{};
    };
    class Derived : public Base {
    private:
        using Base::m_value;
    public:
        Derived(int value) : Base { value } {}
    };
	Derived derived{ 7 };
	std::cout << derived.m_value; // error: m_value is private in Derived
	Base& base{ derived };
	std::cout << base.m_value; // okay: m_value is public in Base

    // No way to change the access specifier for a single overload
    class Base{
    public:
        int getValue() const { return m_value; }
        int getValue(int) const { return m_value; }
    };
    class Derived : public Base {
    private:
        using Base::getValue; // make ALL getValue functions private
    };
	Derived derived{ 7 };
	std::cout << derived.getValue();  // error: getValue() is private in Derived
	std::cout << derived.getValue(5); // error: getValue(int) is private in Derived

    // Deleting functions in the derived class
    class Derived : public Base {
    public:
        Derived(int value) : Base { value } {}
        int getValue() const = delete; // mark this function as inaccessible
    };
	Derived derived { 7 };
	std::cout << derived.getValue();        // The following won't work because getValue() has been deleted!
	std::cout << derived.Base::getValue();  // We can call the Base::getValue() function directly
	// Or we can upcast Derived to a Base reference and getValue() will resolve to Base::getValue()
	std::cout << static_cast<Base&>(derived).getValue();
}
{   // <----------- 24.9 ------------>
    // Multiple inheritance - enables a derived class to inherit members from more than one parent.
    class Person {
    private:
        std::string m_name{};
        int m_age{};
    public:
        Person(std::string_view name, int age) : m_name{ name }, m_age{ age } {}
        const std::string& getName() const { return m_name; }
        int getAge() const { return m_age; }
    };
    class Employee {
    private:
        std::string m_employer{};
        double m_wage{};
    public:
        Employee(std::string_view employer, double wage) : m_employer{ employer }, m_wage{ wage } {}
        const std::string& getEmployer() const { return m_employer; }
        double getWage() const { return m_wage; }
    };
    // Teacher publicly inherits Person and Employee
    class Teacher : public Person, public Employee {
    private:
        int m_teachesGrade{};
    public:
        Teacher(std::string_view name, int age, std::string_view employer, double wage, int teachesGrade)
            : Person{ name, age }, Employee{ employer, wage }, m_teachesGrade{ teachesGrade } {}
    };
    Teacher t{ "Mary", 45, "Boo", 14.3, 8 };

    // Mixin - small class that can be inherited from in order to add properties to a class
    struct Point2D { int x{}, y{}; };
    class Box{ // mixin Box class
    public:
        void setTopLeft(Point2D point) { m_topLeft = point; }
        void setBottomRight(Point2D point) { m_bottomRight = point; }
    private:
        Point2D m_topLeft{};
        Point2D m_bottomRight{};
    };
    class Label{ // mixin Label class
    public:
        void setText(const std::string_view str) { m_text = str; }
        void setFontSize(int fontSize) { m_fontSize = fontSize; }
    private:
        std::string m_text{};
        int m_fontSize{};
    };
    class Tooltip{ // mixin Tooltip class
    public:
        void setText(const std::string_view str) { m_text = str; }
    private:
        std::string m_text{};
    };
    class Button : public Box, public Label, public Tooltip {}; // Button using three mixins
	Button button{};
	button.Box::setTopLeft({ 1, 1 });
	button.Box::setBottomRight({ 10, 10 });
	button.Label::setText("Submit");
	button.Label::setFontSize(6);
	button.Tooltip::setText("Submit the form to the server");
    // should use :: scope resolution, to prevent error in ambiguous cases - like setText() here

    class USBDevice{
    private:
        long m_id {};
    public:
        long getID() const { return m_id; }
    };
    class NetworkDevice {
    private:
        long m_id {};
    public:
        long getID() const { return m_id; }
    };
    class WirelessAdapter: public USBDevice, public NetworkDevice {
    public:
        WirelessAdapter(long usbId, long networkId) : USBDevice { usbId }, NetworkDevice { networkId } {}
    };
    WirelessAdapter c54G { 5442, 181742 };
    std::cout << c54G.getID(); // Which getID() do we call?

    // Diamond of doom
    class PoweredDevice {};
    class Scanner: public PoweredDevice {};
    class Printer: public PoweredDevice {};
    class Copier: public Scanner, public Printer {};
    //          PoweredDevice
    //          /         \ 
    //      Scanner     Printer
    //          \        /
    //            Copier
}
{   // <----------- 24.x ------------>
}
    return 0;
}