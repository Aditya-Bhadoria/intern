#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
{   // <----------- 21.1 ------------>
    // 1st - can only overload the operators that exist
    // 2nd - at least one of the operands in an overloaded operator must be a user-defined type
    // could overload operator+(int, Mystring), but not operator+(int, double)
    // 3rd - not possible to change the number of operands an operator supports
    // 4th - all operators keep their default precedence and associativity
}
{   // <----------- 21.2 ------------>
    class Cents {
    private: int m_cents {};
    public: Cents(int cents) : m_cents{ cents } {}
        // add Cents + Cents using a friend function
        friend Cents operator+(const Cents& c1, const Cents& c2);
        // subtract Cents - Cents using a friend function
        // This function is not considered a member of the class, even though the definition is inside the class
        friend Cents operator-(const Cents& c1, const Cents& c2){
            return Cents { c1.m_cents - c2.m_cents }; 
        }
        int getCents() const { return m_cents; }
    };
    // note: this function is not a member function!
    Cents operator+(const Cents& c1, const Cents& c2){
        // use the Cents constructor and operator+(int, int)
        // we can access m_cents directly because this is a friend function
        return c1.m_cents + c2.m_cents;
    }
    Cents cents1{ 6 };
    Cents cents2{ 8 };
    Cents centsSum{ cents1 + cents2 };
    std::cout << "I have " << centsSum.getCents() << " cents.\n";
    
    // add Cents + int using a friend function
    friend Cents operator+(const Cents& c1, int value);
    // add int + Cents using a friend function
    friend Cents operator+(int value, const Cents& c1);
    Cents c1{ Cents{ 4 } + 6 };
    Cents c2{ 6 + Cents{ 4 } };
}
{   // <----------- 21.3 ------------>
    // if you don’t need private access, can write overloaded operators as normal functions
    class Cents{
    private:
        int m_cents{};
    public:
        Cents(int cents) : m_cents{ cents } {}
        int getCents() const { return m_cents; }
    };
    // note: this function is not a member function nor a friend function!
    Cents operator+(const Cents& c1, const Cents& c2){
        // use the Cents constructor and operator+(int, int)
        // we don't need direct access to private members here
        return Cents{ c1.getCents() + c2.getCents() };
    }
}
{   // <----------- 21.4 ------------>
    class Point{
    private:
        double m_x{}, m_y{}, m_z{};
    public:
        Point(double x=0.0, double y=0.0, double z=0.0) : m_x{x}, m_y{y}, m_z{z} {}
        friend std::ostream& operator<< (std::ostream& out, const Point& point);
    };
    // std::ostream is the type for object std::cout
    std::ostream& operator<< (std::ostream& out, const Point& point) {
        // Since operator<< is a friend of the Point class, we can access Point's members directly.
        out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')'; // actual output done here
        return out; // return std::ostream so we can chain calls to operator<<
    }
    const Point point1 { 2.0, 3.0, 4.0 };
    std::cout << point1 << '\n';
    // if return std::ostream by value - compiler error, because std::ostream specifically disallows being copied
    
    // note that point must be non-const so we can modify the object
    std::istream& operator>> (std::istream& in, Point& point) {
        // This version subject to partial extraction issues (see below)
        in >> point.m_x >> point.m_y >> point.m_z;
        return in;
    }
    Point point{ 1.0, 2.0, 3.0 }; // non-zero test data
    std::cin >> point;                             // if input = {4.0b 5.6 7.26}
    std::cout << "You entered: " << point << '\n'; // You entered: Point(4, 0, 3)
    
    // A transactional operation must either completely succeed or completely fail
    // note that point must be non-const so we can modify the object
    // note that this implementation is a non-friend
    std::istream& operator>> (std::istream& in, Point& point){
        double x{}, y{}, z{};
        if (in >> x >> y >> z)      // if all extractions succeeded
            point = Point{x, y, z}; // overwrite our existing point
        // Alternate version :-
        in >> x >> y >> z;
        point = in ? Point{x, y, z} : Point{};
        // error handling
        in >> x >> y >> z;
        if (x < 0.0 || y < 0.0 || z < 0.0)       // if any extractable input is negative
            in.setstate(std::ios_base::failbit); // set failure mode manually
        point = in ? Point{x, y, z} : Point{};
    
        return in;
    }
}
{   // <----------- 21.5 ------------>
    class Cents{
    private:
        int m_cents {};
    public:
        Cents(int cents) : m_cents { cents } { }
        // Overload Cents + int
        Cents operator+(int value) const;
        int getCents() const { return m_cents; }
    };
    // note: this function is a member function!
    // the cents parameter in the friend version is now the implicit *this parameter
    Cents Cents::operator+ (int value) const { return Cents { m_cents + value }; }

	const Cents cents1 { 6 };
	const Cents cents2 { cents1 + 2 };

    // assignment (=), subscript ([]), function call (()), and member selection (->) operators must be overloaded as member functions
}
{   // <----------- 21.6 ------------>
    class Cents{
        Cents(int cents): m_cents{cents} {}
        // Overload -Cents as a member function
        Cents operator-() const;
    };
    // note: this function is a member function!
    Cents Cents::operator-() const
    { return -m_cents; } // since return type is a Cents, this does an implicit conversion from int to Cents using the Cents(int) constructor

    class Point {
    private:
        double m_x {}, m_y {}, m_z {};
    public:
        Point(double x=0.0, double y=0.0, double z=0.0) : m_x{x}, m_y{y}, m_z{z} {}
        // Convert a Point into its negative equivalent
        Point operator- () const;
        // Return true if the point is set at the origin
        bool operator! () const;
    };
    // Convert a Point into its negative equivalent
    Point Point::operator- () const { return { -m_x, -m_y, -m_z }; }
    // Return true if the point is set at the origin, false otherwise
    bool Point::operator! () const { return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0); }

    Point point{}; // use default constructor to set to (0.0, 0.0, 0.0)
    if (!point) std::cout << "point is set at the origin.\n";
}
{   // <----------- 21.7 ------------>
    class Car {
    private:
        std::string m_make;
        std::string m_model;
    public:
        Car(std::string_view make, std::string_view model) : m_make{ make }, m_model{ model } {}
        friend bool operator== (const Car& c1, const Car& c2);
        friend bool operator!= (const Car& c1, const Car& c2);

    };
    bool operator== (const Car& c1, const Car& c2) {
        return (c1.m_make == c2.m_make && c1.m_model == c2.m_model);
    }
    bool operator!= (const Car& c1, const Car& c2) {
        return (c1.m_make != c2.m_make || c1.m_model != c2.m_model);
    }
    // more examples
    bool operator> (const Cents& c1, const Cents& c2) { return c1.m_cents > c2.m_cents; }
    bool operator< (const Cents& c1, const Cents& c2) { return c1.m_cents < c2.m_cents; }
    bool operator<= (const Cents& c1, const Cents& c2) { return c1.m_cents <= c2.m_cents; }
    bool operator>= (const Cents& c1, const Cents& c2) { return c1.m_cents >= c2.m_cents; }

    // see changes - Minimizing comparative redundancy
    friend bool operator== (const Cents& c1, const Cents& c2) { return c1.m_cents == c2.m_cents; }
    friend bool operator!= (const Cents& c1, const Cents& c2) { return !(operator==(c1, c2)); }

    friend bool operator< (const Cents& c1, const Cents& c2) { return c1.m_cents < c2.m_cents; }
    friend bool operator> (const Cents& c1, const Cents& c2) { return operator<(c2, c1); }

    friend bool operator<= (const Cents& c1, const Cents& c2) { return !(operator>(c1, c2)); }
    friend bool operator>= (const Cents& c1, const Cents& c2) { return !(operator<(c1, c2)); }
}
{   // <----------- 21.8 ------------>
    class Digit {
    private:
        int m_digit{};
    public:
        Digit(int digit=0) : m_digit{digit} {}
        Digit& operator++(); // prefix has no parameter
        Digit& operator--(); // prefix has no parameter

        Digit operator++(int); // postfix has an int parameter
        Digit operator--(int); // postfix has an int parameter
        friend std::ostream& operator<< (std::ostream& out, const Digit& d);
    };
    Digit& Digit::operator++(){
        // If our number is already at 9, wrap around to 0
        if (m_digit == 9) m_digit = 0;
        else ++m_digit; // otherwise just increment to next number
        return *this;
    }
    Digit& Digit::operator--(){
        if (m_digit == 0) m_digit = 9;
        else --m_digit;
        return *this;
    }
    // int parameter means this is postfix operator++
    Digit Digit::operator++(int) {
        Digit temp{*this}; // Create a temporary variable with our current digit
        // Use prefix operator to increment this digit
        ++(*this); // apply operator
        // return temporary result
        return temp; // return saved state
    }
    // int parameter means this is postfix operator--
    Digit Digit::operator--(int) {
        Digit temp{*this}; // Create a temporary variable with our current digit
        // Use prefix operator to decrement this digit
        --(*this); // apply operator
        // return temporary result
        return temp; // return saved state
    }
    std::ostream& operator<< (std::ostream& out, const Digit& d) {
        out << d.m_digit;
        return out;
    }
    Digit digit { 8 };
    std::cout << digit << ++digit; // calls Digit::operator++();
    std::cout << digit++; // calls Digit::operator++(int);
    std::cout << digit << --digit; // calls Digit::operator--();
    std::cout << digit--; // calls Digit::operator--(int);
    std::cout << digit;     // prints -> 5667665
}
{   // <----------- 21.9 ------------>
    class IntList {
    private:
        int m_list[10]{};
    public:
        int& operator[] (int index) { 
            if (!(index >= 0 && static_cast<std::size_t>(index) < std::size(m_list)))
            { /* handle invalid index here */ } // checks bound
            return m_list[index]; 
        }
    };
    IntList list{};
    list[2] = 3; // set a value
    std::cout << list[2] << '\n'; // get a value
    
    // For const objects: can only be used for access
    // This function could also return by value if the type is cheap to copy
    const int& operator[] (int index) const { return m_list[index]; }
    const IntList clist{};
    // clist[2] = 3; // compile error: clist[2] returns const reference, which we can't assign to

    // Use an explicit object parameter (self) and auto&& to differentiate const vs non-const
    auto&& operator[](this auto&& self, int index){
        // Complex code goes here
        return self.m_list[index];
    }
    list[2] = 3; // okay: calls non-const version of operator[]
    // clist[2] = 3; // compile error: clist[2] returns const reference, which we can't assign to

    // Make sure you’re not trying to call an overloaded operator[] on a pointer to an object.
    IntList* list{ new IntList{} };
    (*list)[2] = 3; // get our IntList object, then call overloaded operator[]
    delete list;
}
{   // <----------- 21.10 ------------>
    class Matrix{
    private:
        double m_data[4][4]{};
    public:
        double& operator()(int row, int col);
        void operator()();
    };
    double& Matrix::operator()(int row, int col){
        assert(row >= 0 && row < 4);
        assert(col >= 0 && col < 4);
        return m_data[row][col];
    }
    void Matrix::operator()(){
        // reset all elements of the matrix to 0.0
        for (int row{ 0 }; row < 4; ++row)
            for (int col{ 0 }; col < 4; ++col)
                m_data[row][col] = 0.0;
    }
    Matrix matrix;
    matrix(1, 2) = 4.5;
    matrix(); // erase matrix

    // Having fun with functors
    class Accumulator {
    private:
        int m_counter{ 0 };
    public:
        int operator() (int i) { return (m_counter += i); }
        void reset() { m_counter = 0; } // optional
    };
    Accumulator acc{};
    std::cout << acc(1) << '\n'; // prints 1
    std::cout << acc(3) << '\n'; // prints 4
}
{   // <----------- 21.11 ------------>
    // Overloaded int cast
    operator int() const { return m_cents; }
    // Overloaded typecasts must be non-static members, and should be const
    // Overloaded typecasts do not have explicit parameters
    // Overloaded typecast do not declare a return type, the name of the conversion is the return type
    class Cents {
    private:
        int m_cents{};
    public:
        // Overloaded int cast
        operator int() const { return m_cents; }
    };
    class Dollars {
    private:
        int m_dollars{};
    public:
        Dollars(int dollars=0) : m_dollars{ dollars } {}
        // Allow us to convert Dollars into Cents
        operator Cents() const { return Cents { m_dollars * 100 }; }
    };
    void printCents(Cents cents) { std::cout << cents; } // cents will be implicitly cast to an int here
    Dollars dollars{ 9 };
    printCents(dollars); // dollars will be implicitly cast to a Cents here
    // Explicit typecast
    explicit operator int() const { return m_cents; } // now marked as explicit
    void printCents(Cents cents){
    //  std::cout << cents;                   // no longer works because cents won't implicit convert to an int
        std::cout << static_cast<int>(cents); // we can use an explicit cast instead
    }

    // When possible, prefer converting constructors, and avoid overloaded typecasts.
    // There are a few cases where an overloaded typecast should be used instead:
    // When providing a conversion to a fundamental type
    // When the conversion returns a reference or const reference
    // When providing a conversion to a type you can’t add members to (e.g. a conversion to std::vector)
    // When you do not want the type being constructed to be aware of the type being converted from
}
{   // <----------- 21.12 ------------>
    class Fraction {
    private:
        int m_numerator { 0 };
        int m_denominator { 1 };
    public:
        // Default constructor
        Fraction(int numerator = 0, int denominator = 1 )
            : m_numerator { numerator }, m_denominator { denominator }
        { assert(denominator != 0); }
        // Copy constructor
        Fraction(const Fraction& copy)
            : m_numerator { copy.m_numerator }, m_denominator { copy.m_denominator }
        {
            // no need to check for a denominator of 0 here since copy must already be a valid Fraction
            std::cout << "Copy constructor called\n"; // just to prove it works
        }
        // Overloaded assignment
        Fraction& operator= (const Fraction& fraction);
        friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
    };
    // A simplistic implementation of operator= (see better implementation below)
    Fraction& Fraction::operator= (const Fraction& fraction){
        // do the copy
        m_numerator = fraction.m_numerator;
        m_denominator = fraction.m_denominator;
        // return the existing object so we can chain this operator
        return *this;
    }

    // Detecting and handling self-assignment
    MyString& MyString::operator= (const MyString& str){
        // self-assignment check
        if (this == &str) return *this;
        // if data exists in the current string, delete it
        if (m_data) delete[] m_data;
        m_length = str.m_length;
        m_data = nullptr;
        // allocate a new array of the appropriate length
        if (m_length) m_data = new char[static_cast<std::size_t>(str.m_length)];
        std::copy_n(str.m_data, m_length, m_data); // copies m_length elements of str.m_data into m_data
        // return the existing object so we can chain this operator
        return *this;
    }

    class Fraction {
    public:
        // Default constructor
        Fraction(int numerator = 0, int denominator = 1)
            : m_numerator { numerator }, m_denominator { denominator }
        { assert(denominator != 0); }
        Fraction(const Fraction &copy) = delete; // Copy constructor
        // Overloaded assignment
        Fraction& operator= (const Fraction& fraction) = delete; // no copies through assignment!
    };
    Fraction fiveThirds { 5, 3 };
    Fraction f;
    f = fiveThirds; // compile error, operator= has been deleted
}
{   // <----------- 21.13 ------------>
    // shallow copy - copies each member of the class individually using the assignment operator for overloaded operator=
    class MyString {
    private:
        char* m_data{};
        int m_length{};
    public:
        MyString(const char* source = "" ){
            assert(source); // make sure source isn't a null string
            m_length = std::strlen(source) + 1;
            m_data = new char[m_length];
            // Copy the parameter string into our internal buffer
            for (int i{ 0 }; i < m_length; ++i) m_data[i] = source[i];
        }
        ~MyString()  // destructor
        { delete[] m_data; } // We need to deallocate our string

        char* getString() { return m_data; }
        int getLength() { return m_length; }
    };
    MyString hello{ "Hello, world!" };
    {
        MyString copy{ hello }; // use default copy constructor
    } // copy gets destroyed here.  The destructor deletes copy's string, which leaves hello with a dangling pointer
    std::cout << hello.getString() << '\n'; // this will have undefined behavior

    // deep copy - allocates memory for the copy and then copies the actual value, so copy lives in distinct memory from the source
    // assumes m_data is initialized
    void MyString::deepCopy(const MyString& source){
        delete[] m_data; // first we need to deallocate any value that this string is holding!
        m_length = source.m_length; // because m_length is not a pointer, we can shallow copy it
        // m_data is a pointer, so we need to deep copy it if it is non-null
        if (source.m_data) {
            m_data = new char[m_length]; // allocate memory for our copy
            // do the copy
            for (int i{ 0 }; i < m_length; ++i) m_data[i] = source.m_data[i];
        }
        else m_data = nullptr;
    }
    // Copy constructor
    MyString::MyString(const MyString& source) { deepCopy(source); }
    // Assignment operator
    MyString& MyString::operator=(const MyString& source){
        // check for self-assignment
        if (this != &source){ deepCopy(source); } // now do the deep copy
        return *this;
    }
}
{   // <----------- 21.14 ------------>
    class Cents {
    private:
        int m_cents {};
    public:
        Cents(int cents) : m_cents { cents } {}
        friend bool operator< (const Cents& c1, const Cents& c2) // got to overload, otherwise template give compile error
        { return (c1.m_cents < c2.m_cents); } 
        friend std::ostream& operator<< (std::ostream& ostr, const Cents& c) {
            ostr << c.m_cents; return ostr;
        }
    };
    template <typename T>
    const T& max(const T& x, const T& y)
    { return (x < y) ? y : x; }
    Cents nickel{ 5 };
    Cents dime { 10 };
    Cents bigger { max(nickel, dime) };
    std::cout << bigger << " is bigger\n";

    template <typename T>
    T average(const T* myArray, int numValues){
        T sum { 0 };
        for (int count { 0 }; count < numValues; ++count) sum += myArray[count];
        sum /= numValues;
        return sum;
    }
    class Cents{
    public:
        friend std::ostream& operator<< (std::ostream& out, const Cents& cents) 
        { out << cents.m_cents << " cents "; return out; }
        Cents& operator+= (const Cents &cents) { m_cents += cents.m_cents; return *this; }
        Cents& operator/= (int x) { m_cents /= x; return *this; }
    };
    Cents centsArray[] { Cents { 5 }, Cents { 10 }, Cents { 15 }, Cents { 14 } };
    std::cout << average(centsArray, 4) << '\n';
}
{   // <----------- 21.x ------------>
    // something cool
}
{   // <----------- 21.y ------------>
    // something Cooler [DBZ Reference]
}
    return 0;
}