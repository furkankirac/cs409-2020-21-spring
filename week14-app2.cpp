// std::reference_wrapper, std::ref, std::cref
// threads

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

void f1(int n)
{
    for (int i = 0; i < 5; ++i)
    {
        cout << "Thread 1 executing\n";
        ++n;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i)
    {
        cout << "Thread 2 executing\n";
        ++n;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

class foo
{
public:
    void bar()
    {
        for (int i = 0; i < 5; ++i)
        {
            cout << "Thread 3 executing\n";
            ++n;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
    int n = 0;
};

class baz
{
public:
    void operator()()
    {
        for (int i = 0; i < 5; ++i) {
            cout << "Thread 4 executing\n";
            ++n;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
    int n = 0;
};

int main()
{
    int n = 0;

//    int* a = &n;
//    (*a)++;
//    int& a = n;
//    a++;

//    auto v = vector<int>{1, 2, 3};
//    auto vr = vector<int&>{n};


    auto f = foo{};
    auto b = baz{};
    auto t1 = thread(&f1, n+1); // pass by value
    auto t2 = thread(&f2, ref(n)); // pass by reference
    auto t3 = thread(move(t2)); // t3 is now running f2(). t2 is no longer a thread
    auto t4 = thread(&foo::bar, &f); // t4 runs foo::bar() on object f
    auto t5 = thread(b); // t5 runs baz::operator() on a copy of object b
    t1.join();
    t3.join();
    t4.join();
    t5.join();
    cout << "Final value of n is " << n << '\n';
    cout << "Final value of f.n (foo::n) is " << f.n << '\n';
    cout << "Final value of b.n (baz::n) is " << b.n << '\n';
}
