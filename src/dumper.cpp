#include "dumper.h"

template<int> void dump(const int& obj, std::ostream& out)
{
    out.write((char*)&obj, sizeof(obj));
}

template<int> int load(std::istream& in)
{
    int ret;
    in.read((char*)&ret, sizeof(ret));
    return ret;
}
