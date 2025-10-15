#include "Language.h"

bool Localization::loadLanguage(const std::string& languageCode) {
    // Очищаем текущие строки
    strings.clear();

    // Открываем файл с строками для языка languageCode
    std::string filename = "lang/" + languageCode + ".lang"; //in folder lang file .lang
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open language file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == '#') continue;

        // Ищем разделитель '='
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            strings[key] = value;
        }
    }

    currentLanguage = languageCode;
    return true;
}

std::string Localization::getString(const std::string& key) const {
    auto it = strings.find(key);
    if (it != strings.end()) {
        return it->second;
    }
    // Если строка не найдена, возвращаем ключ или сообщение об ошибке
    return "[" + key + "]";
}

void Localization::setLanguage(const std::string& languageCode) {
    if (currentLanguage != languageCode) {
        loadLanguage(languageCode);
    }
}

Localization& Localization::getInstance() {
    static Localization instance;
    return instance;
}

void ChooseLanguage() {
    Language lang = Language::NONE;

    std::cout << "Please choose your languge: en/ru\n";

    std::string input;
    
    while (lang == Language::NONE) {
        std::cin >> input;

        if (toLower(input) == "en") {
            lang = Language::Eng;
            Localization::getInstance().setLanguage("en");
            std::cerr << "Welcome to HELLO-WOW!\n";
        }
        else if (toLower(input) == "ru") {
            SetConsoleOutputCP(CP_UTF8);
            lang = Language::Rus;
            Localization::getInstance().setLanguage("ru");
            std::cout <<  u8"Добро пожаловать в HELLO-WOW!\n";
        }
        else {
            std::cout << "Incorrect language input, please try again\n";
        }
    }
}