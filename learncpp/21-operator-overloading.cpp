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
    
}
{   // <----------- 21.4 ------------>

}
{   // <----------- 21.5 ------------>

}
{   // <----------- 21.6 ------------>

}
{   // <----------- 21.7 ------------>

}
{   // <----------- 21.8 ------------>
    
}
{   // <----------- 21.9 ------------>

}
{   // <----------- 21.10 ------------>

}
{   // <----------- 21.11 ------------>

}
{   // <----------- 21.12 ------------>

}
{   // <----------- 21.13 ------------>

}
{   // <----------- 21.14 ------------>

}
{   // <----------- 21.x ------------>

}
{   // <----------- 21.y ------------>

}
    return 0;
}