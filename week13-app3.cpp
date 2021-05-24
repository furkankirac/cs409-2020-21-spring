// decltype of lambda

#include <iostream>

using namespace std;

void freefunc(/*...*/) { }

struct Lambda
{
    int k;
    Lambda(int k) : k(k) { }
    auto operator()(int i) const { return this->k*(i+1); }
};

template<typename Lambda>
struct Foo
{
    Lambda lambda; // ability to store lambda, because we can talk about its type due to decltype(lambda)
    Foo() { }
};

using lambda_noop = decltype([](auto&& a) { return a; });
void print(string whatever, auto lambda = lambda_noop{})
{
    cout << lambda(whatever) << endl;
}

int main()
{
//    int k = 10;
    using lambda_type = decltype([](int i) { return (i+1); });

    auto l = lambda_type();
    auto l2 = lambda_type();
    l(10);
    l(20);

//    print("Hello World"s, [](auto&& s) { return s + " I'm here"; });
    print<lambda_noop>("Hello World");

    return 0;
}
