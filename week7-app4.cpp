#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

struct Animal
{
    enum Type
    {
        Undefined=-1, Cat=0, Dog, Bird
    };

    Type type;
    string name;

    Animal(Type type, const string& name) : type{type}, name{name} { }

    auto what_type()
    {
        if(type == Cat) return Cat;
        if(type == Dog) return Dog;
        if(type == Bird) return Bird;
        return Undefined;
    }

    void sleep()
    {
        cout << name << " is sleeping." << endl;
    }

    virtual void meow() { }
    virtual void bark() { }

};

struct Cat : Animal
{
    Cat(const string& name) : Animal(Type::Cat, name) { }

    void meow() override // overrides the Animal::meow
    {
        cout << name << " is meowing." << endl;
    }
};

struct Dog : Animal
{
    Dog(const string& name) : Animal(Type::Dog, name) { }

    void bark() override // overrides the Animal::bark
    {
        cout << name << " is barking." << endl;
    }
};

int main(int argc, char* argv[])
{
    Animal* animals[2] = {nullptr, nullptr};

    animals[0] = new Cat{"Misket"}; // Miss Cat
    animals[1] = new Dog{"Boby"};

    for(int i=0; i<2; ++i)
    {
        animals[i]->sleep();
        cout << animals[i]->what_type() << endl;

        animals[i]->meow();
        animals[i]->bark();

//        int i = 5;
//        static_cast<double>(i);
//        reinterpret_cast<int>(&i);
//        (double)i;
//        (int)&i;


//        auto cat_ptr = dynamic_cast<Cat*>(animals[i]);
//        if(cat_ptr)
//            cat_ptr->meow();
//        auto dog_ptr = dynamic_cast<Dog*>(animals[i]);
//        if(dog_ptr)
//            dog_ptr->bark();

        delete animals[i];
    }

    return 0;
}
