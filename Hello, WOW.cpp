#include <memory>
#include <cstdlib>
#include <iostream>

#include "Battle_System.h"
#include "Character_creator.h"
#include "Spawn_monster.h"
//#include "Spawn_instance.h"



std::shared_ptr<Player> Spawn_player() {
    GameState::getInstance().resetTurn();
    return Character_creation();
}

std::shared_ptr<Monster> Spawn_monster() {
    return Monster_creation();
}

void Defeat(std::shared_ptr<Player> player) {
    std::cout << "Oh, noble hero, your adventure has come to an end.\n" << "Good luck next time!\n";
    player = nullptr;
}

bool OfferNG() {
    std::cout << "Would you like to start a new adventure?(y/n)" << '\n';
    std::string player_input;
    std::cin >> player_input;
    if (player_input == "y" || player_input == "Y") {
        return true;
    }
    return false;
}

int main()
{   
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
        std::cerr << "Enemies now defeated: " << GameState::getInstance().getEnemiesDefeated() << '\n';
    }
    if (GameState::getInstance().getEnemiesDefeated() == 5) std::cout << "Congrats, you've beat the game!\n";
    else std::cout << "Thank you for playng Hello, WOW!\n";
    return 0;
}