#include "Spawn_instance.h"

std::shared_ptr<Player> Spawn_player() {
    GameState::getInstance().resetTurn();
    return Character_creation();
}

std::shared_ptr<Monster> Spawn_monster() {
    return Monster_creation();
}