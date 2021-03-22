// l-value, r-value
// bindings:
//  l-value ref to l_value           - works
//  l-value ref to r_value           - does not work
//  const l-value ref to l_value     - works
//  const l-value ref to r_value     - works
//  copy by value with l_value       - works
//  copy by value with r_value       - works

// a stack<T> implementation
// move-ctor, move-assignment

#include <iostream>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

void foo(int& value) // this binds to l-value things with a reference
{
    cout << "int& : " << value << endl;
}

void foo(const int& value)
{
    cout << "const int& : " << value << endl;
}

void foo(int&& value) // this binds to r-value things with a reference
{
    value++;
    cout << "int&& : " << value << endl;
}

//void foo(int value) // this binds to all kinds of things
//{
//    cout << "int : " << value << endl;
//}

int main(int argc, char* argv[])
{
    // l-value is a memory container given a name which holds a value
    // r-value is only the value (there a temporary)

//    int x = 5;
//    foo(x);

    foo(5);

    return 0;
}
