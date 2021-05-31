// some features that a select few know
// - pointer arithmetic, array access implementation
// - try-catch-throw, "function level try-catch!"

// noexcept
// volatile

// constructing function arguments with {...}
// returning {...}

// orderless function parameters? can we do it?


#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Bar
{
    Bar()
    {
        throw 5;
    }
};

struct Foo
{
    Bar bar;

    Foo() try : bar{Bar()}
    {
    }
    catch (...) {
        cout << "Handle the exception" << endl;
        // handles the thrown exception here
    }

    void print() const;
    void print() noexcept;
//    void print() &;
//    void print() &&;
};



struct Arg
{
    string s;
    int i{};
    float f{};
};

auto print(const Arg& arg) -> Arg
{
    cout << "string is " << arg.s << endl;
    cout << "int is " << arg.i << endl;
    cout << "float is " << arg.f << endl;

    return {.s="Hello"};
}


struct TrueFalse { bool value; };
enum class OnOff { On, Off };

auto tf = TrueFalse{false};
auto oo = OnOff{OnOff::Off};


template<typename First, typename ... Rest>
void PRINT(First&& first, Rest&& ... rest)
{
    if constexpr(is_same_v<First, TrueFalse>)
    {
        tf = first;
    }
    else if constexpr(is_same_v<First, OnOff>)
    {
        oo = first;
    }

    if constexpr(sizeof...(rest) > 0)
    {
        PRINT(forward<Rest>(rest)...);
    }
    else
    {
        cout << "TrueFalse = " << tf.value << endl;
        cout << "OnOff = " << (oo == OnOff::On ? "On" : "Off") << endl;
    }
}


//    auto v = vector<int>{1, 2, 3};
//    auto* ptr = &v[1];
//    cout << *(ptr+1) << endl;
//    cout << ptr[1] << endl;
//    cout << 1[ptr] << endl;
//    cout << *(1+ptr) << endl;
int main()
{
    volatile auto i = 10;

//    auto j = i;
//    auto f = Foo{};

//    auto a = print({.s="Hi", .f=3.14f});
//    cout << a.s << endl;

    tf = TrueFalse{false};
    oo = OnOff{OnOff::Off};
    PRINT(TrueFalse{true}, OnOff{OnOff::On});

    tf = TrueFalse{false};
    oo = OnOff{OnOff::Off};
    PRINT(OnOff{OnOff::On}, TrueFalse{true});
}
