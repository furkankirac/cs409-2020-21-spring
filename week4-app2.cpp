#include <iostream>

// operator overloading
// function-call operator
// function objects

// getter, setter
// returning a reference
// l-value, r-value

// move-ctor, move-assignment
// inheritance

#include <iostream>
#include <string>
#include <vector>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

class Foo
{
    int value = 100;
    float f = 3.14f;

public:
    Foo() { } // default c-tor

    int get_value()
    {
        return value;
    }

    int* get_value_ptr()
    {
        return &value;
    }

    int& get_value_ref()
    {
        return value;
    }

    void set_value(int value)
    {
        this->value = value;
    }

    void operator=(int v)
    {
        this->value = v;
    }

    void operator() () const
    {
        cout << "My Attribute Value is " << this->value << "," << this->f << endl;
    }

    void operator() (int another_value) const
    {
        cout << "My Attribute Value is " << this->value*another_value << "," << this->f << endl;
    }
};

template<typename T>
void repeat_it(const T& obj, int how_many_times)
{
    for(int i=0; i<how_many_times; i++)
        obj(2);
}

void run(int value, float f)
{
    cout << "My Attribute Value is " << value << "," << f << endl;
}

int main(int argc, char* argv[])
{
    auto f = Foo(); // default c-tor gets called
    f(); // operator() gets called
    f.operator()();

//    run(100, 3.14f);

    repeat_it(f, 10);

//    f.get_value() = 1000; // f.get_value() returns r-value (kind of homeless person)
//    100 = 1000; // cannot assign on top of r-value. r-value does not indicate a memory compartment. it's just a value wandering around

    *f.get_value_ptr() = 3000;
//    f.value = 3000;
    f.get_value_ref() = 4000;

//    f.set_value(2000);
    cout << "f's value is " << f.get_value_ref() << endl;

    f = 5;
//    f.operator=(5);
    cout << "f's value is " << f.get_value() << endl;

    return 0;
}
