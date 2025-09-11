#pragma once

#include <cstdint>

class GameState {
public:
    static GameState& getInstance() {
        static GameState instance;
        return instance;
    }

    GameState(const GameState&) = delete;
    void operator=(const GameState&) = delete;

    uint64_t getTurn() const { return turn_; }
    void nextTurn() { turn_++; }
    void resetTurn() { turn_ = 0; }
    const uint64_t& getEnemiesDefeated() const { return enemies_defeated_; }
    uint64_t& setEnemiesDefeated() { return enemies_defeated_; }

private:
    GameState() : turn_(0), enemies_defeated_(0) {}
    uint64_t turn_;
    uint64_t enemies_defeated_;
};