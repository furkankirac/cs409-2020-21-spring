// concepts by Bjarne Stroustrup

// template specialization
// if-constexpr
// is_same<T1, T2>

// variadic templates

// left-to-right, right-to-left precedence in an expression
//  assignment operator, chained assigment
//  comma operator
// fold expressions

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename T> struct TypeDisplay;

// for instance, T = std::vector<int>
template<typename T> concept AnyContainer = requires(T t) { t.begin(); t.end(); t.size(); t.begin()++; *t.begin(); };

template<template<typename> typename ContainerTemplate, typename T>
concept PushableContainer = requires(ContainerTemplate<T> t)
{
    t.push_back( T{} );
};

template<typename Container>
concept PushableContainer_v2 = requires(Container c)
{
    c.push_back( remove_cvref_t< decltype(*c.begin()) > {} );
};


void print(const auto& container)
{
    for(const auto& item : container)
        cout << item << " ";
    cout << endl;
}

template<
    template<typename ...> typename ContainerTemplate, // ContainerTemplate is a template that expects a single typename
    typename ... Ts
    >
//requires(PushableContainer<ContainerTemplate, Ts...>)
requires(PushableContainer_v2<ContainerTemplate<Ts...>>)
[[nodiscard]] auto transform(const ContainerTemplate<Ts...>& container, auto func)
{
    using T_new = decltype(func(*container.begin()));
    auto container_new = ContainerTemplate<T_new>{};
    for(const auto& item : container)
        container_new.push_back(func(item));
    return container_new;
}

//template<AnyContainer Container>
////requires(AnyContainer<Container>)
//[[nodiscard]] auto transform(const Container& container, auto func)
//{
//    using T_new = decltype(func(*container.begin()));
//    auto container_new = Container{}; // we lost the ability to create a container with the new type coming from business logic
//    for(const auto& item : container)
//        container_new.push_back(func(item));
//    return container_new;
//}

auto get_lambda(auto by) { return [by](const int& value) { return value * by; }; }

int main(int argc, char* argv[])
{
    vector<int> v{1, 2, 3, 4, 5};

//    const, volatile, ref --> cv_ref

//    using K = decltype(*v.begin());
//    TypeDisplay< std::remove_cvref_t<K> > a;

    auto l = list<int>{10, 20, 30, 40, 50};

    // int 5 is not a container, but a generic algorithm not constrained with a concept still tries to compile code
    // for the below case.
//    transform(5, [](const pair<int, int>& p) { return p; });

    print(v);

    auto l_result = transform(l, get_lambda(11.9)); // returns list<double>
    print(l_result);

    return 0;
}
