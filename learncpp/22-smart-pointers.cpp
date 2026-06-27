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
    
}
{   // <----------- 22.5 ------------>

}
{   // <----------- 22.6 ------------>

}
{   // <----------- 22.7 ------------>

}
{   // <----------- 22.x ------------>

}
    return 0;
}