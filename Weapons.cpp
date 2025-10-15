#include "Weapons.h"

Weapon::Weapon() : dtype_(DamageType::Cutting), damage_(3), wtype_(WeaponType::Sword) {}

Weapon::Weapon(const WeaponType& wtype) : wtype_(wtype), damage_(0), dtype_(DamageType::Pure) { //Check for damage types!
	switch (wtype) {
	case WeaponType::Sword:
		damage_ = 3;
		dtype_ = DamageType::Cutting;
		break;
	case WeaponType::Club:
		damage_ = 3;
		dtype_ = DamageType::Blunt;
		break;
	case WeaponType::Dagger:
		damage_ = 2;
		dtype_ = DamageType::Piercing;
		break;
	case WeaponType::Axe:
		damage_ = 4;
		dtype_ = DamageType::Cutting;
	case WeaponType::Spear:
		damage_ = 3;
		dtype_ = DamageType::Piercing;
	case WeaponType::SwordLeg:
		damage_ = 10;
		dtype_ = DamageType::Cutting;
	}
}

const WeaponType& Weapon::WType() {
	return wtype_;
}

const int64_t& Weapon::DValue() {
	return damage_;
}

const DamageType& Weapon::DType() {
	return dtype_;
}

std::ostream& operator <<(std::ostream& os, Weapon w) {
	switch (w.WType()) {
	case WeaponType::Sword:
		os << Localization::getInstance().getString("wsword");
		break;
	case WeaponType::Club:
		os << Localization::getInstance().getString("wclub");
		break;
	case WeaponType::Dagger:
		os << Localization::getInstance().getString("wdagger");
		break;
	case WeaponType::Axe:
		os << Localization::getInstance().getString("waxe");
		break;
	case WeaponType::Spear:
		os << Localization::getInstance().getString("wspear");
		break;
	case WeaponType::SwordLeg:
		os << Localization::getInstance().getString("wlegsword");
		break;
	}
	return os;
}