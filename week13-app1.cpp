// ADL and friend functions, swap idiom

#include <iostream>
#include <string>
#include <memory>
#include <type_traits>

//using namespace std;

namespace my
{

struct Foo
{
    int i;
    Foo(int i) : i(i) { }
};

void bar() { std::cout << "Hello" << std::endl; }

void print(const Foo& f) { std::cout << f.i << std::endl; }

void swap(Foo& f1, Foo& f2)
{
    std::cout << "MY SWAP is called" << std::endl;
    auto temp = f1;
    f1 = f2;
    f2 = temp;
}

} // end of my namespace

//template<typename T>
//void SWAP(T& value1, T& value2)
//{
//    auto temp = value1;
//    value1 = value2;
//    value2 = temp;
//}

int main()
{
    using namespace std;

    auto foo = my::Foo(100);
    my::bar();
    print(foo); // ADL = argument dependent lookup

    std::cout << "Hi\n";
    operator<<(std::cout, "Hi\n");

    auto i = 10;
    auto j = 20;
    auto foo1 = my::Foo(100);
    auto foo2 = my::Foo(100);
    swap(foo1, foo2); // ADL lookup calls your custom swap function here
    std::cout << i << std::endl;
    std::cout << j << std::endl;

    return 0;
}
