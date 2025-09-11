#pragma once
#include <cstdint>

enum DamageType {
	Cutting,
	Piercing,
	Blunt, 
	Pure
};

class Damage {
public:
	Damage();
	Damage(const DamageType& dtype, const uint64_t& dvalue);
	
	uint64_t& DValue();

	DamageType& DType();
	
private:
	DamageType dtype_;
	uint64_t dvalue_;
};