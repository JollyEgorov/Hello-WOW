#include "Utility.h"

int64_t Random(const int64_t& lower_bound, const int64_t& upper_bound) {   
    std::random_device rd;
    std::mt19937 gen(rd()); //mersenne twister algo
    std::uniform_int_distribution<> dist(lower_bound, upper_bound);
    return dist(gen);
}
