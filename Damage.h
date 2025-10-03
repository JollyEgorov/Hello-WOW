#pragma once
#include <cstdint>
#include <iostream>

enum class DamageType {
	Cutting,
	Piercing,
	Blunt, 
	Pure
};

class Damage {
public:
	Damage();

	Damage(const DamageType& dtype, const int64_t& dvalue);
	
	int64_t& DValue();

	DamageType& DType();

	const int64_t& DValue() const;

	const DamageType& DType() const;
	
private:
	DamageType dtype_;
	int64_t dvalue_;
};

std::ostream& operator << (std::ostream& os, const DamageType dt);

std::ostream& operator << (std::ostream& os, const Damage& d);