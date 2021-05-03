// overloading lambdas
// union, std::variant, std::holds_alternative, std::get_if, std::visit

// tuple and its implementation
// std::integer_sequence<T, T...>,
// std::make_integer_sequence<T, size_t>,
// std::make_index_sequence<size_t>,
// std::index_sequence_for<typename...>

#include <iostream>
#include <variant>
#include <vector>

using namespace std;

template<typename ...> struct TD;

struct FunctionObjectInt
{
    auto operator() (int i) const
    { cout << "integer has been passed" << endl; }
};
auto lambda_int = [](int i) { cout << "integer has been passed" << endl; };

struct FunctionObjectFloat
{
    auto operator() (float f) const
    { cout << "float has been passed" << endl; }
};
auto lambda_float = [](float f) { cout << "float has been passed" << endl; };

struct FunctionObjectString
{
    auto operator() (const string& s) const
    { cout << "string has been passed" << endl; }
};
auto lambda_string = [](const string& s) { cout << "string has been passed" << endl; };

struct FunctionObjectIntFloatString : FunctionObjectInt, FunctionObjectFloat, FunctionObjectString
{
    using FunctionObjectInt::operator(), FunctionObjectFloat::operator(), FunctionObjectString::operator();
};

struct FunctionObject
{
    auto operator() (int i) const             { cout << "integer has been passed" << endl; }
    auto operator() (float f) const           { cout << "float has been passed" << endl; }
    auto operator() (const string& s) const   { cout << "string has been passed" << endl; }
};

template<typename ... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename ... Ts> overloaded(Ts...) -> overloaded<Ts...>;

enum variant_type { type_int=0, type_float=1 };

struct variant_int_float
{
    variant_type vt;
    union {
        int value_int;
        float value_float;
    };

    auto operator =(int v)
    {
        this->vt = type_int;
        this->value_int = v;
        return *this;
    }

    auto operator =(float v)
    {
        this->vt = type_float;
        this->value_float = v;
        return *this;
    }

    bool hold_alternative_int()
    {
        return vt == type_int;
    }
    bool hold_alternative_float()
    {
        return vt == type_float;
    }
};


int main()
{
    auto vif = variant_int_float{};
    vif = 10;
//    vif.vt = type_int;
//    vif.value_int = 10;

    vif = 3.14f;
//    vif.vt = type_float;
//    vif.value_float = 3.14f;


        auto fo = FunctionObjectIntFloatString{};
    fo(5);
    fo(3.14f);
    fo(string("Hi"));
    cout << endl;

    lambda_int(5);
    lambda_float(3.14f);
    lambda_string(string("Hi"));
    cout << endl;

    auto lambda_all = overloaded{
        [](int i) { cout << "integer has been passed" << endl; },
        [](float f) { cout << "float has been passed" << endl; },
        [](const string& s) { cout << "string has been passed" << endl; }
    };

    lambda_all(5);
    lambda_all(3.14f);
    lambda_all(string("Hi"));

    using intstring = variant<int, string, float>;
    intstring IS = 10;
//    IS = string("Hi There");
//    IS = 3.14f;

//    if(auto pvalue = get_if<int>(&IS))
//        cout << "There is an integer in variant IS: " << *pvalue << endl;
//    else if(auto pvalue = get_if<string>(&IS))
//        cout << "There is a string in variant IS: " << *pvalue << endl;
//    else if(auto pvalue = get_if<float>(&IS))
//        cout << "There is a float in variant IS: " << *pvalue << endl;

//    int i = 1;
//    switch(i)
//    {
//    case 0: cout << "Hi" << endl; break;
//    case 1: cout << "there" << endl; break;
//    };

    auto buslog = overloaded{
         [](int i) { cout << "There is an integer in variant IS: " << i << endl; },
         [](float f) { cout << "There is a float in variant IS: " << f << endl; },
         [](const string& s) { cout << "There is a string in variant IS: " << s << endl; }
    };

    visit(buslog, IS);

    auto v = vector<variant<int, float, string>>{"Hi there", 3.14f, 100};
    for(auto&& item : v)
    {
        visit(buslog, item);
    }

    return 0;
}
