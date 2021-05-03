// tuple and its implementation
// constexpr keyword
// ref-qualified member functions

// std::integer_sequence<T, T...>,
// std::make_integer_sequence<T, size_t>,
// std::make_index_sequence<size_t>,
// std::index_sequence_for<typename...>

#include <iostream>
#include <vector>
#include <utility>
#include <tuple>

using namespace std;

template<typename ...> struct TD;

//struct TUPLE
//{
//    int int_value;
//    string string_value;
//    float float_value;
//};

template<typename First, typename ... Rest>
struct Tuple
{
    static constexpr size_t n_elements = 1 + sizeof...(Rest);

    First value;
    Tuple<Rest...> rest;

    Tuple(const First& first, const Rest& ... rest) : value{first}, rest{rest...} { }

    static constexpr auto size() { return n_elements; }

    template<size_t i, size_t current=0>
    auto get() const
    {
        if constexpr(i==current)
            return value;
        else
            return rest.template get<i, current+1>();
    }

    template<typename T, size_t current=0>
    auto get() const
    {
        if constexpr(is_same_v<T, First>)
            return value;
        else
            return rest.template get<T, current+1>();
    }
};

template<typename T>
struct Tuple<T>
{
    static constexpr size_t n_elements = 1;
    static constexpr auto size() { return n_elements; }

    T value;

    Tuple(const T& value) : value{value} { }

    template<size_t i, size_t current=0>
    auto get() const
    {
        static_assert(i==current, "Cannot find the type in tuple!");
//        if constexpr(i==current)
        return value;
    }

    template<typename U, size_t current=0>
    auto get() const
    {
        static_assert(is_same_v<U, T>, "Cannot find the type in tuple!");
//        if constexpr(is_same_v<U, T>)
        return value;
    }
};

template<size_t i, typename T>
auto get(T&& tpl)
{
    return forward<T>(tpl).template get<i>();
}

template<typename T, typename ... Ts>
auto get(const Tuple<Ts...>& tpl)
{
    return tpl.template get<T>();
}

template<typename T, size_t ... Is>
void print_tuple_impl(const T& tpl, index_sequence<Is...>)
{
    ((cout << get<Is>(tpl) << " "), ...);
}


template<typename ... Ts>
void print_tuple(const tuple<Ts...>& tpl)
{
    print_tuple_impl(tpl, index_sequence_for<Ts...>{});
}


int main()
{
//    using TUPLE = tuple<int, string, float>;
//    auto t = TUPLE{100, "Blabla", 3.14f};
//    cout << get<1>(t) << endl;
//    cout << get<string>(t) << endl;

    using K = Tuple<int, float>;
    using K2 = Tuple<float, string, int>;

    auto k = K(10, 3.14f);
    cout << "Size of tuple is " << K::size() << endl;
    cout << "Size of tuple is " << k.size() << endl;
    cout << "Size of tuple is " << K2::size() << endl;
    cout << get<1>(k) << endl;
    cout << get<float>(k) << endl;

    cout << get<string>(Tuple{20, 1.1f, string("big long string")}) << endl;

//    auto stdtpl = std::tuple{1, 1.1, 2.2f};
//    cout << get<2>(stdtpl) << endl;

    // std::integer_sequence<typename T, T ... values >
//    TD<integer_sequence<int, 5, 8, 3, 2>> a;

    // std::make_integer_sequence<T, size_t>
//    TD<make_integer_sequence<int, 10>> b;

    // std::make_index_sequence<size_t>
//    TD<make_index_sequence<10>> c;

    // std::index_sequence_for<typename...>
//    TD<index_sequence_for<int, float, int, string, vector<int>>> d;

    print_tuple(tuple<int, int, double, float>{1, 2, 1.1, 2.2f});

    return 0;
}
