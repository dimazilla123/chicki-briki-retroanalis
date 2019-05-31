#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <iostream>
#include <algorithm>
#include "state.h"

const int ai_turn = 1;

char prompt(const std::string& message, const std::string& choses);
void print_state(const State& current);
void print_status(Status st);
#endif
