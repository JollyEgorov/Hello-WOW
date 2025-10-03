#include "Character_creator.h"

std::shared_ptr<Player> Character_creation() {

    std::cout << "Your character stats:\n";

    int64_t strength_ = Random(1, 3);
    int64_t dexterity_ = Random(1, 3);
    int64_t vitality_ = Random(1, 3);
    
    if (false) {                                            //DEV CHEAT!
        strength_ = 0;
        dexterity_ = 50;
        vitality_ = 50;
    }

    std::cout << GREEN_COLOR << "Dexterity: " << dexterity_ << '\n' << RESET_COLOR;
    std::cout << RED_COLOR << "Strength: " << strength_ << '\n' << RESET_COLOR;
    std::cout << YELLOW_COLOR << "Vitality: " << vitality_ << '\n' << RESET_COLOR;

    std::string player_input;

    CharClass st_class_ = CharClass::None;
    
    while (st_class_ == CharClass::None) {
        std::cout << "Plesase correctly choose your class: rogue(r), barbarian(b) or warrior(w)\n";
        std::cin >> player_input;
        if (player_input == "r" || player_input == "R") {
            st_class_ = CharClass::Rogue;
            std::cout << "Welcome to the dungeon, nimble rogue!\n";
        }
        else if (player_input == "w" || player_input == "W") {
            st_class_ = CharClass::Warrior;
            std::cout << "Welcome to the dungeon, mighty warrior!\n";
        }
        else if (player_input == "b" || player_input == "B") {
            st_class_ = CharClass::Barbarian;
            std::cout << "Welcome to the dungeon, furious barbarian!\n";
        }
        else {
            std::cout << "Invalid Class input, please try again\n";
        }
        //std::cerr << "player_input: " << player_input << '\n';
        //std::cerr << "st_class_: " << st_class_ << '\n';
    }

    return std::make_shared<Player>(strength_, dexterity_, vitality_, st_class_);
    return nullptr;
}