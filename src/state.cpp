#include "state.h"
#include <cassert>
#include <tuple>

int State::fingers(int hand, int player) const
{
    assert(hand == 0 || hand == 1);
    return player_data[(turn + player) % 2][hand];
}

void State::next()
{
    turn ^= 1;
}

Status State::status() const
{
    if (player_data[turn][0] == player_data[turn][1] && player_data[turn][0] == 0)
        return Status::LOSE;
    int other = turn ^ 1;
    if (player_data[other][0] == player_data[other][1] && player_data[other][0] == 0)
        return Status::WIN;
    return Status::DRAW;
}

bool State::operator<(const State& other) const
{
    return std::tie(player_data[0][0], player_data[0][1],
                    player_data[1][0], player_data[1][1],
                    turn) <
           std::tie(other.player_data[0][0], other.player_data[0][1],
                    other.player_data[1][0], other.player_data[1][1],
                    other.turn);
}

bool State::operator==(const State& other) const
{
    return std::tie(player_data[0][0], player_data[0][1],
                    player_data[1][0], player_data[1][1],
                    turn) ==
           std::tie(other.player_data[0][0], other.player_data[0][1],
                    other.player_data[1][0], other.player_data[1][1],
                    other.turn);
}

bool State::operator!=(const State& other) const
{
    return !(*(this) == other);
}

std::vector<State> get_next_states(const State& st)
{
    std::vector<State> ret;
    for (int attack_hand = 0; attack_hand < 2; attack_hand++) {
        State to_add = st;
        to_add.next();
        for (int target_hand = 0; target_hand < 2; target_hand++) {
            if (st.fingers(attack_hand) != 0) {
                to_add.player_data[to_add.turn][target_hand] +=
                    st.player_data[st.turn][attack_hand];
                to_add.player_data[to_add.turn][target_hand] %= MAX_FINGERS;
                ret.push_back(to_add);
            }
        }
    }
    if (st.fingers(0) != 0) {
        State to_add = st;
        to_add.next();
        to_add.player_data[st.turn][1] += to_add.player_data[st.turn][0];
        to_add.player_data[st.turn][1] %= MAX_FINGERS;
        ret.push_back(to_add);
    }
    if (st.fingers(1) != 0) {
        State to_add = st;
        to_add.next();
        to_add.player_data[st.turn][0] += to_add.player_data[st.turn][1];
        to_add.player_data[st.turn][0] %= MAX_FINGERS;
        ret.push_back(to_add);
    }
    if ((st.fingers(0) + st.fingers(1)) % 2 == 0 && st.fingers(0) != st.fingers(1)) {
        State to_add = st;
        to_add.next();
        to_add.player_data[st.turn][0] = to_add.player_data[st.turn][1] = (st.fingers(0) + st.fingers(1)) / 2;
        ret.push_back(to_add);
    }
    return ret;
}
