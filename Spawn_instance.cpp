#include "Spawn_instance.h"

std::unique_ptr<Character> Spawn_player() {
    GameState::getInstance().resetTurn();
    return Character_creation();
}

std::unique_ptr<Character> Spawn_monster() {
    return Monster_creation();
}