#pragma once
#include <cstdint>
#include "Damage.h"

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

	const uint64_t& DValue();

	const DamageType& DType();

protected:
	uint64_t damage_;
	DamageType dtype_;
	WeaponType wtype_;
};