// subroutines (1950s) vs coroutines (1960s)

// concepts
// modules
// ranges
// coroutines

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// generator
struct F
{
    int i = 0;
    void operator()()
    {
        cout << i++ << endl;
    }
};

auto l1 = [i=0]() mutable {
    cout << i++ << endl;
};


//void g()
//{
//    auto i = 0;
//    while(true)
//    {
//        yield i;

//        ++i;
//    }
//}

int main()
{
    auto f = F{};
    auto f2 = F{};
    for(int i=0; i<3; ++i)
        f();
    for(int i=0; i<3; ++i)
        f2();
    for(int i=0; i<3; ++i)
        l1();

//    for(int i=0; i<3; ++i)
//        g();

}
