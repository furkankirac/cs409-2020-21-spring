// fold expressions

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename First, typename ... Rest>
inline void print(First first, Rest ... rest)
{
    cout << first << endl;

//    print<Rest...>(rest...);
    if constexpr(sizeof...(rest) != 0)
        print(rest...);
}


int main(int argc, char* argv[])
{
//    print<int, float>(5, 3.14f);
    print(5, 3.14f);
    print<double, string, int>(1.1, "Hi", 10);

    return 0;
}
