// member function pointers, member attribute pointers
// std::invoke, std::apply
// capturing parameter-packs in lambdas

#include <tuple>
#include <functional>
#include <iostream>

using namespace std;

template<typename...> struct TD;

void print(int i) { cout << i << endl; }

struct Foo
{
    int value;
    Foo(int value) : value{value} { }

    void print_added(int i) const { cout << (value+i) << endl; }
};

int main()
{
    // invoke a free function

    using FuncPtr = void (*)(int);
//    typedef void (*FuncPtr)(int);
    FuncPtr funcptr = &print;
//    funcptr(5);
    invoke(&print, 5);

    // invoke an r-value lambda
//    [](int i) { cout << i << endl; }(5);
    invoke([](int i) { cout << i << endl; }, 5);

    // invoke a member function
    auto foo = Foo{100};
    foo.print_added(10);
    auto fooptr = &foo;

    using MemberFuncPtr = void (Foo::*)(int) const;
    MemberFuncPtr ptr = &Foo::print_added;
    (foo.*ptr)(10);
    ((*fooptr).*ptr)(10);
    (fooptr->*ptr)(10);
    invoke(&Foo::print_added, foo, 10);

    // invoke (access) a data member
    auto value_ptr = &Foo::value;
//    foo.value;
//    foo.*value_ptr;
    cout << invoke(&Foo::value, foo) << endl;
}



//namespace detail {
//    template <typename F, typename Tuple, std::size_t... I>
//    constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
//    {
//        return invoke(forward<F>(f), get<I>(std::forward<Tuple>(t))...);
//    }
//} // namespace detail

//template <typename F, typename Tuple>
//constexpr decltype(auto) apply(F&& f, Tuple&& t)
//{
//    return
//        detail::apply_impl(
//            forward<F>(f),
//            forward<Tuple>(t),
//            make_index_sequence<tuple_size_v<remove_reference_t<Tuple>>>{} );
//}

