#include <iostream>
#include <algorithm>
#include <fstream>
#include <cassert>
#include "dumper.h"

char prompt(const std::string& message, const std::string& choses)
{
    std::cout << message << "[" << choses << "]\n";
    std::string answ;
    std::cin >> answ;
    assert(answ.size() != 0);
    auto it = std::find(choses.begin(), choses.end(), answ.front());
    assert(it != choses.end());
    return answ.front();
}

int main(int argc, char *argv[])
{
    std::ifstream in(standart_dump_name, std::ios::binary);
    std::map<State, Status> statuses = load_map<State, Status>(in);

    State current = State{.player_data = {{1, 1}, {1, 1}}, .turn = 0};
    int ai_turn = 1;
    while (current.status() == Status::DRAW) {
        if (current.turn != ai_turn) {
            std::cout << "AI hands: " << current.player_data[ai_turn][0] << " " << current.player_data[ai_turn][1] << "\n";
            std::cout << "Player hands: " << current.player_data[ai_turn ^ 1][0] << " " << current.player_data[ai_turn ^ 1][1] << "\n";
            current.next();
            std::string choses = "lr";
            if ((current.fingers(0) + current.fingers(1)) % 2 == 0)
                choses.push_back('s');
            char answ = prompt("What to do (l to attack with left, r to attack with right, s to merge hands (if sum is even))?", choses);
            break;
        } else {
            auto variants = get_next_states(current);
            State chose = variants.front();
            for (auto var : variants) {
                if (statuses[var] == Status::LOSE) {
                    chose = var;
                    break;
                }
            }
            current = chose;
        }
    }

    if (current.turn == ai_turn)
        current.next();
    std::cout << (current.status() == Status::WIN ? "You won!" : "You lose!") << "\n";

    return 0;
}
