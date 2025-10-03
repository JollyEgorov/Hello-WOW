#pragma once

#include <windows.h>

enum Colors {
    GREEN = 10,
    RED = 12,
    YELLOW = 14,
    WHITE = 7
};

class ConsoleColor {
public:
    static void SetColor(int color);

    static void Reset();
};