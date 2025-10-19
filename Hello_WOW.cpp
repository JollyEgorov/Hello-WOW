#include <memory>
#include <cstdlib>
#include <iostream>

#include "Language.h"
#include "Battle_System.h"
#include "Character_creator.h"
#include "Spawn_monster.h"
#include "ConsoleSetup.h"

std::shared_ptr<Player> Spawn_player() {
    GameState::getInstance().resetTurn();
    return Character_creation();
}

std::shared_ptr<Monster> Spawn_monster() {
    return Monster_creation();
}

void Defeat(std::shared_ptr<Player> player) {
    std::cout << Localization::getInstance().getString("mendadventure0") << '\n'
              << Localization::getInstance().getString("mendadventure1") << '\n';
    player = nullptr;
}

bool OfferNG() {
    std::cout << Localization::getInstance().getString("inewadventure") << '\n';
    std::string player_input;
    std::cin >> player_input;
    if (player_input == "y" || player_input == "Y") {
        return true;
    }
    return false;
}

int main()
{   
    setConsoleTitle("Hello, WOW!");
    ChooseLanguage();
    std::shared_ptr<Player> player = Spawn_player();
    GameState::getInstance().setEnemiesDefeated() = 0;
    while (GameState::getInstance().getEnemiesDefeated() != 5) {
        std::shared_ptr<Monster> monster = Spawn_monster();
        std::this_thread::sleep_for(std::chrono::seconds(2)); //DEBUG
        if (Fight(player, monster) == player) {
            player->LevelUp();
            player->OfferWeapon(monster);
            GameState::getInstance().setEnemiesDefeated() = GameState::getInstance().getEnemiesDefeated() + 1;
        }
        else {
            Defeat(player);
            if (OfferNG()) {
                player = Spawn_player();
            }
            else break;
        }
        std::cout << Localization::getInstance().getString("ienemiesdefeated") << ' ' << GameState::getInstance().getEnemiesDefeated() << '\n';
    }

    if (GameState::getInstance().getEnemiesDefeated() == 5) std::cout << Localization::getInstance().getString("mendvictory0") << '\n'
                                                                      << Localization::getInstance().getString("mendvictory1") << '\n';

    std::cout << Localization::getInstance().getString("iexit") << '\n';
    
    std::cin.get();
    std::cin.get();
    return 0;
}