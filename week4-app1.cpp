#include <iostream>

// auto
// default argument/parameter values
// default ctor
// default attribute values

// malloc/free - this is C dynamic memory allocation
// new/delete - not modern C++ / this is old C++
// std::vector
// std::vector<Foo>

// operator overloading
// function-call operator
// function objects

// getter, setter
// l-value, r-value
// returning a reference

// move-ctor, move-assignment
// inheritance

#include <iostream>
#include <string>
#include <vector>

using INT = int; // type aliasing
using namespace std; // namespace import into our namespace. do not ever use this in a header file!

void log(int arg1, string arg3)
{
    cout << "arg1 = " << arg1 << endl;
    cout << "arg3 = " << arg3 << endl;
}

void log(int arg1, float arg2=3.14f, string arg3="")
{
    cout << "arg1 = " << arg1 << endl;
    cout << "arg2 = " << arg2 << endl;
    cout << "arg3 = " << arg3 << endl;
}

struct Foo
{
    int value = 0; // if any ctor doesn't init this attrib. consider it as zero
    vector<int> dynamic_memory;

//    int* dynamic_memory = nullptr;

    Foo() : value(100), dynamic_memory(1000)
    {
//        allocate();
    }

    Foo(int value) : value(value), dynamic_memory(1000)
    {
//        allocate();
    }

//    void allocate()
//    {
//        dynamic_memory = new int[1000]; // heap allocation
//        dynamic_memory[0] = 10;
//        dynamic_memory[1] = 100;
//    }


    ~Foo()
    {
//        delete[] dynamic_memory; // delete[] is different than delete. new[] requires delete[] to be called.
        cout << "Foo is destructed" << endl;
    }
//    ~Foo() { } // default destructor created by the compiler if yo don't declare a destructor
};

void do_smt()
{
    auto i = 5; // type if automatically deduced for you by looking at the right hand side of the expression
    auto f = Foo(); // almost always auto AAA
    auto f2 = Foo(1000);

    auto vfoo = vector<Foo>(10);

    cout << "Default ctor value = " << f.value << endl;

    log(100, 3.14f, string("do_smt")); // int, float, char const *

    cout << "Leaving do_smt" << endl;
    // here the destructor of Foo gets called for destroying f
    // destroying i is trivial. it's primitive type. freeing the stack frame memory already destroys it.
    // hence, no dtor gets called.
}

int main(int argc, char* argv[])
{
    do_smt();

//    int* p = (int*)malloc(1000*sizeof(int)); // dynamic mem alloc in C style for 1000 integers
//    free(p);

//    Foo* foo_memory = (Foo*)malloc(sizeof(Foo)); // dynamic mem alloc in C style for 1000 integers
//    foo_memory->value = 100;
//    foo_memory->allocate();

    //    vector<int> vi = vector<int>(1000);
    auto vi = vector<int>(1000);
    vi[0] = 10;
    vi[1] = 100;



//    log(10, 3.14f, string("main")); // int, float, char const *
//    log(10, 3.14f); // int, float, char const *
//    log(3.14f); // 3.14f is automatically down-casted by truncation to an integer 3!
    log(5, "hello"); // the 2nd overload of log gets called

    return 0;
}
