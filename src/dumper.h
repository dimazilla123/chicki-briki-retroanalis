#ifndef DUMPER_H
#define DUMPER_H

#include "state.h"
#include <map>
#include <ostream>
#include <istream>

template<typename T> void dump(const T& obj, std::ostream& out);
template<typename T> T load(std::istream& in);

#endif
