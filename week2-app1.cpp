#include <iostream>

// variables and functions and scope
// local, global, static variables
// free, member, static functions
// static attributes

// methods vs functions + this pointer

// OBJECT
// ctor/dtor
// copy-ctor, copy-assignment
// move-ctor, move-assignment
// inheritance

// function / operator overloading
// almost always auto - aaa rule: move type to the right
// unified/universal initialization

#include <iostream>
#include "movie.h"
#include "extended_movie.h"

// global variable that holds an integer number
int a = 10;

int genre_type = 0; // 0 == Comedy, 1 == Drama, 2 == Action

int Movie::count = 0;


Movie::Movie(GenreType genre, int year) : genre(genre), year(year)
{
    std::cout << "Movie ctor got called." << std::endl;
    count++;

//    this->genre = genre;
//    this->year = year;
}

Movie::~Movie()
{
    std::cout << "Movie dtor got called." << std::endl;
    count--;
}

Movie::Movie(const Movie& other) : genre(other.genre), year(other.year)
{
//    other.year = 1900;
    count++;
    std::cout << "Movie's copy-ctor got called." << std::endl;
}





void Movie::print() // not a free-function, this is a method belonging to Movie type
{
    // "this" variable is actually the memory address of the instance
    this->year = 2021;
    std::cout << "Genre=" << (int)this->genre << ", Year=" << this->year << std::endl;
}


void print(Movie* p) // free-function
{
    p->year = 2021;
    std::cout << "Genre=" << (int)p->genre << ", Year=" << p->year << std::endl;
}


void run() // free function (independent of an object, doesn't belong to an object)
{
    static bool initialized = false;

    if(!initialized)
    {
        initialized = true;
        std::cout << "Initializing..." << std::endl;
    }

    std::cout << "run() function is called." << std::endl;

    static int value = 0;
    value++;
    std::cout << "value=" << value << std::endl;

    Movie m_drama(GenreType::Drama, 1978);
    std::cout << "number of movie instances after m_drama = " << Movie::count << std::endl;
    //    m_drama.genre = GenreType::Drama;
    //    m_drama.year = 1978;

//    Movie m_drama_copy(m_drama.genre, m_drama.year);
    Movie m_drama_copy(m_drama); // copy c-tor.
    // Movie::count becomes 2


    Movie m_comedy(GenreType::Comedy, 2002);
    std::cout << "number of movie instances after m_comedy = " << Movie::count << std::endl;

//    m_drama_copy.operator=(m_comedy);
//    m_drama_copy = m_comedy;

    print(&m_drama);
    m_drama.print();

    std::cout << "m_drama.year=" << m_drama.year << std::endl;

    print(&m_comedy);
    m_comedy.print();
}



int main(int argc, char* argv[])
{
    int a = 100;
    a = 200;

    std::cout << a << std::endl;
    std::cout << ::a << std::endl;

    run();
    run();

    return 0;
}
