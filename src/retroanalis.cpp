#include "retroanalis.h"
#include <algorithm>
#include <queue>

using Graph = std::map<State, std::vector<State>>;

Graph prepare(std::queue<State>& q, std::map<State, Status>& stats,
                                    std::map<State, int>& cnt)
{
    Graph h;
    for (int left1 = 0; left1 < MAX_FINGERS; left1++) {
        for (int right1 = 0; right1 < MAX_FINGERS; right1++) {
            for (int left2 = 0; left2 < MAX_FINGERS; left2++) {
                for (int right2 = 0; right2 < MAX_FINGERS; right2++) {
                    for (int turn = 0; turn < 2; turn++) {
                        State st = State{.player_data = {
                            {left1, right1},
                            {left2, right2},
                        }, .turn = turn};
                        stats[st] = st.status();
                        if (st.status() != Status::DRAW) {
                            q.push(st);
                        }
                        for (const auto& next_st : get_next_states(st)) {
                            h[next_st].push_back(st);
                            ++cnt[st];
                        }
                    }
                }
            }
        }
    }
    for (auto [st, nexts] : h) {
        std::sort(nexts.begin(), nexts.end());
        nexts.erase(std::unique(nexts.begin(), nexts.end()), nexts.end());
    }
    return h;
}

void analis(std::map<State, Status>& stats)
{
    std::queue<State> q;
    std::map<State, int> cnt;
    Graph h = prepare(q, stats, cnt);
    while (!q.empty()) {
        State st = q.front();
        q.pop();
        if (st.status() == Status::LOSE) {
            for (auto prev_st : h[st]) {
                stats[prev_st] = Status::WIN;
                q.push(prev_st);
            }
        } else {
            for (auto prev_st : h[st]) {
                --cnt[prev_st];
                if (cnt[prev_st] == 0) {
                    stats[prev_st] = Status::LOSE;
                    q.push(prev_st);
                }
            }
        }
    }
}
