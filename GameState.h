#pragma once

#include <cstdint>

enum enumLanguage {
    En,
    Ru
};

class GameState {
public:
    static GameState& getInstance() { 
        static GameState instance;
        return instance;
    }

    GameState(const GameState&) = delete;
    void operator=(const GameState&) = delete;

    int64_t getTurn() const { return turn_; }
    void nextTurn() { turn_++; }
    void resetTurn() { turn_ = 0; }
    const int64_t& getEnemiesDefeated() const { return enemies_defeated_; }
    int64_t& setEnemiesDefeated() { return enemies_defeated_; }
    enumLanguage& setGameLanguage() { return language; }
    const enumLanguage getGameLanguage() const { return language; }

private:
    GameState() : turn_(0), enemies_defeated_(0), language(enumLanguage::En) {}
    int64_t turn_;
    int64_t enemies_defeated_;
    enumLanguage language;
};