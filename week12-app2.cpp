// static polymorphism: Curiously Recurring Template Pattern (CRTP)
// decltype(auto)
// std::apply
// capturing parameter-packs in lambdas

#include <iostream>

using namespace std;

template<typename DERIVED>
struct Core
{
    void run() const
    {
        using K = typename DERIVED::type;
        auto new_value = K{};
        static_cast<const DERIVED*>(this)->print();
    }
};

struct Plugin_1 : Core<Plugin_1>
{
    using type = int;

    void print() const
    {
        cout << "Plugin 1" << endl;
    }
};

struct Plugin_2 : Core<Plugin_2>
{
    using type = float;

    void print() const
    {
        cout << "Plugin 2" << endl;
    }
};


int main(int argc, char* argv[])
{
    auto p1 = Plugin_1{}; //
    p1.run();

    auto p2 = Plugin_2{};
    p2.run();

    return 0;
}
