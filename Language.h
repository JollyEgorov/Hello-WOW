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
    // Загрузка строк для указанного языка (например, "ru", "en")
    bool loadLanguage(const std::string& languageCode);

    // Получение строки по ключу
    std::string getString(const std::string& key) const;

    // Установка текущего языка
    void setLanguage(const std::string& languageCode);

    // Singleton, если хотим использовать один экземпляр по всему проекту
    static Localization& getInstance();

private:
    Localization() = default;
    std::unordered_map<std::string, std::string> strings;
    std::string currentLanguage;
};

void ChooseLanguage();