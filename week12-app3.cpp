// decltype(auto)
// std::apply
// capturing parameter-packs in lambdas

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <type_traits>

template<typename...> struct TD;

auto get_int_byval() -> int { int i = 5; return i; }
auto get_int_byref() -> int& { static int i = 5; return i; }

struct Func
{
    template<typename Callable>
    auto operator() (Callable callable) const {
        return callable();
    }
};


int main(int argc, char* argv[])
{
    // function object Func taking a callable returning auto


    // lambda version returning decltype(auto)

    auto i1 = get_int_byval(); // int
    auto i2 = get_int_byref(); // int

    decltype(auto) i3 = get_int_byval(); // int
    decltype(auto) i4 = get_int_byref(); // int&

    auto func1 = Func{};
    decltype(auto) j1 = func1(&get_int_byval); // int
    decltype(auto) j2 = func1(&get_int_byref); // int

    auto func2 = [](auto callable) -> decltype(auto) {
        return callable();
    };
    decltype(auto) k1 = func2(&get_int_byval); // int
    decltype(auto) k2 = func2(&get_int_byref); // int&
//    TD< decltype(k1), decltype(k2) > a;

    return 0;
}
