#ifndef EXTENDED_MOVIE_H
#define EXTENDED_MOVIE_H

//#pragma once

#include "movie.h"
#include <string>

// inheritance
struct ExtendedMovie : Movie
{
    std::string name;

    ExtendedMovie(GenreType genre, int year, std::string name) : Movie(genre, year), name(name)
    {

    }
};

#endif
