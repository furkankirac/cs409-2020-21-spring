// designated initializers

// range-for initializer

// NTTP (Non-type template params)

// constexpr functions
// consteval functions
// constinit

// volatile

// some features that a select few know
// - pointer arithmetic, array access implementation
// - try-catch-throw, "function level try-catch!", noexcept

#include <iostream>
#include <map>

using namespace std;

struct Foo
{
    int i;
    double d;
    float f;
};

struct Data
{
    std::map<int, string> values;
// ....
    auto data_pairs() const
    {
        return values;
    }
};

Data getData() { return Data{}; }

int long_running_func()
{
    // ....
    return 1000;
}

int main()
{
    //    auto foo = Foo{.i=100, .f=3.14f}; // designated initializers

    int i;
    if(int j=long_running_func(); j > 100)
        i = j;

    for(auto d = getData(); auto [key, value] : d.data_pairs())
    {
    }

    auto d = 5; // d is not contaminated by the above block. we can use d now.


    return 0;
}
