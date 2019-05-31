#include "print_utils.h"
#include <cassert>

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

void print_state(const State& current)
{
    std::cout << "AI hands: " << current.player_data[ai_turn][0] << " " << current.player_data[ai_turn][1] << "\n";
    std::cout << "Player hands: " << current.player_data[ai_turn ^ 1][0] << " " << current.player_data[ai_turn ^ 1][1] << "\n";
}

void print_status(Status st)
{
    if (st == Status::LOSE)
        std::cout << "LOSE" << "\n";
    else if (st == Status::DRAW)
        std::cout << "DRAW" << "\n";
    else if (st == Status::WIN)
        std::cout << "WIN" << "\n";
}
