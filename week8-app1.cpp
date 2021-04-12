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

template<typename T>
concept AnyContainer = requires(T t) // for instance, T = std::vector<int>
{
    t.begin();
    t.end();
    t.size();
    t.begin()++;
    *t.begin();
};

template<
    template<typename> typename ContainerTemplate,
    typename T
    >
concept PushableContainer = requires(ContainerTemplate<T> t)
{
    t.push_back( T{} );
};

void print(const auto& container)
{
    for(const auto& item : container)
        cout << item << " ";
    cout << endl;
}

struct MultiplyBy
{
    double by;
    //    MultiplyBy(double by) : by(by) { }
    auto operator() (const int& value) const { return value * by; }
};


void transform_(auto& container, auto func)
{
    for(auto& item : container)
        func(item);
}

template<
    template<typename> typename ContainerTemplate, // ContainerTemplate is a template that expects a single typename
    typename T
    >
requires(PushableContainer<ContainerTemplate, T>)
[[nodiscard]] auto transform(const ContainerTemplate<T>& container, auto func)
{
    using T_new = decltype(func(*container.begin()));
    auto container_new = ContainerTemplate<T_new>{};
    for(const auto& item : container)
        container_new.push_back(func(item));
    return container_new;
}

template<AnyContainer Container>
//requires(AnyContainer<Container>)
[[nodiscard]] auto transform(const Container& container, auto func)
{
    using T_new = decltype(func(*container.begin()));
    auto container_new = Container{}; // we lost the ability to create a container with the new type coming from business logic
    for(const auto& item : container)
        container_new.push_back(func(item));
    return container_new;
}


auto get_lambda(auto by)
{
    return [by](const int& value) { return value * by; };
}

int main(int argc, char* argv[])
{
    vector<int> v{1, 2, 3, 4, 5};
    auto l = list<int>{10, 20, 30, 40, 50};

    // int 5 is not a container, but a generic algorithm not constrained with a concept still tries to compile code
    // for the below case.
//    transform(5, [](const pair<int, int>& p) { return p; });

    print(v);

    auto lambda_multiplyby11_ = [](int& value) { value *= 11.1; };
    transform_(v, lambda_multiplyby11_);
    //    print(v);

    //    auto v_result = transform(v, MultiplyBy11{}); // returns vector<double>
    //    auto l_result = transform(l, MultiplyBy11{}); // returns list<double>

    int by = 11;
    auto lambda_multiplyby11 = [by](const int& value) { return value * by; };
    auto v_result = transform(v, lambda_multiplyby11); // returns vector<double>

    auto l_result = transform(l, get_lambda(11.9)); // returns list<double>
    print(v_result);
    print(l_result);
    //    auto a = TypeDisplay<decltype(l_result)>{};

    //    print(transform(l, MultiplyBy11{}));

    //    print(l);
    //    transform_(l, MultiplyBy11_{});
    //    print(l);

    return 0;
}
