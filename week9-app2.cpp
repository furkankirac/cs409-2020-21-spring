// parameter type binding exercises

#include <iostream>

struct Widget { };
template<typename ...> struct TypeDisplayer;

// (1) function with l-value ref
void f(Widget&) { std::cout << "1\n"; }

// (2) function with l-value ref-to-const
void f(const Widget&) { std::cout << "2\n"; }

// (3) function with r-value ref
//void f(Widget&&) { std::cout << "3\n"; }

// (4) function with r-value ref-to-const
void f(const Widget&&) { std::cout << "4\n"; }

// (5) function template with forwarding ref
template<typename T>
void f(T&&) { std::cout << "5\n"; }

// (6) function template with r-value ref-to-const
template<typename T>
void f(const T&&) { std::cout << "6\n"; }

Widget getWidget() { Widget w; return w; }
const Widget getConstWidget() { const Widget w; return w; }

int main(int argc, char* argv[])
{
    // what is the preference order of above functions for below questions?
//    Widget w1{}; // auto w1 = Widget{};
//    f(w1); // 1, 5, 2

//    const Widget w2{};
//    f(w2); // 2, 5

//    f(getWidget()); // 3, 5, 4, 6, 2

//    f(getConstWidget()); // 4, 6, 5, 2

    return 0;
}

