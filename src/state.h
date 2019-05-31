#ifndef STATE_H
#define STATE_H

#include <vector>

const int MAX_FINGERS = 5;

struct State
{
    int player_data[2][2]; // player_data[i][j] -- i player, j hand
    int turn; // 0 -- first, 1 -- second
    int fingers(int hand, int player=0) const; // 0 -- current, 1 -- next
    void next();
};

std::vector<State> get_next_states(const State& st);

#endif
