#include "ConsoleSetup.h"

void setConsoleTitle(const std::string& title) {
#ifdef _WIN32
    // ��� Windows
    SetConsoleTitleA(title.c_str());
#else
    // ��� Linux/macOS � ������ UNIX-������
    std::cout << "\033]0;" << title << "\007";
#endif
}