#include "dumper.h"

template<typename T> void dump(const T& obj, std::ostream& out)
{
    out.write((char*)&obj, sizeof(obj));
}

template<typename T> T load(std::istream& in)
{
    T ret;
    in.read((char*)&ret, sizeof(ret));
    return ret;
}

template<typename Key, typename Data> void dump_map(const std::map<Key, Data>& obj, std::ostream& out)
{
    for (auto [key, data] : obj) {
        dump(key, out);
        dump(data, out);
    }
}
template<typename Key, typename Data> std::map<Key, Data> load_map(std::istream& in)
{
    Key key;
    Data data;
    std::map<Key, Data> m;
    while (in.peek() != EOF) {
        key = load<Key>(in);
        data = load<Data>(in);
        m[key] = data;
    }
    return m;
}

template void dump(const int& obj, std::ostream& out);
template int load(std::istream& in);
template void dump(const State& obj, std::ostream& out);
template State load(std::istream& in);
template void dump_map(const std::map<State, Status>& obj, std::ostream& out);
template std::map<State, Status> load_map(std::istream& in);
