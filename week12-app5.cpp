// capturing parameter-packs in lambdas

#include <iostream>
#include <string>

using namespace std;

template<typename ... Ts>
auto list(Ts&& ... ts)
{
    return [ts...](auto accessor) {
        return accessor(ts...);
    };
}

template<typename LIST>
auto get_first(LIST&& list)
{
    auto access_first_element = []<typename First, typename ... Rest>(First&& first, Rest&& ... rest) {
        return first;
    };

    return list(access_first_element);
}

auto get_size(auto&& list)
{
    auto access_list_size = [](auto&& ... all) {
        return sizeof...(all);
    };

    return list(access_list_size);
}

auto get_tail(auto&& list_)
{
    auto access_rest = [](auto&&, auto&& ... rest) {
        return list(rest...);
    };

    return list_(access_rest);
}


int main()
{
    auto l = list(5, 10.10, "Hi", string("there"));

    cout << get_first(l) << endl;
    cout << get_size(l) << endl;

    auto rest = get_tail(l); // rest equals to this now: list(10.10, "Hi", string("there"));
    cout << get_first(rest) << endl;


    return 0;
}
