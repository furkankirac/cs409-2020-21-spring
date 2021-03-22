// a stack<T> implementation
// move-ctor, move-assignment

#include <iostream>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

struct Int
{
    int* value_ptr = nullptr;

    Int() : value_ptr(new int(0))
    { cout << "Int() got called: value = 0, value_ptr = " << value_ptr << endl; }

    Int(int value) : value_ptr(new int(value))
    { cout << "Int(int) got called: value = " << value << ", value_ptr = " << value_ptr << endl; }

    void operator=(const Int& other)
    {
        cout << "copy assignment got called" << endl;
        delete this->value_ptr;
        this->value_ptr = new int(*other.value_ptr);
    }

    void operator=(Int&& other)
    {
        cout << "move assignment got called" << endl;
        std::swap(value_ptr, other.value_ptr);
//        int* temp = value_ptr;
//        value_ptr = other.value_ptr;
//        other.value_ptr = temp;
    }

    ~Int()
    {
        cout << "Deleting " << value_ptr << endl;
        delete value_ptr;
    }
};

template<typename T>
class Stack
{
    struct Node
    {
        Node* next = nullptr;
        T elem;
//        Node() : elem() { }
    };

    Node* head = nullptr;

public:
    ~Stack()
    {
        while(head)
        {
            cout << "Deleting node, address = " << head << endl;
            auto next = head->next;
            delete head;
            head = next;
        }
    }

    void push(const T& t)
    {
        auto n = new Node();
        n->next = head;
        n->elem = t; // copy assignment
        head = n;
    }

    void push(T&& t)
    {
        auto n = new Node();
        n->next = head;
        n->elem = move(t); // move assignment: equivalent to n->elem = (T&&)t;
        head = n;
    }
};


int foo()
{
    Stack<Int> si;

    Int i = Int(3);

    si.push(Int(1000));
    si.push(i);


    Stack<string> ss;
    string s = "Hi there";
    ss.push(string("Hello World Hello World Hello World Hello World Hello World Hello World"));
    ss.push(s);


//    Int i = Int();
//    Int j = Int(100);
//    i.operator=(j);
//    i = j; // copy assignment

    return 0;   // Return Value Optimization
}

int main(int argc, char* argv[])
{
    int a = foo();

    return 0;
}
