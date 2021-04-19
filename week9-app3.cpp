#include <iostream>
//#include <string>

// move semantics pitfalls

// pitfall #1:
namespace PF1
{
struct B { };
struct A
{
    B b_;

    template<typename T>
    A(T&& t) : b_{std::move(t)}
    { }
};
}

// pitfall #2:
namespace PF2
{
struct B { };
template<typename T>
struct A
{
    B b_;

    A(T&& t) : b_{std::forward<T>(t)}
    { }
};
}

// pitfall #3:
namespace PF3
{
struct B { };
struct C { };
struct A
{
    B b_;
    C c_;

    template<typename T>
    A(T&& t)
        : b_{std::forward<T>(t)}
        , c_{std::forward<T>(t)}
    {
    }
};
}


// pitfall #4:
namespace PF4
{
struct B { };
struct C { };
struct A
{
    B b_;
    C c_;

    template<typename T1, typename T2>
    A(T1&& t1, T2&& t2)
        : b_{std::forward<T1>(t1)}
        , c_{std::forward<T2>(t2)}
    {
    }
};
}

template<typename ...>
struct TypeDisplayer;

#include <type_traits>

// pitfall #5:
template<typename T>
void foo(T&&)
{
    //    using K = std::remove_reference_t<T>;

    //    TypeDisplayer<K> a;
    if constexpr(std::is_integral<T>::value) // use K here, instead of T
    {
        // deal with integral types: char, short, int, long, ...
    }
    else
    {
        // deal with non-integral types
    }
}

int main(int argc, char* argv[])
{
//    int a = 5;
//    foo(a);

    return 0;
}
