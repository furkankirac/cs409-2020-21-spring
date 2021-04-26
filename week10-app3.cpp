// tuple and its implementation
// std::integer_sequence, std::index_sequence

// overloading lambdas
// union, variant, std::visit

// member function pointers
// std::invoke
// std::invocable<T, Args...>

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

template<typename ...> struct TD;

template<typename T, size_t sz>
struct Array
{
    T values[sz];
};

// deduction guide
template<typename First, typename ... Rest>
Array(First&& first, Rest&& ... rest) -> Array<remove_reference_t<First>, sizeof...(rest)+1>;

Array(const char*) -> Array<string, 1>;

struct Tuple_v1
{
    float f;
    double d;
    string s;
};

struct FunctionObjectInt
{
    auto operator() (int i)
    {
        cout << "integer has been passed" << endl;
    }
};

struct FunctionObjectFloat
{
    auto operator() (float f)
    {
        cout << "float has been passed" << endl;
    }
};

struct FunctionObjectString
{
    auto operator() (const string& s)
    {
        cout << "string has been passed" << endl;
    }
};


struct FunctionObjectIntFloatString : FunctionObjectInt, FunctionObjectFloat, FunctionObjectString
{
    using FunctionObjectInt::operator();
    using FunctionObjectFloat::operator();
    using FunctionObjectString::operator();
};

struct FunctionObject
{
    auto operator() (int i)
    {
        cout << "integer has been passed" << endl;
    }

    auto operator() (float f)
    {
        cout << "float has been passed" << endl;
    }

    auto operator() (const string& s)
    {
        cout << "string has been passed" << endl;
    }

//    template<typename T>
//    auto operator() (T&& i)
//    {
//        using K = remove_reference_t<T>;
//        if constexpr(is_same_v<K, int>)
//            cout << "integer has been passed" << endl;
//        else if constexpr(is_same_v<K, float>)
//            cout << "float has been passed" << endl;
//        else if constexpr(is_same_v<K, string>)
//            cout << "string has been passed" << endl;
//    }
};


int main()
{
    auto a = Array<int, 5>{1, 2, 3, 4, 10};
    auto b = Array{1, 2, 3, 4, 10}; // works due to deduction guide help
    auto c = Array{"1"};

    auto t1 = tuple<float, float, double, string>{3.14f, 1.0f, 6.28, "Hi there"};
    auto t2 = Tuple_v1{3.14f, 6.28, "Hi there"};

//    cout << std::get<float>(t1) << endl;
//    cout << std::get<double>(t1) << endl;
//    cout << std::get<string>(t1) << endl;

    cout << std::get<0>(t1) << endl;
    cout << std::get<1>(t1) << endl;
    cout << std::get<2>(t1) << endl;
    cout << std::get<3>(t1) << endl;

    auto fo = FunctionObjectIntFloatString{};
    fo(5);
    fo(3.14f);
    fo(string("Hi"));


    return 0;
}
