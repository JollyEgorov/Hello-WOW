#pragma once 

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <windows.h>

#include "Utility.h"

enum class Language {
    Eng,
    Rus,
    NONE
};

class Localization {
public:
    // �������� ����� ��� ���������� ����� (��������, "ru", "en")
    bool loadLanguage(const std::string& languageCode);

    // ��������� ������ �� �����
    std::string getString(const std::string& key) const;

    // ��������� �������� �����
    void setLanguage(const std::string& languageCode);

    // Singleton, ���� ����� ������������ ���� ��������� �� ����� �������
    static Localization& getInstance();

private:
    Localization() = default;
    std::unordered_map<std::string, std::string> strings;
    std::string currentLanguage;
};

void ChooseLanguage();