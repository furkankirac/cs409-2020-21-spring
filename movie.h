#ifndef MOVIE_H
#define MOVIE_H

//#pragma once

enum class GenreType
{
    Comedy, // = 0,
    Drama, // = 1,
    Action, // = 2
};

struct Movie
{
    static int count;

    GenreType genre;
    int year;

    Movie(GenreType genre, int year);
    ~Movie();

    Movie(const Movie& other);

    void print();
};

#endif
