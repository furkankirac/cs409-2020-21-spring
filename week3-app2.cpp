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

struct Movie
{
    int genre;
    int year;
};


void run()
{
//    Movie m1;

//    Movie* mp = &m1;

//    Movie& mref = m1;

//    (*mp).genre = 1;
//    mp->genre = 1;

//    mref.genre = 2;

    int a = 3; // in the stack memory of main functions's stack-frame
    int b = 5;

    float const pi = 3.14f; // east const

    // p1 is an integer pointer. p1 is a variable storing a memory address.
    // in that memory address there is at least one integer
    int * p1 = &a; // = nullptr;

    p1 = &a;
    p1[0]++;
//    (*p1)++;
    std::cout << a << std::endl;
    // ...

//    p1 = &b;
////    (*p1)++;
//    std::cout << a << std::endl;
//    std::cout << b << std::endl;


    const int & ref = a;
    //ref++;
    a+=100;
    std::cout << ref << std::endl;

//    ref = b;

    // ...


}


int main(int argc, char* argv[])
{
    int k = 5;

    run();

    return 0;
}
