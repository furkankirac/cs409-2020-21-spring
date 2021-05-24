// SFINAE: Substitution Failure Is Not An Error (mostly obsolete due to concepts support)
// static polymorphism: Curiously Recurring Template Pattern (CRTP)
// decltype(auto)
// member function pointers, member attribute pointers
// std::apply
// capturing parameter-packs in lambdas

#include <iostream>

using namespace std;

template<typename ...> struct TD;

template<bool, typename T>      struct enableIf { };
template<typename T>            struct enableIf<true, T> { using type = T; };

//// make this accept only integral numbers
template<typename T>
typename enableIf<is_integral_v<T>, void>::type print(T i)
{
    cout << "integral value:" << i << endl;
}

//// make this accept only floating point numbers
template<typename T>
typename enableIf<is_floating_point_v<T>, void>::type print(T f)
{
    cout << "floating point value:" << f << endl;
}


int main(int argc, char* argv[])
{
//    auto a = enableIf<true, int>::type{};
//    auto b = enableIf<false, int>::type{};


    return 0;
}
