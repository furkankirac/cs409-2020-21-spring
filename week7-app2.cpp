#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

// std::map, std::pair, structured binding

// if-constexpr
// is_same<T1, T2>


// inheritance, virtual functions

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename T> struct TypeDisplay;

void print(const auto& container)
{
    for(const auto& item : container)
        cout << item << " ";
    cout << endl;
}


template<typename T, T t> void foo() { cout << t << endl; }
template<auto t> void bar() { cout << t << endl; }


int main(int argc, char* argv[])
{
//    foo<int, 10>();
//    foo<char, 'F'>();

    bar<10>();
    bar<'F'>();

    return 0;
}
