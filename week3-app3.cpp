#include <iostream>

// overloading
// function / operator overloading
// function objects

// Generic Programming Paradigm:
// templates, function templates, class templates, variable templates, type-alias templates

// Object Oriented Paradigm:
// ctor/dtor
// copy-ctor, copy-assignment

// to be taught: inheritance
// to be taught: move-ctor, move-assignment

#include <iostream>

// Generic Programming Paradigm
template<typename T>
struct Value
{
    T value;

    Value() : value(0) // default ctor
    {
    }

    Value(T value) : value(value)
    {
    }

    ~Value() { }

    // copy constructor
    Value(const Value<T>& other) : value(other.value)
    {
        std::cout << "Copy ctor got called" << std::endl;
    }

    // copy assignment
    void operator=(const Value<T>& right)
    {
        this->value = right.value;
    }


//    Value<T> operator+(const Value<T>& right) const
//    {
//        return Value<T>(this->value + right.value);
//    }
};

// copy assignment as free-function
// this is not allowed by C++ compiler, as it is extremely dangerous to change the behavior of an already available
// library code
//template<typename T>
//void operator=(Value<T>& left, const Value<T>& right)
//{
//    left.value = right.value;
//}

template<typename T>
Value<T> operator+(const Value<T>& left, const Value<T>& right) // free-function
{
    return Value<T>(left.value + right.value);
}


void run() // free-function
{
    std::cout << "run got called." << std::endl;
}

void run(int value) // free-function
{
    std::cout << "run got called with a value=" << value << "." << std::endl;
}


int main(int argc, char* argv[])
{
    run();
    run(100);

    using IntValue = Value<int>;

    IntValue v1(10);
    Value<int> v2(100);

    Value<int> v3 = v1 + v2;
//    Value v4 = operator+(v1, v2);
//    Value v5 = v1.operator+(v2);

    Value<int> vnew(v1); // copy ctor
    Value<int> vnew2 = v1; // again calling copy ctor
    Value<int> vnew3; // default ctor called. it is constructed here.
    vnew3 = v1;
//    operator=(vnew3, v1);
//    vnew3.operator=(v1);


    return 0;
}
