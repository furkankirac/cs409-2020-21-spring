// StudentID: xxxxxxxx, Name: AAA BBB CCC

#include <iostream>
#include <vector>

template<typename ...> struct TD; // your compile time debug helper (TypeDisplayer)

template<typename T>
concept Scalar = std::is_integral_v<T> || std::is_floating_point_v<T>;

auto $1 = []<typename T>(T&& t, auto&& ...)                 -> decltype(auto) { return std::forward<T>(t); };
auto $2 = []<typename T>(auto&&, T&& t, auto&& ...)         -> decltype(auto) { return std::forward<T>(t); };
auto $3 = []<typename T>(auto&&, auto&&, T&& t, auto&& ...) -> decltype(auto) { return std::forward<T>(t); };

template<typename F, typename ... All>
constexpr auto eval(const F& f, All&& ... all)
{
    if constexpr(Scalar<F>)
        return f;
    else
        return f(std::forward<All>(all)...);
}

auto operator +(const auto& f1, const auto& f2) {
    return [f1, f2]<typename ... All>(All&& ... all) -> decltype(auto) {
        return eval(f1, std::forward<All>(all)...) + eval(f2, std::forward<All>(all)...); };
}
auto operator -(const auto& f1, const auto& f2) {
    return [f1, f2]<typename ... All>(All&& ... all) -> decltype(auto) {
        return eval(f1, std::forward<All>(all)...) - eval(f2, std::forward<All>(all)...); };
}
auto operator *(const auto& f1, const auto& f2) {
    return [f1, f2]<typename ... All>(All&& ... all) -> decltype(auto) {
        return eval(f1, std::forward<All>(all)...) * eval(f2, std::forward<All>(all)...); };
}
auto operator /(const auto& f1, const auto& f2) {
    return [f1, f2]<typename ... All>(All&& ... all) -> decltype(auto) {
        return eval(f1, std::forward<All>(all)...) / eval(f2, std::forward<All>(all)...); };
}

auto operator ++(const auto& f) {
    return [f]<typename ... All>(All&& ... all) -> decltype(auto) { return ++f(std::forward<All>(all)...); };
}

auto operator ++(const auto& f, int) {
    return [f]<typename ... All>(All&& ... all) -> decltype(auto) { return f(std::forward<All>(all)...)++; };
}

auto operator >(const auto& f, double val) {
    return [f, val]<typename ... All>(All&& ... all) -> decltype(auto) {
        return f(std::forward<All>(all)...) > val;
    };
}

template<typename T, typename ... Rest>
struct Vector : std::vector<T, Rest...>
{
    using std::vector<T, Rest...>::vector; // inherit all constructors of the base class as well

    template<typename U>
    auto operator[](const U& t) -> decltype(auto)
    {
        if constexpr(std::is_integral_v<U>)
        {
            return std::vector<T, Rest...>::operator[](t < 0 ? t+this->size() : t);
        }
        else if constexpr(std::is_same_v<U, std::vector<bool>>)
        {
            auto v = std::vector<T, Rest...>{};
            auto it = this->begin();
            auto it_mask = t.begin();
            for(; it != this->end(); ++it, ++it_mask)
                if(*it_mask)
                    v.emplace_back(*it);
            return v;
        }
        else if constexpr(std::is_same_v<decltype(t((*this)[0])), bool>)
        {
            auto v = std::vector<bool, Rest...>{};
            for(auto&& item : *this)
                v.emplace_back(t(item));
            return v;
        }
        else
        {
            auto v = std::vector<T, Rest...>{};
            for(auto& item : *this)
                v.push_back(t(item));
            return v;
        }
    }
};

template<typename T, T ... values> Vector(T...) -> Vector<T>; // deduction guide for facilitating Vector usage

template<typename T> // dual requires usage below is correct. first is clause, second one is expression version
void print(T&& container) requires requires(T t) { t.size(); t.begin(); t.end(); t.begin()++; }
{
    for(auto&& item : container)
        std::cout << item << " ";
    std::cout << std::endl;
}

void print(const char* item)    { std::cout << std::endl << item << std::endl; }
void print(auto&& item)         { std::cout << item << std::endl; }
void print(auto&& ... ts)       { (print(ts), ...); }

int main()
{
    // design a print overload-set or a single print function that can generically print any number of
    // containers and strings and other values in a single call to print. check the below usage of print.

    // design a math expression system that lazily represents an operation over values that will be later provided
    // use $1, $2, $3 as special variables of this math expression toolkit
    // $1 means the first value, $2 means the second, $3 means the third value supplied to a function/lambda
    // (yes, using $ is valid for variables!)
    // for instance; auto e=$3-$1+$2 creates an expression via composing 3 different lambdas
    // when later called with (10, 20, 30, 40, 50, ...) evaluates to 30-10+20
    // your design shall take care of at least +, -, *, /, ++, > operators
    // note that ++i and i++ are different overloads. How to overload both of them? Check the internet.
    // > will create a lazy boolean expression
    // ++ will also touch and change the item itself
    // (for instance running $1++ over a vector will increment all elements by one after the evaluation is done)
    // operator precedence is the same as the precedences that are defined in the C++ language
    // if you do compose two lambdas from left to right, there shall be no problem with the precedence
    // language will take care of it for you

    // create a Vector<...> class that inherits from vector<...> and extends it so that after auto v = Vector{...};
    // v[boolean expression] outputs a mask of vector<bool>
    // v[other expression] creates a new vector that contains transformed items according to the expression
    // v[vector<bool>] selects only the elements that correspond to boolean true locations of the vector<bool> mask
    // v[index] works as before
    // v[-index] selects the item starting from the end of the vector. For instance, -1 is the last element.

    // Q1 (15 pts) - print overload-set working correctly as used below in all questions
    // Q2 (30 pts) – below and all expressions that can be written with $1, $2, $3 and +, -, *, / works correctly    auto l1 = (1.1 + $3) * ($1 + $2 / 2.0);
    auto l1 = (1.1 + $3) * ($1 + $2 / 2.0);
    print("l1(5, 10, 15)", l1(5, 10, 15));

    // Q3 (5 pts) - deduction guide for below line
    // you can change below line to Vector<int>{10, 20, 30} if you want to skip this question
    auto v = Vector{10, 20, 30}; // not written Vector<int>{10, 20, 30} especially.

    // Q4 (5 pts) - $1>10 works as expected
    // Q5 (10 pts) - masking of a Vector works
    auto mask_gt_10 = v[$1 > 10];
//    auto mask_gt_10 = std::vector<bool>{false, true, true};

    // Q6 (10 pts) - selection of Vector elements by means of a mask
    auto v_selected = v[mask_gt_10];
    print("v", v, "Mask of $1>10", mask_gt_10, "v_selected", v_selected);

    // Q7 (10 pts) - accessing elements of a Vector in standard way and in reverse direction
    print("First element of v", v[0], "Last Element of v", v[-1]);
    print("v", v);

    // Q8 (only for CS409) (15 pts) - item++ operator works on Vector<int>
    print("v applied with $1++ * 3", v[$1++ * 3]);
    print("v", v); // note that v's items are now incremented by one due to $1++ above

    // Q8 (only for CS509) (15 pts) - ++item operator works on Vector<double>
    // you can change below line to Vector<double>{1.1, 2.2, 3.3} if you don't want points from Q3
    auto v2 = Vector{1.1, 2.2, 3.3};
    print("v2", v2);
    print("v2 applied with ++$1 - 1", v2[++$1 - 1]);
    print("v2", v2); // note that v's items are now incremented by one due to $1++ above
    return 0;
}
