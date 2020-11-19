#ifndef __HEAD_H__
#define __HEAD_H__
#include <iostream>
#include "D:\FMT\include\fmt\format.h"
#include "D:\FMT\include\fmt\ranges.h"
#include "D:\FMT\include\fmt\os.h"

namespace Exercise
{
    int ivar = 0;
    double dvar = 0;
    const int limit = 1000;

}

// int ivar = 0;
void manip()
{
using namespace Exercise;

    double dvar = 3.1416;
    fmt::print("{}\n", dvar);

    int iobj = limit + 1;
    fmt::print("{}\n",iobj);

    ++ivar;
    fmt::print("{}\n", ivar);

    // ++::ivar;
    // fmt::print("{}\n", ::ivar);
}

#endif