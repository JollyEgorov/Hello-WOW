#pragma once
#include <cstdlib>
#include <iostream>
#include <random>

#define RESET_COLOR		"\033[0m"
#define RED_COLOR		"\033[31m"
#define GREEN_COLOR		"\033[32m"
#define YELLOW_COLOR	"\033[33m"

uint64_t Random(const uint64_t& first, const uint64_t& second);