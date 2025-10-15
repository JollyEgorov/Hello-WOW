#pragma once
#include <cstdint>
#include "Damage.h"
#include "Language.h"

enum WeaponType{
	Sword,
	Club,
	Dagger,
	Axe,
	Spear,
	SwordLeg
};

class Weapon {
public:
	Weapon();
	Weapon(const WeaponType& wtype);

	virtual ~Weapon() = default;

	const WeaponType& WType();

	const int64_t& DValue();

	const DamageType& DType();

protected:
	int64_t damage_;
	DamageType dtype_;
	WeaponType wtype_;
};
std::ostream& operator <<(std::ostream& os, Weapon w);