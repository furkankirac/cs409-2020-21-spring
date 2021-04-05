#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

// nodiscard

// templates, typename T, T variable, auto in templates
// if-constexpr
// is_same<T1, T2>

// std::map, std::pair, structured binding

// inheritance, virtual functions

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename T> struct TypeDisplay;

void print(const auto& container)
{
    for(const auto& item : container)
        cout << item << " ";
    cout << endl;
}

struct MultiplyBy11_ { void operator() (int& value) const       { value *= 11.1; }        };
struct MultiplyBy11  { auto operator() (const int& value) const { return value * 11.1; }  };

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
[[nodiscard]] auto transform(const ContainerTemplate<T>& container, auto func)
{
    using T_new = decltype(func(*container.begin()));
    auto container_new = ContainerTemplate<T_new>{};
    for(const auto& item : container)
        container_new.push_back(func(item));
    return container_new;
}

int main(int argc, char* argv[])
{
    auto v = vector<int>{1, 2, 3, 4, 5};
    auto l = list<int>{10, 20, 30, 40, 50};

    print(v);
//    transform_(v, MultiplyBy11_{});
//    print(v);

//    auto v_result = transform(v, MultiplyBy11{}); // returns vector<double>
//    auto l_result = transform(l, MultiplyBy11{}); // returns list<double>
    auto v_result = transform(v, MultiplyBy{11}); // returns vector<double>
    auto l_result = transform(l, MultiplyBy{11.9}); // returns list<double>
    print(v_result);
    print(l_result);
//    auto a = TypeDisplay<decltype(l_result)>{};

//    print(transform(l, MultiplyBy11{}));

//    print(l);
//    transform_(l, MultiplyBy11_{});
//    print(l);

    return 0;
}
