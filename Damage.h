#pragma once
#include <cstdint>

enum class DamageType {
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

	const uint64_t& DValue() const;

	const DamageType& DType() const;
	
private:
	DamageType dtype_;
	uint64_t dvalue_;
};