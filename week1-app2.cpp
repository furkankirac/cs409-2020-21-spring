#include <iostream>

// Brief intro. to C++ basics.

// variables and functions and scope
//   primitive types
//   local, global, static variables
//   free, member, static functions
//   function return types

// primitive types: char, int, bool, double, float, ... (because CPU knows about them in its native language)

// reflection
//   auto, sizeof, sizeof..., typeid, decltype, ...
//   reflexpr (C++23) -->> introduce us Real Reflection in C++,
//      provide us with new core-features called MetaClasses (by Herb Sutter)
// Creator of C++: Bjarne Stroustrup
// Chairman of C++: Herb Sutter (in Microsoft)

// OOP: struct, class, ctor/dtor, inheritance

#include <string>

struct Student {
    int age;
    float gpa;
    std::string name;

    Student(Student& s)
    {
        // ...
    }

    Student(int age, float gpa, std::string name)
    {
        this->age = age;
        this->gpa = gpa;
        this->name = name;
    }
};

Student s1(22, 4.0f, "Furkan");
Student s2(40, 3.5f, "Mustafa");

// this ptr, static functions
// functions vs function parameters
// methods vs objects

// C++: a VALUE SEMANTIC language. we work with THE VALUE. we can get references to the values as well.
// Java/Python/Javascript/C#...:
//   everything is allocated in the heap memory (some exceptions of course)
//   everything is accessed via a reference (REFERENCE SEMANTIC language)

// in C++:
//Integer a = 10; // create an integer in stack memory and assign 10 to it
//b = a; // this is deep-copy. you really copy the VALUE itself.
//Integer* a_ptr = new Integer; // allocate a space for single integer in heap memory
//// a_ptr could be 0x10004afc
//*a_ptr = 10; // assign 10 to it
//b_ptr = a_ptr; // you copy the pointer to the VALUE
//c = *b_ptr; // c is 10

// in Java
//Integer a = new Integer(10);
//b = a; // this is not a deep-copy most of the time, you just copy the reference/pointer


// OOP basics
// ctor/dtor
// copy-ctor, copy-assignment
// move-ctor, move-assignment (not covered in CS321)
// inheritance (not covered in CS321)

// function / operator overloading

// almost always auto - aaa rule: move type to the right
// unified/universal initialization

// namespaces
// dynamic polymorphism, v-table (default in Java, you opt-in in C++ with virtual keyword) (not covered in CS321)

int main(int argc, char* argv[])
{
    return 0;
}
