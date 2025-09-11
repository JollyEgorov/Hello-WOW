#include "Character.h"

Character::Character() : Strength(0), Dexterity(0), Vitality(0), hp(1), effects() {}

Character::Character(const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_) : 
                     Strength(strength_), Dexterity(dexterity_), Vitality(vitality_), hp(1), effects() {
}

uint64_t& Character::Str() {
    return Strength;
}
uint64_t& Character::Dex() {
    return Dexterity;
}
uint64_t& Character::Vit() {
    return Vitality;
}
uint64_t& Character::HP() {
    return hp;
}

Player::Player() : Character(), weapon(), rogue_level(0), warrior_level(0), barbarian_level(0) {}

Player::Player(const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_, const CharClass& st_class_)
    : Character(strength_, dexterity_, vitality_), weapon(), rogue_level(0), warrior_level(0), barbarian_level(0) {
    if (st_class_ == CharClass::Rogue) {
        Weapon w1(WeaponType::Dagger);
        weapon = w1;
        rogue_level = 1;
        effects.insert(enumPoisoned);
    }
    else if (st_class_ == CharClass::Warrior) {
        Weapon w1(WeaponType::Sword);
        weapon = w1;
        warrior_level = 1;
    }
    else if (st_class_ == CharClass::Barbarian) {
        Weapon w1(WeaponType::Club);
        weapon = w1;
        barbarian_level = 1;
    }
    hp = rogue_level * 4 + warrior_level * 5 + barbarian_level * 6 + vitality_;
    std::cout << "You now have " << hp << " hp\n"; //DEBUG?
}

uint64_t& Player::Rogue_level() {
    return rogue_level;
}
uint64_t& Player::Warrior_level() {
    return rogue_level;
}
uint64_t& Player::Barbarian_level() {
    return rogue_level;
}
Weapon& Player::CurrentWeapon() {
    return weapon;
}
const uint64_t& Player::TotalLevel() const {
    return rogue_level + warrior_level + barbarian_level;
}

Monster::Monster() : Character(), base_damage(0), type(MonsterType::Goblin), loot(Weapon(WeaponType::Dagger)) {}

Monster::Monster(const uint64_t& hp_, uint64_t base_damage_, const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_, MonsterType type_, Weapon loot_)
                : Character(strength_, dexterity_, vitality_), base_damage(base_damage_), type(type_), loot(loot_){
    hp = hp_;
}

const MonsterType& Monster::Type() {
    return type;
}
const uint64_t& Monster::Damage() {
    return base_damage;
}
const Weapon& Monster::Loot() {
    return loot;
}

std::ostream& operator<<(std::ostream& os, MonsterType type) {//Why can't I move it to the other file?
    switch (type) {
    case MonsterType::Goblin: os << "goblin"; break;
    case MonsterType::Skeleton: os << "skeleton"; break;
    case MonsterType::Slime: os << "slime"; break;
    case MonsterType::Ghost: os << "ghost"; break;
    case MonsterType::Golem: os << "golem"; break;
    case MonsterType::Dragon: os << "dragon"; break;
    default: os << "Unknown monster!"; break;
    }
    return os;
}