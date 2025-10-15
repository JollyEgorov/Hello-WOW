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
    std::cout << Localization::getInstance().getString("ihp0") << hp << Localization::getInstance().getString("ihp1") << '\n'; //DEBUG?
}

const std::string Player::GetType() const { //Check EVERYWHERE!
    return Localization::getInstance().getString("thero");
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
            std::cout  << Localization::getInstance().getString("iclassupchoose") << "\n";
            
            std::cin >> input;
            input = std::tolower(static_cast<unsigned char>(input));

            switch (tolower(input)) {
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
                    BarbarianLevelUp();
                    ++barbarian_level;
                    break;
                }
                default: {
                    std::cout << Localization::getInstance().getString("eclasschoose") << '\n';
                    std::cin.clear();
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    break;
                }
            }

            hp = rogue_level * 4 + warrior_level * 5 + barbarian_level * 6 + Vitality;
            std::cout << Localization::getInstance().getString("ihp0") << hp << Localization::getInstance().getString("ihp1") << '\n';
        }
    }
    else {
        std::cout << Localization::getInstance().getString("imaxlvl") << '\n';
    }
    std::cout << Localization::getInstance().getString("icurrlvl0") << rogue_level 
              << Localization::getInstance().getString("icurrlvl1") << warrior_level 
              << Localization::getInstance().getString("icurrlvl2") << barbarian_level << ")\n";
    return;
}

void Player::OfferWeapon(std::shared_ptr<Monster> monster) {
    std::cout << Localization::getInstance().getString("idrop");
    
    std::cout << monster->Loot() << ". ";

    std::cout << Localization::getInstance().getString("iofferweapon") << "\n";
    bool incorrect_input = true;
    while (incorrect_input) {
        std::string player_input;
        std::cin >> player_input;
        if (toLower(player_input) == "y") {
            std::cout << Localization::getInstance().getString("itakeloot") << monster->Loot() << "." << '\n';
            weapon = monster->Loot();
            incorrect_input = false;
        }
        else if (toLower(player_input) == "n") {
            std::cout << Localization::getInstance().getString("idonttakeloot") << '\n';
            incorrect_input = false;
        }
        else {
            std::cout << Localization::getInstance().getString("einvinp") <<"\n";
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
        return  Localization::getInstance().getString("tgoblin");
        break;
    case (MonsterType::Skeleton):
        return  Localization::getInstance().getString("tskeleton");
        break;
    case (MonsterType::Slime):
        return  Localization::getInstance().getString("tslime");
        break;
    case (MonsterType::Ghost):
        return  Localization::getInstance().getString("tghost");
        break;
    case (MonsterType::Golem):
        return  Localization::getInstance().getString("tgolem");
        break;
    case (MonsterType::Dragon):
        return  Localization::getInstance().getString("tdragon");
        break;
    default:
        return  Localization::getInstance().getString("tmonster");
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
    case MonsterType::Goblin: os << Localization::getInstance().getString("tgoblin"); break;
    case MonsterType::Skeleton: os << Localization::getInstance().getString("tskeleton"); break;
    case MonsterType::Slime: os << Localization::getInstance().getString("tslime"); break;
    case MonsterType::Ghost: os << Localization::getInstance().getString("tghost"); break;
    case MonsterType::Golem: os << Localization::getInstance().getString("tgolem"); break;
    case MonsterType::Dragon: os << Localization::getInstance().getString("tdragon"); break;
    default: os << Localization::getInstance().getString("tumonster"); break;
    }
    return os;
}