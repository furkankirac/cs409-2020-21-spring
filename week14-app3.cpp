// macros

// declval
// template of variable
// inline variables
// type erasure - std::function // duck typing

#include <iostream>
#include <functional>
#include "less_macro.hpp"

using namespace std;

#define F(x, y) cout << y << x


template<typename T>
T pi = 3.141526;

struct Foo { };

int print(Foo)
{
    return 10;
}

void filter(auto&& container, std::function<void(int)> func)
{
//    func(5);
}

int main()
{
    F(10, "Hi");
    cout << "Hi" << 10;

    auto a = std::function<void(int)>{};
//    a = &print;
//    a(5.5);


//    auto pi_float = pi<float>;
//    auto pi_double = pi<double>;

}
