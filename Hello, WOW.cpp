#include <memory>
#include <cstdlib>
#include <iostream>

#include "GameState.h"
#include "Utility.h"
#include "Weapons.h"
#include "Character.h"
#include "Effects.h"
#include "Battle_System.h"
#include "Character_creator.h"
#include "Spawn_monster.h"
//#include "Spawn_instance.h"

std::unique_ptr<Character> Spawn_player() { //WHY?
    GameState::getInstance().resetTurn();
    return Character_creation();
}

std::unique_ptr<Character> Spawn_monster() { //WHY???
    return Monster_creation();
}

void Check_Player_Health(std::unique_ptr<Character>& player) { // Replace?
    if (player->HP() == 0) {
        //Character_creation();
        player = Spawn_player();
    }
}

int main()
{
    
   auto player = Spawn_player();
    while (GameState::getInstance().getEnemiesDefeated() != 5) {
        auto monster = Spawn_monster();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        Fight(player, monster);
        Check_Player_Health(player);
    }
    std::cout << "Congrats, you've beat the game!\n";
    return 0;
}