#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    // !!!!!!!!!!!!!! VERY VERY IMP !!!!!!!!!!!!!!!
    
{   // <----------- 22.1 ------------>
    template <typename T>
    class Auto_ptr1 {
        T* m_ptr {};
    public:
        // Pass in a pointer to "own" via the constructor
        Auto_ptr1(T* ptr=nullptr) :m_ptr(ptr) {}
        // The destructor will make sure it gets deallocated
        ~Auto_ptr1() { delete m_ptr; }
        // Overload dereference and operator-> so we can use Auto_ptr1 like m_ptr.
        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }
    };
    // A sample class to prove the above works
    class Resource {
    public:
        Resource() { std::cout << "Resource acquired\n"; }
        ~Resource() { std::cout << "Resource destroyed\n"; }
    };
    int main(){
        Auto_ptr1<Resource> res(new Resource()); // Note the allocation of memory here
            // ... but no explicit delete needed
        // Also note that we use <Resource>, not <Resource*> - because we've defined m_ptr to have type T* (not T)
        return 0;
    } // res goes out of scope here, and destroys the allocated Resource for us. This prints :-
    // Resource acquired
    // Resource destroyed

    // Some flaws :-
    void passByValue(Auto_ptr1<Resource> res) { /*code*/ } // res destroyed after func call
    Auto_ptr1<Resource> res1(new Resource());
    passByValue(res1);
    // res1 will be copied by value into parameter res, so both res1.m_ptr and res.m_ptr will hold the same address.
    // When res is destroyed, res1.m_ptr is left dangling. When res1.m_ptr is later deleted, undefined behavior will result.

    // Move semantics means the class will transfer ownership of the object rather than making a copy.
    template <typename T>
    class Auto_ptr2 {
        T* m_ptr {};
    public:
        Auto_ptr2(T* ptr=nullptr) :m_ptr(ptr) {}
        ~Auto_ptr2() { delete m_ptr; }
        // A copy constructor that implements move semantics
        Auto_ptr2(Auto_ptr2& a) { // note: not const
            // We don't need to delete m_ptr here.  This constructor is only called when we're creating a new object, and m_ptr can't be set prior to this.
            m_ptr = a.m_ptr; // transfer our dumb pointer from the source to our local object
            a.m_ptr = nullptr; // make sure the source no longer owns the pointer
        }
        // An assignment operator that implements move semantics
        Auto_ptr2& operator=(Auto_ptr2& a) { // note: not const
            if (&a == this) return *this;
            delete m_ptr; // make sure we deallocate any pointer the destination is already holding first
            m_ptr = a.m_ptr; // then transfer our dumb pointer from the source to the local object
            a.m_ptr = nullptr; // make sure the source no longer owns the pointer
            return *this;
        }
        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }
        bool isNull() const { return m_ptr == nullptr; }
    };
    class Resource{
    public:
        Resource() { std::cout << "Resource acquired\n"; }
        ~Resource() { std::cout << "Resource destroyed\n"; }
    };
	Auto_ptr2<Resource> res1(new Resource());
	Auto_ptr2<Resource> res2; // Start as nullptr
	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");
	res2 = res1; // res2 assumes ownership, res1 is set to null
	std::cout << "Ownership transferred\n";
	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");
}
{   // <----------- 22.2 ------------>
    int&& rref{ 5 }; // r-value reference initialized with r-value 5
    // because we're initializing an r-value reference with a literal, a temporary with value 5 is created here
    // a temporary object is constructed from the literal so that the reference is referencing a temporary object, not a literal value.

    void fun(const int& lref) // l-value arguments will select this function
    { std::cout << "l-value reference to const: " << lref << '\n'; }
    void fun(int&& rref) // r-value arguments will select this function
    { std::cout << "r-value reference: " << rref << '\n'; }
	int x{ 5 };
	fun(x); // l-value argument calls l-value version of function
	fun(5); // r-value argument calls r-value version of function

    // Rvalue reference variables are lvalues
    int&& ref{ 5 };
    fun(ref);   // calls fun(const int&) instead of fun(int&&)
}
{   // <----------- 22.3 ------------>
    template<typename T>
    class Auto_ptr3 {
        T* m_ptr {};
    public:
        // Copy constructor
        // Do deep copy of a.m_ptr to m_ptr
        Auto_ptr3(const Auto_ptr3& a){
            m_ptr = new T;
            *m_ptr = *a.m_ptr;
        }
        // Copy assignment
        // Do deep copy of a.m_ptr to m_ptr
        Auto_ptr3& operator=(const Auto_ptr3& a) {
            if (&a == this) return *this; // Self-assignment detection
            delete m_ptr; // Release any resource we're holding
            m_ptr = new T; // Copy the resource
            *m_ptr = *a.m_ptr;
            return *this;
        }
        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }
        bool isNull() const { return m_ptr == nullptr; }
    };
    class Resource {};
    Auto_ptr3<Resource> generateResource(){
        Auto_ptr3<Resource> res{new Resource};
        return res; // this return value will invoke the copy constructor
    }
	Auto_ptr3<Resource> mainres;
	mainres = generateResource(); // this assignment will invoke the copy assignment
    // When this program is run, it prints:
    // Resource acquired    // res created
    // Resource acquired    // return by value creates a new temporary Resource using copy constructor
    // Resource destroyed   // res goes out of scope
    // Resource acquired    // mainres uses copy assignment
    // Resource destroyed   // temporary copy goes out of scope
    // Resource destroyed   // mainres goes out of scope, program ends

	// Move constructor
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr4(Auto_ptr4&& a) noexcept
		: m_ptr { a.m_ptr } { a.m_ptr = nullptr; } // we'll talk more about this line below
        
	// Move assignment
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr4& operator=(Auto_ptr4&& a) noexcept {
        if (&a == this) return *this; // Self-assignment detection
		delete m_ptr; // Release any resource we're holding
		m_ptr = a.m_ptr; // Transfer ownership of a.m_ptr to m_ptr
		a.m_ptr = nullptr; // we'll talk more about this line below
		return *this;
	}
    // When run, this program prints:
    // Resource acquired
    // Resource destroyed
    // instead of copying our Resource twice (copy constructor and copy assignment), we transfer it twice
    // Move constructors and move assignment should be marked as noexcept. This tells the compiler that these functions will not throw exceptions.
    
    // Automatic l-values returned by value may be moved instead of copied
    // notice that above when returning by value, res was moved even though it is a l-value
    // automatic objects returned from a function by value can be moved even if they are l-values

    class Name {
    private:
        std::string m_name {}; // std::string is move capable
    public:
        Name(std::string_view name) : m_name{ name } {}
        Name(const Name& name) = delete;
        Name& operator=(const Name& name) = delete;
        Name(Name&& name) noexcept {
            std::cout << "Move ctor\n";
            std::swap(*this, name); // bad!
        }
        Name& operator=(Name&& name) noexcept {
            std::cout << "Move assign\n";
            std::swap(*this, name); // bad!
            return *this;
        }
        const std::string& get() const { return m_name; }
    };
    Name n1{ "Alex" };
    n1 = Name{"Joe"}; // invokes move assignment
    // std::swap() calls both the move constructor and move assignment on move-capable objects - results in an infinite recursion issue

    // Create our own swap friend function to swap the members of Name
    friend void swap(Name& a, Name& b) noexcept 
    { std::swap(a.m_name, b.m_name); }
    // We avoid recursive calls by invoking std::swap on the std::string member, not on Name
}
{   // <----------- 22.4 ------------>
    // std::move is STL function that casts (using static_cast) its argument into an r-value reference, so that move semantics can be invoked
    #include <utility> // for std::move
    template <typename T>
    void mySwapMove(T& a, T& b) {
        T tmp { std::move(a) }; // invokes move constructor
        a = std::move(b); // invokes move assignment
        b = std::move(tmp); // invokes move assignment
    }
	std::string x{ "abc" };
	std::string y{ "de" };
	mySwapMove(x, y); // does 3 moves instead of 3 copies

	v.push_back(std::move(str)); // calls r-value version of push_back, which moves str into the array element
    // Unless otherwise specified, moved-from objects [of types defined in the C++ standard library] shall be placed in a valid but unspecified state
}
{   // <----------- 22.5 ------------>
    // manage any dynamically allocated object that is not shared by multiple objects
    #include <memory> // for std::unique_ptr
    class Resource {
    public:
        Resource() { std::cout << "Resource acquired\n"; }
        ~Resource() { std::cout << "Resource destroyed\n"; }
    };
    int main() {
        // allocate a Resource object and have it owned by std::unique_ptr
        std::unique_ptr<Resource> res{ new Resource() };
        return 0;
    } // res goes out of scope here, and the allocated Resource is destroyed

    #include <utility> // for std::move
	std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
	std::unique_ptr<Resource> res2{}; // Start as nullptr
	// res2 = res1; // Won't compile: copy assignment is disabled
	res2 = std::move(res1); // res2 assumes ownership, res1 is set to null
	std::cout << "Ownership transferred\n";
	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");
    // copy initialization and copy assignment are disabled

    std::ostream& operator<<(std::ostream& out, const Resource&){
        out << "I am a resource";
        return out;
    }
	std::unique_ptr<Resource> res{ new Resource{} };
	if (res) // use implicit cast to bool to ensure res contains a Resource
		std::cout << *res << '\n'; // print the Resource that res is owning

    #include <memory> // for std::unique_ptr and std::make_unique
    class Fraction {
    private:
        int m_numerator{ 0 }, m_denominator{ 1 };
    public:
        Fraction(int numerator = 0, int denominator = 1) :
            m_numerator{ numerator }, m_denominator{ denominator } {}

        friend std::ostream& operator<<(std::ostream& out, const Fraction &f1){
            out << f1.m_numerator << '/' << f1.m_denominator;
            return out;
        }
    };
	// Create a single dynamically allocated Fraction with numerator 3 and denominator 5
	// We can also use automatic type deduction to good effect here
	auto f1{ std::make_unique<Fraction>(3, 5) };
	std::cout << *f1 << '\n';
	// Create a dynamically allocated array of Fractions of length 4
	auto f2{ std::make_unique<Fraction[]>(4) };
	std::cout << f2[0] << '\n';
    // Use std::make_unique() instead of creating std::unique_ptr and using new yourself.

    std::unique_ptr<Resource> createResource()
    { return std::make_unique<Resource>(); }
    auto ptr{ createResource() };

    // This function takes ownership of the Resource, which isn't what we want
    void takeOwnership(std::unique_ptr<Resource> res)
    { if (res) std::cout << *res << '\n'; } // the Resource is destroyed here
    auto ptr{ std::make_unique<Resource>() };
    //    takeOwnership(ptr); // This doesn't work, need to use move semantics
    takeOwnership(std::move(ptr)); // ok: use move semantics

    // The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
    void useResource(const Resource* res) {
        if (res) std::cout << *res << '\n';
        else std::cout << "No resource\n";
    }
	auto ptr{ std::make_unique<Resource>() };
	useResource(ptr.get()); // note: get() used here to get a pointer to the Resource

    Resource* res{ new Resource() };
    std::unique_ptr<Resource> res1{ res };
    std::unique_ptr<Resource> res2{ res };
    // While this is legal syntactically, [In The End] both res1 and res2 will try to delete the Resource, which will lead to undefined behavior.
    
    Resource* res{ new Resource() };
    std::unique_ptr<Resource> res1{ res };
    delete res;
    // Second, don’t manually delete the resource out from underneath the std::unique_ptr.
}
{   // <----------- 22.6 ------------>
    // std::shared_ptr keeps track of how many std::shared_ptr are sharing the resource
    // As long as at least one std::shared_ptr is pointing to the resource, the resource will not be deallocated, even if individual std::shared_ptr are destroyed
    #include <memory> // for std::shared_ptr
    class Resource {
    public:
        Resource() { std::cout << "Resource acquired\n"; }
        ~Resource() { std::cout << "Resource destroyed\n"; }
    };
    int main() {
        // allocate a Resource object and have it owned by std::shared_ptr
        Resource* res { new Resource };
        std::shared_ptr<Resource> ptr1{ res }; 
        {
            std::shared_ptr<Resource> ptr2 { ptr1 }; // make another std::shared_ptr pointing to the same thing
            std::cout << "Killing one shared pointer\n";
        } // ptr2 goes out of scope here, but nothing happens
        std::cout << "Killing another shared pointer\n";
        return 0;
    } // ptr1 goes out of scope here, and the allocated Resource is destroyed

	Resource* res { new Resource };
	std::shared_ptr<Resource> ptr1 { res }; {
		std::shared_ptr<Resource> ptr2 { res }; // create ptr2 directly from res (instead of ptr1)
		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, and the allocated Resource is destroyed
	std::cout << "Killing another shared pointer\n";
    // ptr1 goes out of scope here, and the allocated Resource is destroyed again
    // Always make a copy of an existing std::shared_ptr if you need more than one std::shared_ptr pointing to the same resource.

	// allocate a Resource object and have it owned by std::shared_ptr
	auto ptr1 { std::make_shared<Resource>() };{
		auto ptr2 { ptr1 }; // create ptr2 using copy of ptr1
		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, but nothing happens

    // std::shared_ptr uses two pointers internally
    // One pointer points at the resource being managed, other points at a “control block”, which is a 
    // dynamically allocated object that tracks of a bunch of stuff, including how many std::shared_ptr are pointing at the resource
    
    // std::unique_ptr can be converted into a std::shared_ptr via a special std::shared_ptr constructor that accepts a std::unique_ptr r-value. 
    // The contents of the std::unique_ptr will be moved to the std::shared_ptr.
    // std::shared_ptr can not be safely converted to a std::unique_ptr
}
{   // <----------- 22.7 ------------>
    #include <memory> // for std::shared_ptr
    class Person{
        std::string m_name;
        std::shared_ptr<Person> m_partner; // initially created empty
    public:
        Person(const std::string &name): m_name(name)
        { std::cout << m_name << " created\n"; }
        ~Person()
        { std::cout << m_name << " destroyed\n"; }
        friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2){
            if (!p1 || !p2) return false;
            p1->m_partner = p2;
            p2->m_partner = p1;
            std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';
            return true;
        }
    };
	auto lucy { std::make_shared<Person>("Lucy") }; // create a Person named "Lucy"
	auto ricky { std::make_shared<Person>("Ricky") }; // create a Person named "Ricky"
	partnerUp(lucy, ricky); // Make "Lucy" point to "Ricky" and vice-versa
    // prints :-
    // Lucy created
    // Ricky created
    // Lucy is now partnered with Ricky
    // No deallocation, as ricky goes out of scope, but doesn't deallocate because lucy's m_partner still exist
    // lucy goes out of scope, but doesn't deallocate because ricky's m_partner still exist
    
    // Circular reference - each object references the next
	ptr1->m_ptr = ptr1; // m_ptr is now sharing the Resource that contains it, won't deallocate either

    // std::weak_ptr - observe and access the same object as a std::shared_ptr (or other std::weak_ptrs) but not considered an owner
    class Person{
        std::string m_name;
        std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr
    public:
        Person(const std::string &name): m_name(name)
        { std::cout << m_name << " created\n"; }
        ~Person()
        { std::cout << m_name << " destroyed\n"; }
        friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2) {
            if (!p1 || !p2) return false;
            p1->m_partner = p2;
            p2->m_partner = p1;
            std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';
            return true;
        }
    };
	auto lucy { std::make_shared<Person>("Lucy") };
	auto ricky { std::make_shared<Person>("Ricky") };
	partnerUp(lucy, ricky);
    // Lucy created
    // Ricky created
    // Lucy is now partnered with Ricky
    // Ricky destroyed
    // Lucy destroyed

    // std::weak_ptr are not directly usable (have no operator->) - must first convert to std::shared_ptr
    class Person{
        std::string m_name;
        std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr
    public:
        std::shared_ptr<Person> getPartner() const { return m_partner.lock(); } // use lock() to convert weak_ptr to shared_ptr
        const std::string& getName() const { return m_name; }
    };
	partnerUp(lucy, ricky);
	auto partner = ricky->getPartner(); // get shared_ptr to Ricky's partner
	std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';

    // to test whether a std::weak_ptr is valid - use the expired() member function
    // returns true if the std::weak_ptr is pointing to an invalid object, and false otherwise
	std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");
}
{   // <----------- 22.x ------------>
}
    return 0;
}