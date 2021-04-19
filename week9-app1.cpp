// filter algorithm implementation
// C++11 reference collapsing rules
// perfect forwarding, forwarding references, std::forward

#include <iostream>
#include <vector>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename ...> struct TD;

template<typename Container, typename ... Rest>
inline void print(const Container& container, const Rest& ... rest)
{
    cout << "Size = " << container.size() << endl;
    for(const auto& item : container)
    {
        if constexpr(is_same_v<const string&, decltype(item)>)
            cout << "\"" << item << "\" ";
        else
            cout << item << " ";
    }
    cout << endl;

    if constexpr(sizeof...(Rest) > 0)
        print<Rest...>(rest...);
}

void bar(int& t)
{
    cout << "called with l-value ref" << endl;
}

void bar(int&& t)
{
    cout << "called with r-value ref" << endl;
}


template<typename T>
void foo(T&& t)
{
    bar(forward<T>(t));
//    if constexpr(is_same_v<T, int&>)
//        bar(t);
//    else if constexpr(is_same_v<T, int>)
//        bar(move(t)); // bar((int&&)t);
}

//template void foo(int); // explicit template instantiation. instantiates for T=int

template<typename CallSiteInfo, typename T>
auto&& my_forward(T&& t)
{
    if constexpr(is_reference_v<CallSiteInfo>) // l-value at call-site
        return t; // T contains single ref, t is &+&&-->&, returning &+&&, returns &
    else // means r-value at call-site. we can move the items and don't care about their destruction
        return move(t); // T contains no ref, move(t) is &&, returning &&+&&, returns &&
}


template<typename Container>
[[nodiscard]] auto filter(Container&& container, auto func)
{
    auto c_new = std::remove_reference_t<Container>{};
    for(auto&& item : container)
    {
        if(func(item))
        {
            // below line doesn't work because Container and its item are two different types
            // standard library's forward function expects the Instance to be of the Type of the instance
            // c_new.push_back(forward<Container>(item));

            c_new.push_back(my_forward<Container>(item)); // equivalent to below code
//            if constexpr(is_reference_v<Container>) // means that Container is referenced itself ---> l-value at call-site
//                c_new.push_back(item);
//            else // means r-value at call-site. we can move the items and don't care about container's contents
//                c_new.push_back(move(item));
        }
    }
    return c_new;
}

int main(int argc, char* argv[])
{
    auto v = vector<string>{"1", "22", "333"};
    print(v);

    auto v_filtered = filter(v, [](const string& s) { return s.length() >= 2; });
    print(v_filtered);

    auto v_filtered2 = filter(
        vector<string>{"1", "22", "333"},
        [](const string& s) { return s.length() >= 2; }
        );
    print(v_filtered2);

    auto v2 = vector<int>{1, 22, 333};
    auto v2_filtered = filter(v2, [](const int& i) { return i >= 300; });
    print(v, v_filtered, v2, v2_filtered);

    using T = int; // primitive type int only
    using Tref = int&; // l-value reference to int
    using Trefref = int&&; // r-value reference to int
//    auto a = TD<T&, Tref&, Trefref&>{};    // int&, int&, int&
//    auto b = TD<T&&, Tref&&, Trefref&&>{}; // int&&, int&, int&&

    int k = 5;
    foo(k); // l-value call
    foo(5); // r-value call

    return 0;
}
