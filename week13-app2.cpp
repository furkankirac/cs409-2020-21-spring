// std::integral_constant, std::true_type, std::false_type, tag dispatching

#include <iostream>

using namespace std;

struct FalseType : integral_constant<bool, false> { };
struct TrueType  : integral_constant<bool, true> { };

struct Int5_t { static const int value = 5; };


template<typename T>    struct IsIntegral : FalseType { };
template<>              struct IsIntegral<int> : TrueType { };
template<>              struct IsIntegral<short> : TrueType { };
// ...


enum Mode { Logging, Standard };

using LoggingMode = integral_constant<Mode, Logging>;
using StandardMode = integral_constant<Mode, Standard>;

void print(auto&& whatever, LoggingMode)
{
    cout << "Logging Mode\n" << whatever << endl;
}

void print(auto&& whatever, StandardMode)
{
    cout << "Standard Mode\n" << whatever << endl;
}

int main()
{
    using int5_t = integral_constant<int, 5>;

    print("blabla", LoggingMode{}); // tag dispatching
    print("blabla", StandardMode{});

    return 0;
}
