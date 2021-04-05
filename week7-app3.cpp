#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>

// inheritance, virtual functions

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename T> struct TypeDisplay;

void print(const auto& container)
{
    for(const auto& item : container)
        cout << item << " ";
    cout << endl;
}

template<typename T1, typename T2>
void print(const map<T1, T2>& container)
{
    for(const auto& [key, value] : container)
        cout << key << ", " << value << endl;
    cout << endl;
}

template<typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;
};


int main(int argc, char* argv[])
{
    auto v = vector<int>{1, 2, 3, 4, 5};
    auto p1 = pair<int, float>{5, 3.14f};
    auto t1 = tuple<int, float, string, vector<int>>{
        10, 3.14f, "Hello", {1, 2, 3, 4}
    };
    p1.first; // this is 5
    p1.second; // this 3.14f

    auto m = map<int, string>{
        {2, "two"},
        {1, "one"},
        {20, "twenty"},
        {13, "thirteen"},
    };

    print(v);
    print(m);

    return 0;
}
