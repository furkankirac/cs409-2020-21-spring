// explicit c-tors
// overloading casting operators of a struct
// explicit casting operators
// return type resolver trick with a proxy struct instance returned

// parameter type binding exercises
// move semantics pitfalls

// different versions of variadic print function, first-to-last, last-to-first
// fold expressions: comma operator, = operator tricks
// requires clause, requires expression, requires requires!

// class template type deductions
// deduction guides

// tuple and its implementation
// std::integer_sequence, std::index_sequence

// member function pointers
// std::invoke
// std::invocable<T, Args...>

// overloading lambdas
// union, variant, std::visit

#include <iostream>
#include <string>

using namespace std;

template<typename ...> struct TD;

struct Foo
{
    string s;

    Foo(int i) : s{std::to_string(i)} { }
    Foo(const string& s) : s{s} { }
    Foo(string&& s) : s{move(s)} { }

    operator int() const { return 1234; }
    operator float() const { return 6.28f; }

//    auto operator=(const Foo&) { ... }
};

auto bar()
{
    return Foo{1};
}

int main()
{
    string s = "Hello";  // "Hello" is const char[6] --> can be represented by const char*
    auto foo1 = Foo{s};
    auto foo2 = Foo{string("Hello")};
    auto foo3 = Foo{3};

    cout << foo1.s << endl;
    cout << foo2.s << endl;
    cout << foo3.s << endl;

    foo3 = string("Hi There"); // implicit c-tor call
    cout << foo3.s << endl;

//    auto f = 3.14f;
//    auto i = (int)f;

    auto k = (int)foo1;
    int l = foo1; // implicit cast
    float f = foo1; // implicit cast
    cout << l << endl;
    cout << f << endl;

    int i2 = bar();
    float f2 = bar();
    auto x = bar(); // x is a Foo instance

    return 0;
}
