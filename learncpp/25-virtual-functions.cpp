#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    // !!!!!!!!!!! VERY VERY IMP !!!!!!!!!!!
    
{   // <----------- 25.1 ------------>
    Derived derived{ 5 };
    // These are both legal!
    Base& rBase{ derived }; // rBase is an lvalue reference (not an rvalue reference)
    Base* pBase{ &derived }; // both these can only see members of Base
    std::cout << derived.getName() << " " << derived.getValue() << '\n';    // Derived 5
    std::cout << rBase.getName() << " " << rBase.getValue() << '\n';        // Base 5
    std::cout << pBase->getName() << " " << pBase->getValue() << '\n';      // Base 5

    const Cat fred{ "Fred" };
    const Cat misty{ "Misty" };
    const Cat zeke{ "Zeke" };
    const Dog garbo{ "Garbo" };
    const Dog pooky{ "Pooky" };
    const Dog truffle{ "Truffle" };
    // Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
    const auto animals{ std::to_array<const Animal*>({&fred, &garbo, &misty, &pooky, &truffle, &zeke }) };
}
{   // <----------- 25.2 ------------>
    // virtual function - resolves to the most-derived version of the function for the actual type of the object being referenced or pointed to
    class Base{
    public:
        virtual std::string_view getName() const { return "Base"; } // note addition of virtual keyword
    };
    class Derived: public Base{
    public:
        virtual std::string_view getName() const { return "Derived"; }
    };
    Derived derived {};
    Base& rBase{ derived };
    std::cout << rBase.getName() << '\n'; // print - Derived

    class A {
    public: virtual std::string_view getName() const { return "A"; }
    };
    class B: public A {
    public: virtual std::string_view getName() const { return "B"; }
    };
    class C: public B {
    public: virtual std::string_view getName() const { return "C"; }
    };
    class D: public C {
    public: virtual std::string_view getName() const { return "D"; }
    };
    C c {};
    A& rBase{ c };
    std::cout << rBase.getName() << '\n'; // prints - C
    A a { c }; // copies the A portion of c into a (don't do this)
    std::cout << a.getName(); // will always call A::getName

    // polymorphism - ability of an entity to have multiple forms
    // Compile-time polymorphism - polymorphism that are resolved by the compiler e.g. function overload resolution, template resolution
    // Runtime polymorphism - polymorphism that are resolved at runtime e.g. virtual function resolution
    
    // Signature of the derived class function must exactly match the signature of the base class virtual function
    // If a function is virtual, all matching overrides in derived classes are implicitly virtual.
    class Base {
    public:
        virtual int getValue() const { return 5; }
    };
    class Derived: public Base {
    public:
        virtual double getValue() const { return 6.78; } // compile error - not considered a matching override
    };
}
{   // <----------- 25.3 ------------>
    class A {
    public:
        virtual std::string_view getName1(int x) { return "A"; }
        virtual std::string_view getName2(int x) { return "A"; }
    };
    class B : public A {
    public:
        virtual std::string_view getName1(short x) { return "B"; } // note: parameter is a short
        virtual std::string_view getName2(int x) const { return "B"; } // note: function is const
    };
	B b{};
	A& rBase{ b };
	std::cout << rBase.getName1(1) << '\n'; // prints - A
	std::cout << rBase.getName2(2) << '\n'; // prints - A

    class A {
    public:
        virtual std::string_view getName1(int x) { return "A"; }
        virtual std::string_view getName2(int x) { return "A"; }
        virtual std::string_view getName3(int x) { return "A"; }
    };
    class B : public A {
    public:
        std::string_view getName1(short int x) override { return "B"; } // compile error, function is not an override
        std::string_view getName2(int x) const override { return "B"; } // compile error, function is not an override
        std::string_view getName3(int x) override { return "B"; } // okay, function is an override of A::getName3(int)

    };
    // If a member function is both const and an override, the const must be listed first

    // final specifier - where you don’t want someone to be able to override a virtual function, or inherit from a class
    class A {
    public:
        virtual std::string_view getName() const { return "A"; }
    };
    class B : public A {
    public:
        // note use of final specifier on following line -- that makes this function not able to be overridden in derived classes
        std::string_view getName() const override final { return "B"; } // okay, overrides A::getName()
    };
    class C : public B {
    public:
        std::string_view getName() const override { return "C"; } // compile error: overrides B::getName(), which is final
    };

    class B final : public A { // note use of final specifier here
    public:
        std::string_view getName() const override { return "B"; }
    };
    class C : public B {};// compile error: cannot inherit from final class

    // covariant return types - derived class virtual function override can have a different return type than the base class and still be considered a matching override
    class Base {
    public:
        // This version of getThis() returns a pointer to a Base class
        virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
        void printType() { std::cout << "returned a Base\n"; }
    };
    class Derived : public Base {
    public:
        // Normally override functions have to return objects of the same type as the base function
        // However, because Derived is derived from Base, it's okay to return Derived* instead of Base*
        Derived* getThis() override { std::cout << "called Derived::getThis()\n";  return this; }
        void printType() { std::cout << "returned a Derived\n"; }
    };
	Derived d{};
	Base* b{ &d };
	d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
	b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, calls Base::printType
}
{   // <----------- 25.4 ------------>
    class Base {
    public:
        ~Base() { std::cout << "Calling ~Base()\n"; } // note: not virtual
    };
    class Derived: public Base {
    private: int* m_array {};
    public:
        Derived(int length) : m_array{ new int[length] } {}
        ~Derived() { // note: not virtual (your compiler may warn you about this)
            std::cout << "Calling ~Derived()\n";
            delete[] m_array;
        }
    };
    Derived* derived { new Derived(5) };
    Base* base { derived };
    delete base;    // prints - Calling ~Base()

    class Base{
        virtual ~Base() { std::cout << "Calling ~Base()\n"; } // note: virtual
    };
    class Derived: public Base {
    public:
        virtual ~Derived() { // note: virtual
            std::cout << "Calling ~Derived()\n";
            delete[] m_array;
        }
    };
    Derived* derived { new Derived(5) };
    Base* base { derived };
    delete base;    // prints - Calling ~Derived() \n Calling ~Base()

    virtual ~Base() = default; // generate a virtual default destructor

    // to call Base::getName() instead of Derived::getName() - use the scope resolution operator:
    Derived derived {};
    const Base& base { derived };
    // Calls Base::getName() instead of the virtualized Derived::getName()
    std::cout << base.Base::getName() << '\n';
}
{   // <----------- 25.5 ------------>
    // binding - process of associating names with such properties (like int x -> associate the name x with type int)
    // Function binding (or method binding) - what function definition is associated with a function call
    // dispatching - actually invoking a bound function

    // Early Binding (Static Binding) - When the compiler or linker can directly resolve which specific function definition matches a function call at compile-time
    // Occurs during direct function calls to non-member functions, non-virtual member functions, overloaded functions, and function templates.
    // highly efficient with zero runtime overhead, but it lacks runtime flexibility

    // Late Binding (Dynamic Binding / Dynamic Dispatch) - When function call cannot be resolved at compile-time and must instead be looked up dynamically at runtime.
    // when calling functions via function pointers (indirect function calls) or when resolving virtual functions.
}
{   // <----------- 25.6 ------------> ⭐️⭐️
    // The virtual table - lookup table of functions used to resolve function calls in a dynamic/late binding manner
    // Basically - A static array of function pointers set up by the compiler at compile-time
    // One vtable per class (not per object). If a class defines or inherits a virtual function, it gets a vtable.
    // Each entry in this table is simply a function pointer that points to the most-derived function accessible by that class
    
    // Virtual Pointer (vptr) - hidden member pointer (often named *__vptr) that the compiler automatically injects into the Base class.
    // It is a per-object cost. Every instance of your class inherits this pointer.
    // When a class object is created, *__vptr is set to point to the virtual table for that class
    // Size penalty - Every class object with virtual functions becomes larger by the size of one pointer
    // Speed penalty - virtual function call requires two extra memory dereferences (Object -> __vptr -> vtable -> Function).
}
{   // <----------- 25.7 ------------>
    // pure virtual function - has no body at all!, simply acts as a placeholder meant to be redefined by derived classes.
    class Base {
    public:
        std::string_view sayHi() const { return "Hi"; } // a normal non-virtual function
        virtual std::string_view getName() const { return "Base"; } // a normal virtual function
        virtual int getValue() const = 0; // a pure virtual function
        int doSomething() = 0; // Compile error: can not set non-virtual functions to 0
    };

    // abstract base class - any class with one or more pure virtual functions, can not be instantiated
    class Animal{ // This Animal is an abstract base class
    protected:
        std::string m_name {};
    public:
        Animal(std::string_view name) : m_name{ name } {}
        const std::string& getName() const { return m_name; }
        virtual std::string_view speak() const = 0; // note that speak is now a pure virtual function
        virtual ~Animal() = default;
    };
    class Cow: public Animal {
    public:
        Cow(std::string_view name) : Animal{ name } {}
        // We forgot to redefine speak
    };
    Cow cow{ "Betsy" };
    std::cout << cow.getName() << " says " << cow.speak() << '\n';  // compile error - type 'Cow' is an abstract class
    
    class Cow: public Animal {
    public:
        std::string_view speak() const override { return "Moo"; }
    };
    std::cout << cow.getName() << " says " << cow.speak() << '\n';  // Betsy says Moo

    // Any class with pure virtual functions should also have a virtual destructor.
    class Animal{ // This Animal is an abstract base class
    protected:
        virtual std::string_view speak() const = 0; // The = 0 means this function is pure virtual
        virtual ~Animal() = default;
    };
    std::string_view Animal::speak() const { return "buzz"; } // even though it has a definition

    class Dragonfly: public Animal {
    public:
        std::string_view speak() const override // this class is no longer abstract because we defined this function
        { return Animal::speak(); }// use Animal's default implementation
    };

    // Interface class - no member variables, and where all of the functions are pure virtual!
    class IErrorLog {
    public:
        virtual bool openLog(std::string_view filename) = 0;
        virtual bool closeLog() = 0;
        virtual bool writeError(std::string_view errorMessage) = 0;
        virtual ~IErrorLog() {} // make a virtual destructor in case we delete an IErrorLog pointer, so the proper derived destructor is called
    };

    // abstract classes still have virtual tables
    // The virtual table entry for a class with a pure virtual function will generally either contain a null pointer, or 
    // point to a generic function that prints an error (sometimes this function is named __purecall).
}
{   // <----------- 25.8 ------------>
    class PoweredDevice {
    public:
        PoweredDevice(int power) { std::cout << "PoweredDevice: " << power << '\n'; }
    };
    class Scanner: public PoweredDevice {
    public:
        Scanner(int scanner, int power) : PoweredDevice{ power }
        { std::cout << "Scanner: " << scanner << '\n'; }
    };
    class Printer: public PoweredDevice {
    public:
        Printer(int printer, int power) : PoweredDevice{ power }
        { std::cout << "Printer: " << printer << '\n'; }
    };
    class Copier: public Scanner, public Printer {
    public:
        Copier(int scanner, int printer, int power) : Scanner{ scanner, power }, Printer{ printer, power } {}
    };
    // would end up with two copies of the PoweredDevice class -- one from Printer, and one from Scanner
    Copier copier{ 1, 2, 3 };
    // PoweredDevice: 3
    // Scanner: 1
    // PoweredDevice: 3
    // Printer: 2

    // virtual base class - means there is only one base object, shared between all objects in the inheritance tree and it is only constructed once
    // this is one time when Copier is allowed to call a non-immediate-parent constructor directly:
    class PoweredDevice {
    public:
    };
    class Scanner: virtual public PoweredDevice { // note: PoweredDevice is now a virtual base class
    public:
        Scanner(int scanner, int power)
            : PoweredDevice{ power } // this line is required to create Scanner objects, but ignored in this case
        { std::cout << "Scanner: " << scanner << '\n'; }
    };
    class Printer: virtual public PoweredDevice { // note: PoweredDevice is now a virtual base class
    public:
        Printer(int printer, int power)
            : PoweredDevice{ power } // this line is required to create Printer objects, but ignored in this case
        { std::cout << "Printer: " << printer << '\n'; }
    };
    class Copier: public Scanner, public Printer {
    public:
        Copier(int scanner, int printer, int power)
            : PoweredDevice{ power }, // PoweredDevice is constructed here
            Scanner{ scanner, power }, Printer{ printer, power } {}
    };
    Copier copier{ 1, 2, 3 };
    // PoweredDevice: 3
    // Scanner: 1
    // Printer: 2
}
{   // <----------- 25.9 ------------>
	std::vector<Base> v{};
	v.push_back(Base{ 5 });    // add a Base object to our vector
	v.push_back(Derived{ 6 }); // add a Derived object to our vector
    // Print out all of the elements in our vector
	for (const auto& element : v)
		std::cout << "I am a " << element.getName() << " with value " << element.getValue() << '\n';
    // I am a Base with value 5
    // I am a Base with value 6

    std::vector<Base&> v{}; // error - elements of std::vector must be assignable, whereas references can’t be reassigned

	std::vector<Base*> v{};
	Base b{ 5 }; // b and d can't be anonymous objects
	Derived d{ 6 };
	v.push_back(&b); // add a Base object to our vector
	v.push_back(&d); // add a Derived object to our vector
	// Print out all of the elements in our vector
	for (const auto* element : v)
		std::cout << "I am a " << element->getName() << " with value " << element->getValue() << '\n';
    // I am a Base with value 5
    // I am a Derived with value 6

	std::vector<std::reference_wrapper<Base>> v{}; // a vector of reassignable references to Base
	Base b{ 5 }; // b and d can't be anonymous objects
	Derived d{ 6 };
	v.push_back(b); // add a Base object to our vector
	v.push_back(d); // add a Derived object to our vector
	// Print out all of the elements in our vector
	// we use .get() to get our element out of the std::reference_wrapper
	for (const auto& element : v) // element has type const std::reference_wrapper<Base>&
		std::cout << "I am a " << element.get().getName() << " with value " << element.get().getValue() << '\n';

    // The Frankenobject
    Derived d1{ 5 };
    Derived d2{ 6 };
    Base& b{ d2 };
    b = d1; // this line is problematic 
    // only the Base portion of d1 is copied into d2.
}
{   // <----------- 25.10 ------------>
    // downcasting - converting base-class pointers into derived-class pointers
    Base* getObject(bool returnDerived) {
        if (returnDerived) return new Derived{1, "Apple"};
        else return new Base{2};
    }
	Base* b{ getObject(true) };
	Derived* d{ dynamic_cast<Derived*>(b) }; // use dynamic cast to convert Base pointer into Derived pointer
    // If a dynamic_cast fails, the result of the conversion will be a null pointer.
	if (d) // make sure d is non-null
		std::cout << "The name of the Derived is: " << d->getName() << '\n';

    // several cases where downcasting using dynamic_cast will not work:
    // With protected or private inheritance.
    // For classes that do not declare or inherit any virtual functions (and thus don’t have a virtual table).

    // static_cast does no runtime type checking to ensure that what you’re doing makes sense
    // using static_cast faster, but more dangerous
    // If you’re absolutely sure that the pointer you’re downcasting will succeed, then using static_cast is acceptable

	Derived apple{1, "Apple"}; // create an apple
	Base& b{ apple }; // set base reference to object
	Derived& d{ dynamic_cast<Derived&>(b) }; // dynamic cast using a reference instead of a pointer
    // if the dynamic_cast of a reference fails, an exception of type std::bad_cast is thrown
}
{   // <----------- 25.11 ------------>
    class Base {
    public:
        // Here's our overloaded operator<<
        friend std::ostream& operator<<(std::ostream& out, const Base& b){
            // Call virtual function identify() to get the string to be printed
            out << b.identify();
            return out;
        }
        // We'll rely on member function identify() to return the string to be printed
        // Because identify() is a normal member function, it can be virtualized
        virtual std::string identify() const { return "Base"; }
    };
    class Derived : public Base {
    public:
        // Here's our override identify() function to handle the Derived case
        std::string identify() const override { return "Derived"; }
    };
	Base b{}; std::cout << b << '\n';
	Derived d{};
	std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects
	Base& bref{ d };
	std::cout << bref << '\n';  // prints - Derived

    // A more flexible solution
    class Base {
    public:
        // Here's our overloaded operator<<
        friend std::ostream& operator<<(std::ostream& out, const Base& b) {
            // Delegate printing responsibility for printing to virtual member function print()
            return b.print(out);
        }
        // We'll rely on member function print() to do the actual printing
        // Because print() is a normal member function, it can be virtualized
        virtual std::ostream& print(std::ostream& out) const {
            out << "Base";
            return out;
        }
    };
    // Some class or struct with an overloaded operator<<
    struct Employee {
        std::string name{};
        int id{};
        friend std::ostream& operator<<(std::ostream& out, const Employee& e) {
            out << "Employee(" << e.name << ", " << e.id << ")";
            return out;
        }
    };
    class Derived : public Base {
    private:
        Employee m_e{}; // Derived now has an Employee member
    public:
        Derived(const Employee& e) : m_e{ e } {}
        // Here's our override print() function to handle the Derived case
        std::ostream& print(std::ostream& out) const override {
            out << "Derived: ";
            // Print the Employee member using the stream object
            out << m_e;
            return out;
        }
    };
	Base b{}; std::cout << b << '\n';
	Derived d{ Employee{"Jim", 4}};
	std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects
	Base& bref{ d };
	std::cout << bref << '\n';
}
{   // <----------- 25.x ------------>
}
    return 0;
}