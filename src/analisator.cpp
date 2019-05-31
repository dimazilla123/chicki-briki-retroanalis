#include <iostream>

#include "retroanalis.h"

#ifndef DEBUG
#define fprintf if (0) fprintf
#endif

int main()
{
    std::map<State, Status> stats;
    analis(stats);

    for (auto [state, status] : stats) {
        std::cout << status << "\n";
    }

    return 0;
}

