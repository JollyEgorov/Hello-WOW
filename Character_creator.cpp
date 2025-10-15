#include "Character_creator.h"

std::shared_ptr<Player> Character_creation() {

    std::cout << Localization::getInstance().getString("istats") << "\n";

    int64_t strength_ = Random(1, 3);
    int64_t dexterity_ = Random(1, 3);
    int64_t vitality_ = Random(1, 3);
    
    if (false) {                                            //DEV CHEAT!
        strength_ = 0;
        dexterity_ = 50;
        vitality_ = 50;
    }

    ConsoleColor::SetColor(GREEN);
    std::cout << Localization::getInstance().getString("istatsdex") << " " << dexterity_ << '\n';
    //std::cout << "Dexterity: " << dexterity_ << '\n';
    ConsoleColor::SetColor(RED);
    std::cout << Localization::getInstance().getString("istatsstr") << " " << strength_ << '\n';
    //std::cout << "Strength: " << strength_ << '\n';
    ConsoleColor::SetColor(YELLOW);
    std::cout << Localization::getInstance().getString("istatsvit") << " " << vitality_ << '\n';
    //std::cout << "Vitality: " << vitality_ << '\n';
    ConsoleColor::Reset();

    std::string player_input;

    CharClass st_class_ = CharClass::None;
    
    while (st_class_ == CharClass::None) {
        std::cout << Localization::getInstance().getString("iclasschoose") << '\n';
        std::cin >> player_input;
        if (player_input == "r" || player_input == "R") {
            st_class_ = CharClass::Rogue;
            std::cout << Localization::getInstance().getString("mgreetrogue") << "\n";
        }
        else if (player_input == "w" || player_input == "W") {
            st_class_ = CharClass::Warrior;
            std::cout << Localization::getInstance().getString("mgreetwarrior") << "\n";
        }
        else if (player_input == "b" || player_input == "B") {
            st_class_ = CharClass::Barbarian;
            std::cout << Localization::getInstance().getString("mgreetbarbarian") << "\n";
        }
        else {
            std::cout << Localization::getInstance().getString("eclasschoose") << "\n";;
        }
        //std::cerr << "player_input: " << player_input << '\n';
        //std::cerr << "st_class_: " << st_class_ << '\n';
    }

    return std::make_shared<Player>(strength_, dexterity_, vitality_, st_class_);
    return nullptr;
}