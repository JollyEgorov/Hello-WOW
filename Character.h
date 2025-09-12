#pragma once
#include <list>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdint>
#include <utility>

#include "Utility.h"
#include "Weapons.h"
#include "GameState.h"

enum CharClass {
    Rogue,
    Warrior,
    Barbarian,
    None
};

enum MonsterType {
    Goblin,
    Skeleton,
    Slime,
    Ghost,
    Golem,
    Dragon
};

enum EffectType {
    enumBackStab,           
    enumPoisoned,           
    enumToAction,           
    enumShield,             
    enumFury,               
    enumStoneSkin,          
    enumSkeleton_skill,     
    enumSlime_skill,
    enumDragon_skill
};

class Character {
public:
    Character();

    Character(const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_);

    virtual ~Character() = default;

    uint64_t& HP();
    uint64_t& Str();
    const uint64_t& Str() const;
    uint64_t& Dex();
    const uint64_t& Dex() const;
    uint64_t& Vit();
    const uint64_t& Vit() const;
    const virtual std::string GetType() const = 0;
    std::list<EffectType> ActiveOffEffects();
    std::list<EffectType> ActiveDefEffects();

    virtual Weapon& CurrentWeapon();
    virtual const Weapon& CurrentWeapon() const;

    virtual void LevelUp(); // For Player only
    virtual void OfferWeapon(std::unique_ptr<Character>& monster); // For Player only
    virtual const Weapon& Loot() const; // For Monster only
    virtual const MonsterType& Type() const;

protected:
    uint64_t hp;
    uint64_t Strength;
    uint64_t Dexterity;
    uint64_t Vitality;
    std::list<EffectType> off_effects;
    std::list<EffectType> def_effects;
};

class Player : public Character{
public:
    Player();
    Player(const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_, const CharClass& st_class_);

    const std::string GetType() const;
    uint64_t& Rogue_level();
    uint64_t& Warrior_level();
    uint64_t& Barbarian_level();
    const uint64_t TotalLevel() const;
    Weapon& CurrentWeapon();
    const Weapon& CurrentWeapon() const;

    void LevelUp();
    void OfferWeapon(std::unique_ptr<Character>& monster) const;

private:
    const uint64_t PlayerLevel() const;
    uint64_t rogue_level;
    uint64_t warrior_level;
    uint64_t barbarian_level;
    Weapon weapon;
};

class Monster : public Character {
public:
    Monster();
    Monster(const uint64_t& hp, const uint64_t& base_damage_, const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_, const MonsterType& type_, const Weapon& loot_);
    
    const std::string GetType() const;
    const MonsterType& Type() const;
    const uint64_t& Damage() const;
    const Weapon& Loot() const;

private:
    const uint64_t base_damage;
    const MonsterType type;
    const Weapon loot;
};

std::ostream& operator<<(std::ostream& os, MonsterType type);