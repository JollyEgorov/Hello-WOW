#include "Color.h"

void ConsoleColor::SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void ConsoleColor::Reset() {
    SetColor(7); // Белый на черном
}