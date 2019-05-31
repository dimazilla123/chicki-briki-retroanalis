#ifndef DUMPER_H
#define DUMPER_H

#include "state.h"
#include <map>
#include <ostream>
#include <istream>

template<typename T> void dump(const T& obj, std::ostream& out);
template<typename T> T load(std::istream& in);

template<typename Key, typename Data> void dump_map(const std::map<Key, Data>& obj, std::ostream& out);
template<typename Key, typename Data> std::map<Key, Data> load_map(std::istream& in);
#endif
