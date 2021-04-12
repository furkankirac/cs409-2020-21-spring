// fold expressions

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename T> struct TypeDisplay;

template<typename T1, typename T2>  struct IsSame       { static const bool value = false; };
template<typename T>                struct IsSame<T, T> { static const bool value = true; };

template<typename T1, typename T2>
const auto IsSame_v = IsSame<T1, T2>::value;



template<typename T>    struct IsIntegral       { static const bool value = false; };
template<>              struct IsIntegral<int>  { static const bool value = true; };
template<>              struct IsIntegral<long> { static const bool value = true; };
template<>              struct IsIntegral<short>{ static const bool value = true; };
template<>              struct IsIntegral<char> { static const bool value = true; };


template<typename T_true, typename T_false, bool b>
struct ConditionalType {
    using type = T_false;
};

template<typename T_true, typename T_false>
struct ConditionalType<T_true, T_false, true>
{
    using type = T_true;
};

template<typename T_true, typename T_false, bool b>
using ConditionalType_t = ConditionalType<T_true, T_false, b>::type;

//using ConditionalType_int_float_true = int;
//using ConditionalType_int_float_false = float;


//const auto IsSame_int_int_v = true;
//const auto IsSame_int_float_v = false;
//const auto IsSame_float_double_v = false;

template<template<typename ...> typename ContainerTemplate, typename ... Ts>
void print(const ContainerTemplate<Ts...>& container)
{
    if constexpr(IsSame_v< ContainerTemplate<Ts...>, std::map<Ts...> >) // check if it is a map<...>
    {
        cout << "Found a map" << endl;
        for(const auto& [key, value] : container)
            cout << key << "," << value << " ";
        cout << endl;
    }
    else
    {
        cout << "Found a container other than map" << endl;
        for(const auto& item : container)
            cout << item << " ";
        cout << endl;
    }
}

//template<typename Key, typename Value>
//void print(const map<Key, Value>& container)
//{
//    for(const auto& [key, value] : container)
//        cout << key << "," << value << " ";
//    cout << endl;
//}

int foo()
{
    return 10, 20, 30;
}


int main(int argc, char* argv[])
{
    auto v = vector<float>{11.1f, 3.14f};
    auto m = map<int, string>{
        {1, "one"},
        {2, "two"},
    };


    int a, b, c;

    a = b = c = 100; // right-to-left assignment
    // c = 100
    // b = c
    // a = b
    cout << a << "," << b << "," << c << endl;

    cout << foo() << endl; // comma operator's usage example

//    cout << IsSame<int, int>::value << endl;
//    cout << IsSame<int, float>::value << endl;
    cout << IsSame_v<int, int> << endl;
    cout << IsSame_v<int, float> << endl;

//    using T = ConditionalType<int, double, false>::type;
    using T = ConditionalType_t<int, double, true>;
    if constexpr(IsSame_v<T, int>)
    {
        cout << "T is an integer" << endl;
    }
    else if constexpr(IsSame_v<T, double>)
    {
        cout << "T is a double" << endl;
    }

//    TypeDisplay<T> a;

    struct Foo
    {
        int value;
        Foo& operator=(const Foo& other)
        {
            value = other.value;
            return *this;
        }
    };

    Foo i;
    Foo j;
    Foo k;
    i = j = k;
    // j = k
    // i = void

    return 0;
}
