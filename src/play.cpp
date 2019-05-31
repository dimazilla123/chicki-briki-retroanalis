#include <iostream>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <unistd.h>
#include "dumper.h"
#include "print_utils.h"

int main(int argc, char *argv[])
{
    State current = State{.player_data = {{1, 1}, {1, 1}}, .turn = 0};

    int op;
    while ((op = getopt(argc, argv, "ht:l:r:L:R:")) != -1) {
        if (op == 'h') {
            std::cout << "Usage" << "\n";
            std::cout << "-h -- help" << "\n";
            std::cout << "-l n -- n fingers at left player's hand" << "\n";
            std::cout << "-r n -- n fingers at left player's hand" << "\n";
            std::cout << "-L n -- n fingers at left AI's hand" << "\n";
            std::cout << "-R n -- n fingers at left AI's hand" << "\n";
            return 0;
        } else if (op == 'l')
            current.player_data[0][0] = std::stoi(optarg) % MAX_FINGERS;
        else if (op == 'r')
            current.player_data[0][1] = std::stoi(optarg) % MAX_FINGERS;
        else if (op == 'L')
            current.player_data[1][0] = std::stoi(optarg) % MAX_FINGERS;
        else if (op == 'R')
            current.player_data[1][1] = std::stoi(optarg) % MAX_FINGERS;
    }

    std::ifstream in(standart_dump_name, std::ios::binary);
    std::map<State, Status> statuses = load_map<State, Status>(in);

    while (current.status() == Status::DRAW) {
        if (current.turn != ai_turn) {
            print_state(current);
            print_status(statuses[current]);
            std::string choses = "lr";
            if ((current.fingers(0) + current.fingers(1)) % 2 == 0 && (current.fingers(0) != current.fingers(1)))
                choses.push_back('s');
            char answ = prompt("What to do (l to attack with left, r to attack with right, s to merge hands (if sum is even))?", choses);
            if (answ == 's') {
                current.player_data[ai_turn ^ 1][0] = current.player_data[ai_turn & 1][1] = (current.player_data[ai_turn ^ 1][0] +
                                                                                             current.player_data[ai_turn ^ 1][1]) / 2;
                current.next();
            } else {
                int attack_hand = (answ == 'l' ? 0 : 1);
                answ = prompt("Who would you attack (p -- yourself, a -- enemy)?", "pa");
                int to_strike = ai_turn;
                if (answ == 'p')
                    to_strike ^= 1;
                answ = prompt("Which hand to attack?", (to_strike != ai_turn ? (attack_hand == 0 ? "r" : "l") : "lr"));
                int targ_hand = (answ == 'l' ? 0 : 1);
                current.player_data[to_strike][targ_hand] += current.player_data[ai_turn ^ 1][attack_hand];
                current.player_data[to_strike][targ_hand] %= MAX_FINGERS;
            }
            current.next();
        } else {
            auto variants = get_next_states(current);
            State chose = variants.front();
            for (auto var : variants) {
                if (statuses[var] == Status::LOSE || (statuses[chose] == Status::WIN && statuses[var] == Status::DRAW)) {
                    chose = var;
                    break;
                }
            }
            current = chose;
        }
    }
    print_state(current);
    print_status(statuses[current]);

    if (current.turn == ai_turn)
        current.next();
    std::cout << (current.status() == Status::WIN ? "You won!" : "You lose!") << "\n";

    return 0;
}
