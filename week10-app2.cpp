// different versions of variadic print function, first-to-last, last-to-first
// fold expressions: comma operator, = operator tricks
// requires clause, requires expression, requires requires!

// class template type deductions
// deduction guides

// tuple and its implementation
// std::integer_sequence, std::index_sequence

// member function pointers
// std::invoke
// std::invocable<T, Args...>

// overloading lambdas
// union, variant, std::visit

#include <iostream>
#include <string>

using namespace std;

template<typename ...> struct TD;

template<typename T>
concept is_numeric = is_integral_v<remove_reference_t<T>> || is_floating_point_v<remove_reference_t<T>>;

void print_v1()
{
    cout << endl;
}

template<typename First, typename ... Rest>
inline void print_v1(First&& first, Rest&& ... rest)
requires requires { (int)first; } // we want first to be castable to integer for this function to exist
{
    cout << first << " ";
    print_v1(rest...);
}

inline void print_v2(is_numeric auto&& first, is_numeric auto&& ... rest) // terse syntax
{
    cout << first << " ";
    if constexpr(sizeof...(rest) != 0)
        print_v1(rest...);
    else
        cout << endl;
}

//auto sum_all(auto&& ... all)
//{
//    return (... + all);
//}

inline void print_foldexp(auto&& ... all)
{
    ((cout << all << " "), ...);
    cout << endl;
}

inline void print_reverse_v1_impl(auto&& first, auto&& ... rest)
{
    if constexpr(sizeof...(rest) != 0)
        print_reverse_v1_impl(rest...);
    cout << first << " ";
}

inline void print_reverse_v1(auto&& ... all)
{
    print_reverse_v1_impl(all...);
    cout << endl;
}

inline void print_reverse_foldexp(auto&& ... all)
{
    struct Foo {};
    (((cout << all << " "), Foo{}) = ...);
//    ((cout << all_0 << " "), Foo{}) = ((cout << all_1 << " "), Foo{}) = ((cout << all_2 << " "), Foo{});

    cout << endl;
}


int main()
{
    int i = 1;
    print_v1(i, 2.0, 3.3f, 'z');
    print_v2(i, 2.0, 3.3f, 'z');
    print_foldexp(i, 2.0, 3.3f, "Hello", 'z');
    print_reverse_v1(i, 2.0, 3.3f, "Hello", 'z');
    print_reverse_foldexp(i, 2.0, 3.3f, "Hello", 'z');

    // hint: chained assignment execution order
//    int i, j, k;
//    i = j = k = 5;
//    k=5;
//    j=k;
//    i=j;

    return 0;
}
