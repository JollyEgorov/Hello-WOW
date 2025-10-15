#include "Utility.h"

int64_t Random(const int64_t& lower_bound, const int64_t& upper_bound) {   
    std::random_device rd;
    std::mt19937 gen(rd()); //mersenne twister algo
    std::uniform_int_distribution<> dist(lower_bound, upper_bound);
    return dist(gen);
}

std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}