#include <iostream>

// Core Language Features:
// type-alias: typedef (C), using (modern C++)
// constness
// pointers, nullptr and const
// references
// references and const
// function / operator overloading
// function objects

// Generic Programming Paradigm:
// templates, function templates, class templates, variable templates, type-alias templates

// Object Oriented Paradigm:
// ctor/dtor
// copy-ctor, copy-assignment
// move-ctor, move-assignment
// inheritance

#include <iostream>

void run()
{

}


int main(int argc, char* argv[])
{
    // type aliasing, creating new types from already available ones (primitive or more sophisticated)
    int a;
    float f;
    struct { int a; float f; } s1;
    struct { int a; float f; } s2;

    typedef struct { int a; float f; } S;
    S s3;
    S s4;

    struct SS { int a; float f; };

    struct FF { SS ss; double d; };

    typedef int INT; // creates a type alias INT from the left side (int)
    using INT = int; // modern C++
    // Dennis Ritchie (passed away in 2011)

    return 0;
}
