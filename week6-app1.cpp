#include <iostream>
#include <vector>
#include <list>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

// uniform initialization
// initializer_list

// filter algorithm
// trailing return
// containers, iterators, begin, end
// range_for

// ++variable vs variable++

// function pointers, function objects, lambdas

struct Foo
{
    int value[3] = {0, 0, 0};

    Foo()                           { cout << "Foo()" << endl; }
    Foo(int)                        { cout << "Foo(int)" << endl; }
    Foo(int, int)                   { cout << "Foo(int, int)" << endl; }
    Foo(int, int, int)              { cout << "Foo(int, int, int)" << endl; }
    Foo(initializer_list<int> il)   { cout << "Foo(initializer_list<int>)" << endl; }

    ~Foo() { cout << "d-tor" << endl; }
};

bool is_even(int value) { return value % 2 == 0; }

bool is_divisible_by_3(int value) { return value % 3 == 0; }

bool is_divisible_by(int value, int by) { return value % by == 0; }

//typedef bool(*FuncType)(int);
using FuncType = bool(*)(int);
using DivisibleByType = bool(*)(int, int);

struct IsDivisibleBy
{
    int by;
//    IsDivisibleBy(int by) : by{by} { }
    bool operator() (int value) const { return value % this->by == 0; }
};

//struct IsGreaterThan
//{
//    double what;
//    bool operator() (double value) const { return value > this->what; }
//};

template<typename Container, typename Func>
auto filter(const Container& v, const Func& func) // -> vector<int>
{
    auto v_even = Container{};
//    for(auto it = v.begin(); it != v.end(); ++it)
//    {
//        int item = *it;
//        if(func(item))
//            v_even.push_back(item);
//    }
    for(auto item : v) // range-for loop
    {
        if(func(item))
            v_even.push_back(item);
    }
    return v_even;
}


int main(int argc, char* argv[])
{
    auto f0 = Foo{};
    auto f1 = Foo{1};
    auto f2 = Foo(1, 2);
    auto f3 = Foo{1, 2, 3, 4, 5};

    auto v1 = vector<int>(5); // vector of 5 integers, default constructed
    auto v2 = vector<int>{5}; // vector of 1 integer with value 5
    auto v3 = vector<int>{1, 2, 3, 4, 5}; // vector of 5 integers with values 1,2,3,4,5 respectively
    auto v4 = list<double>{1.1, 2.2, 3.3, 4.4, 5.5}; // vector of 5 integers with values 1,2,3,4,5 respectively

//    auto v3_filtered = filter(v3, IsDivisibleBy{4});
    auto v3_filtered = filter(v3, [](int value) { return value % 4 == 0; });
    for(const auto& item : v3_filtered)
        cout << item << " ";
    cout << endl;

//    auto v4_filtered = filter(v4, IsGreaterThan{3.0});
    auto v4_filtered = filter(v4, [what=3.0](double value) { return value > what; });
    for(const auto& item : v4_filtered)
        cout << item << " ";
    cout << endl;

//    auto v_filtered = filter(v3, &is_divisible_by_3);
//    auto v_filtered = filter(v3, &is_divisible_by, 5);

//    for(auto it=v_filtered.begin(); it!=v_filtered.end(); ++it)
//        cout << *it << " ";

    return 0;
}
