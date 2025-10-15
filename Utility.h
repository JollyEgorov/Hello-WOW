#pragma once
#include <cstdlib>
#include <iostream>
#include <random>

#define RESET_COLOR		"\033[0m"
#define RED_COLOR		"\033[31m"
#define GREEN_COLOR		"\033[32m"
#define YELLOW_COLOR	"\033[33m"

int64_t Random(const int64_t& first, const int64_t& second);

std::string toLower(const std::string& str);