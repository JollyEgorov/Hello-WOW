#include "ConsoleSetup.h"

void setConsoleTitle(const std::string& title) {
#ifdef _WIN32
    // Для Windows
    SetConsoleTitleA(title.c_str());
#else
    // Для Linux/macOS и других UNIX-систем
    std::cout << "\033]0;" << title << "\007";
#endif
}