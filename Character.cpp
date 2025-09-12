#include "Character.h"

Character::Character() : Strength(0), Dexterity(0), Vitality(0), hp(1), off_effects(), def_effects() {}

Character::Character(const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_) : 
                     Strength(strength_), Dexterity(dexterity_), Vitality(vitality_), hp(1), off_effects(), def_effects() {
}

uint64_t& Character::Str() {
    return Strength;
}
const uint64_t& Character::Str() const {
    return Strength;
}
uint64_t& Character::Dex() {
    return Dexterity;
}
const uint64_t& Character::Dex() const {
    return Dexterity;
}
uint64_t& Character::Vit() {
    return Vitality;
}
const uint64_t& Character::Vit() const {
    return Vitality;
}
uint64_t& Character::HP() {
    return hp;
}

const std::string Character::GetType() const {
    return "Character";
}

std::list<EffectType> Character::ActiveOffEffects() {
    return off_effects;
}
std::list<EffectType> Character::ActiveDefEffects() {
    return off_effects;
}

Weapon& Character::CurrentWeapon() {
    Weapon weapon;
    return weapon;
}
const Weapon& Character::CurrentWeapon() const {
    Weapon weapon;
    return weapon;
}

void Character::LevelUp() { //For Player only
    return;
}
void Character::OfferWeapon(std::unique_ptr<Character>& monster) {// For Player only
    return;
}
const Weapon& Character::Loot() const {    // For Monster only
    return Weapon();
}
const MonsterType& Character::Type() const {
    return MonsterType::Golem;
}
/*
const uint64_t& Character::Damage() const {
    return 666; //To check whether this is ever called!
}*/

Player::Player() : Character(), weapon(), rogue_level(0), warrior_level(0), barbarian_level(0) {}

Player::Player(const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_, const CharClass& st_class_)
    : Character(strength_, dexterity_, vitality_), weapon(), rogue_level(0), warrior_level(0), barbarian_level(0) {
    if (st_class_ == CharClass::Rogue) {
        Weapon w1(WeaponType::Dagger);
        weapon = w1;
        rogue_level = 1;
        off_effects.insert(end(off_effects), EffectType::enumPoisoned);
    }
    else if (st_class_ == CharClass::Warrior) {
        Weapon w1(WeaponType::Sword);
        weapon = w1;
        warrior_level = 1;
        off_effects.insert(end(off_effects), EffectType::enumToAction);
    }
    else if (st_class_ == CharClass::Barbarian) {
        Weapon w1(WeaponType::Club);
        weapon = w1;
        barbarian_level = 1;
        off_effects.insert(end(off_effects), EffectType::enumFury);
    }
    hp = rogue_level * 4 + warrior_level * 5 + barbarian_level * 6 + Vitality;
    std::cout << "You now have " << hp << " hp\n"; //DEBUG?
}

const std::string Player::GetType() const {
    return "the hero";
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
const uint64_t Player::TotalLevel() const {
    return rogue_level + warrior_level + barbarian_level;
}
Weapon& Player::CurrentWeapon() {
    return weapon;
}
const Weapon& Player::CurrentWeapon() const {
    return weapon;
}

void Player::LevelUp() {
    if (PlayerLevel() != 3) { //not top level
        
        char input;
        bool valid_choice = false;
        while (!valid_choice)
        {
            std::cout << "Please correctly choose a speciality to progress: rogue(r), warrior(w) or barbarian(b)\n";
            
            std::cin >> input;
            input = std::tolower(static_cast<unsigned char>(input));

            switch (input) {
                case ('r'): {
                    valid_choice = true;
                    ++rogue_level;
                    break;
                }
                case ('w'): {
                    valid_choice = true;
                    ++warrior_level;
                    break;
                }
                case ('b'): {
                    valid_choice = true;
                    ++barbarian_level;
                    break;
                }
                default: {
                    std::cout << "Invalid choice! Please use (r) for rogue, (w) for warrior or (b) for barbarian.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
            }

            hp = rogue_level * 4 + warrior_level * 5 + barbarian_level * 6 + Vitality;
        }
    }
    else {
        std::cout << "You have reached the maximum level!\n";
    }
    std::cout << "Your current speciality levels: rogue(" << rogue_level << "), warrior(" << warrior_level << "), barbarian(" << barbarian_level << ")\n";
    return;
}

void Player::OfferWeapon(std::unique_ptr<Character>& monster) const {// For Player only
    std::cout << "The enemy drops ";
    switch (monster->Type()) {
    case MonsterType::Goblin:
        std::cout << "a dagger\n";
        break; 
    case MonsterType::Skeleton:
        std::cout << "a club";
        break;
    case MonsterType::Slime:
        std::cout << "a spear";
        break;

    case MonsterType::Ghost:
        std::cout << "a sword";
        break;

    case MonsterType::Golem:
        std::cout << "an axe";
        break;

    case MonsterType::Dragon:
        std::cout << "a legendary sword!";
        break;
    }
    std::cout << '\n';
    return;
}

const uint64_t Player::PlayerLevel() const {
    return rogue_level + warrior_level + barbarian_level;
}

Monster::Monster() : Character(), base_damage(0), type(MonsterType::Goblin), loot(Weapon(WeaponType::Dagger)) {}

Monster::Monster(const uint64_t& hp_, const uint64_t& base_damage_, const uint64_t& strength_, const uint64_t& dexterity_, const uint64_t& vitality_, const MonsterType& type_, const Weapon& loot_)
                : Character(strength_, dexterity_, vitality_), base_damage(base_damage_), type(type_), loot(loot_){
    hp = hp_;
}

const std::string Monster::GetType() const {
    switch (type) {
    case (MonsterType::Goblin):
        return "goblin";
        break;
    case (MonsterType::Skeleton):
        return "skeleton";
        break;
    case (MonsterType::Slime):
        return "slime";
        break;
    case (MonsterType::Ghost):
        return "ghost";
        break;
    case (MonsterType::Golem):
        return "golem";
        break;
    case (MonsterType::Dragon):
        return "dragon";
        break;
    default:
        return "the monster";
    }
}

const MonsterType& Monster::Type() const {
    return type;
}
const uint64_t& Monster::Damage() const {
    return base_damage;
}
const Weapon& Monster::Loot() const {
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