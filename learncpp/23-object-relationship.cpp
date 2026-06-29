#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    // !!!!!!!! OVERVIEW !!!!!!!!

{   // <----------- 23.1 ------------>
    // son son son sahur
}
{   // <----------- 23.2 ------------>
    // Object Composition - process of building complex objects by combining smaller, simpler ones.
    // It models a "has-a" relationship (e.g., a Car has-a transmission, a Creature has-a location).
    // The complex object is called the whole (or parent), and the simpler object is called the part (or child/component).

    // Part-of: The component must physically or logically constitute a part of the whole object.
    // Single Ownership: A part can only belong to one parent object at a time.
    // Lifetime Management: The parent completely manages the part's existence. The part is usually created when the 
    // parent is created and destroyed when the parent is destroyed. Because of this dependency, it is often called a "death relationship".
    // Unidirectional: The relationship is one-way. The parent knows about the part, but the part operates blissfully unaware of the parent's existence.
}
{   // <----------- 23.3 ------------>
    // aggregation :-
    // The part is - part of the object, can (if desired) belong to more than one object, 
    // does not have its existence managed by the object, does not know about the existence of the object
}
{   // <----------- 23.4 ------------>
    // association :-
    // The associated object - is otherwise unrelated to the object, can belong to more than one object, 
    // does not have its existence managed by the object, may or may not know about the existence of the object
    // reflexive association - Sometimes objects may have a relationship with other objects of the same type
}
{   // <----------- 23.5 ------------>
    // dependency - one object invokes another object’s functionality in order to accomplish some specific task
    // always a unidirectional relationship 💔
}
{   // <----------- 23.6 ------------>
    // container class - designed to hold and organize multiple instances of another type
    // Value containers - store copies of the objects that they are holding - responsible for creating and destroying those copies
    // Reference containers - store pointers or references to other objects - not responsible for creation or destruction of those objects
}
{   // <----------- 23.7 ------------>
	int array[] { 5, 4, 3, 2, 1 }; // initializer list

    #include <initializer_list> // for std::initializer_list
    class IntArray{
    private:
        int m_length {};
        int* m_data{};
    public:
        IntArray() = default;
        IntArray(int length) : m_length{ length } , m_data{ new int[static_cast<std::size_t>(length)] {} }{}
        IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
            : IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
        { std::copy(list.begin(), list.end(), m_data); } // Now initialize our array from the list
        // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
        ~IntArray() { delete[] m_data; }
        IntArray(const IntArray&) = delete; // to avoid shallow copies
        IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies
        int& operator[](int index) {
            assert(index >= 0 && index < m_length);
            return m_data[index];
        }
        int getLength() const { return m_length; }
    };
	IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
	for (int count{ 0 }; count < array.getLength(); ++count) std::cout << array[count] << ' ';
}
{   // <----------- 23.x ------------>
}
    return 0;
}