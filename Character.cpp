#include "Character.h"

Character::Character() : Strength(0), Dexterity(0), Vitality(0), hp(1), target_effects(), self_effects() {}

Character::Character(const int64_t strength_, const int64_t dexterity_, const int64_t vitality_) :
    Strength(strength_), Dexterity(dexterity_), Vitality(vitality_), hp(1), target_effects(), self_effects() {
}

int64_t& Character::Str() {
    return Strength;
}
const int64_t& Character::Str() const {
    return Strength;
}
int64_t& Character::Dex() {
    return Dexterity;
}
const int64_t& Character::Dex() const {
    return Dexterity;
}
int64_t& Character::Vit() {
    return Vitality;
}
const int64_t& Character::Vit() const {
    return Vitality;
}
int64_t& Character::HP() {
    return hp;
}

const std::string Character::GetType() const {
    return "Character";
}

std::list<EffectType> Character::ActiveTargetEffects() {
    return target_effects;
}
std::list<EffectType> Character::ActiveSelfEffects() {
    return self_effects;
}

Player::Player() : Character(), weapon(), rogue_level(0), warrior_level(0), barbarian_level(0) {}

Player::Player(const int64_t& strength_, const int64_t& dexterity_, const int64_t& vitality_, const CharClass& st_class_)
    : Character(strength_, dexterity_, vitality_), weapon(), rogue_level(0), warrior_level(0), barbarian_level(0) {
    if (st_class_ == CharClass::Rogue) {
        Weapon w1(WeaponType::Dagger);
        weapon = w1;
        rogue_level = 1;
        target_effects.insert(end(target_effects), EffectType::enumBackStab);
    }
    else if (st_class_ == CharClass::Warrior) {
        Weapon w1(WeaponType::Sword);
        weapon = w1;
        warrior_level = 1;
        target_effects.insert(end(target_effects), EffectType::enumToAction);
    }
    else if (st_class_ == CharClass::Barbarian) {
        Weapon w1(WeaponType::Club);
        weapon = w1;
        barbarian_level = 1;
        target_effects.insert(end(target_effects), EffectType::enumFury);
    }
    hp = rogue_level * 4 + warrior_level * 5 + barbarian_level * 6 + Vitality;
    std::cout << "You now have " << hp << " hp\n"; //DEBUG?
}

const std::string Player::GetType() const {
    return "the hero";
}
int64_t& Player::Rogue_level() {
    return rogue_level;
}
int64_t& Player::Warrior_level() {
    return rogue_level;
}
int64_t& Player::Barbarian_level() {
    return rogue_level;
}
const int64_t Player::TotalLevel() const {
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
                    RogueLevelUp();
                    ++rogue_level;
                    break;
                }
                case ('w'): {
                    valid_choice = true;
                    WarriorLevelUp();
                    ++warrior_level;
                    break;
                }
                case ('b'): {
                    valid_choice = true;
                    void BarbarianLevelUp();
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

void Player::OfferWeapon(std::shared_ptr<Monster> monster) {
    std::cout << "The enemy drops ";
    if (monster->Type() == MonsterType::Golem) {
        std::cout << "an ";
    }
    else std::cout << "a ";
    std::cout << monster->Loot() << ". ";

    std::cout << "Would you like to use it instead of your weapon? (Y/y for yes, N/n for no)\n";
    bool incorrect_input = true;
    while (incorrect_input) {
        std::string player_input;
        std::cin >> player_input;
        if (player_input == "Y" || player_input == "y") {
            std::cout << "The hero takes the " << monster->Loot() << "." << '\n';
            weapon = monster->Loot();
            incorrect_input = false;
        }
        else if (player_input == "N" || player_input == "n") {
            std::cout << "The hero declines to take pathetic srap.\n";
            incorrect_input = false;
        }
        else {
            std::cout << "Invalid input, please, try again.\n";
        }
    }
    return;
}

const int64_t Player::PlayerLevel() const {
    return rogue_level + warrior_level + barbarian_level;
}
void Player::RogueLevelUp() {
    switch (rogue_level) {
    case 1:
        Dexterity += 0;
    case 2:
        target_effects.push_back(enumPoisoned);
    }
}
void Player::WarriorLevelUp() {
    switch (warrior_level) {
    case 1:
        self_effects.push_back(enumShield);
    case 2:
        Strength += 1;
    }
}
void Player::BarbarianLevelUp() {
    switch (barbarian_level) {
    case 1:
        self_effects.push_back(enumStoneSkin);
    case 2:
        Vitality += 1;
    }
}
Monster::Monster() : Character(), base_damage(0), type(MonsterType::Goblin), loot(Weapon(WeaponType::Dagger)) {}

Monster::Monster(const int64_t& hp_, const int64_t& base_damage_, const int64_t& strength_, const int64_t& dexterity_, const int64_t& vitality_, const MonsterType& type_, const Weapon& loot_)
                : Character(strength_, dexterity_, vitality_), base_damage(base_damage_), type(type_), loot(loot_){
    switch (type) {
    case MonsterType::Skeleton:
        self_effects.push_back(enumSkeleton_skill);
        break;
    case MonsterType::Slime:
        self_effects.push_back(enumSlime_skill);
        break;
    case MonsterType::Ghost:
        self_effects.push_back(enumBackStab);
        break;
    case MonsterType::Golem:
        self_effects.push_back(enumStoneSkin);
        break;
    case MonsterType::Dragon:
        self_effects.push_back(enumDragon_skill);
        break;
    }
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
const Damage Monster::Damage_Value() const {
    return Damage(DamageType::Pure, base_damage);
}
const Weapon& Monster::Loot() const {
    return loot;
}

std::ostream& operator<<(std::ostream& os, MonsterType type) {
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