#pragma once

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

void setConsoleTitle(const std::string& title);