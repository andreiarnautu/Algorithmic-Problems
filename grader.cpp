#ifndef __GRADER_CPP__
#define __GRADER_CPP__

#include "graderlib.h"
#include "icc.h"

int main() {
    startGrader();

    run(numCities());

    quietFinish();

    return 0;
}

#endif // __GRADER_CPP__
