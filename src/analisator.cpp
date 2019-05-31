#include <iostream>
#include <fstream>

#include "retroanalis.h"
#include "dumper.h"

#ifndef DEBUG
#define fprintf if (0) fprintf
#endif

int main()
{
    std::map<State, Status> stats;
    analis(stats);

    std::ofstream out(standart_dump_name, std::ios::binary);
    dump_map(stats, out);

    return 0;
}

