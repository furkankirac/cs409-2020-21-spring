// NTTP (Non-type template params)

// constexpr functions
// consteval functions
// constinit

// volatile

// some features that a select few know
// - pointer arithmetic, array access implementation
// - try-catch-throw, "function level try-catch!", noexcept

#include <iostream>

using namespace std;

struct Config
{
    int i;
    float f;
    double d;
};

template<Config C>
void func()
{
    cout << C.i << endl;
    cout << C.f << endl;
    cout << C.d << endl;
}

constexpr auto square(int value) // constexpr means that if possible use this same code at compile time
{
    if(std::is_constant_evaluated())
        return value*value;
    else
        return value;
}

enum Color { Red, Blue, Green };

constexpr auto getColor() { return Red; }

constinit Color background_color = getColor();

int GlobalI = background_color == Red ? 100 : 200;


//func<Config{10, 3.14f, 1.1}>();
int main()
{
    background_color = Blue;

    const auto square_of_11_c = square(11);
    auto square_of_11 = square(11);
//    square_of_11 = 100;
    cout << square_of_11_c << endl;
    cout << square_of_11 << endl;

    return 0;
}
