#include "Damage.h"

Damage::Damage() : dtype_(DamageType::Pure), dvalue_(0){}

Damage::Damage(const DamageType& type, const int64_t& value) : dtype_(type) , dvalue_(value){}

int64_t& Damage::DValue() {
	return dvalue_;
}

DamageType& Damage::DType() {
	return dtype_;
}

const int64_t& Damage::DValue() const {
	return dvalue_;
}

const DamageType& Damage::DType() const {
	return dtype_;
}

std::ostream& operator << (std::ostream& os, const DamageType dt) {
	switch (dt) {
	case DamageType::Cutting:
		os << "Cutting";
		break;
	case DamageType::Piercing:
		os << "Piercing";
		break;
	case DamageType::Blunt:
		os << "Blunt";
		break;
	case DamageType::Pure:
		os << "Pure";
		break;
	}
	return os;
}

std::ostream& operator << (std::ostream& os, const Damage& d) {
	os << d.DType() << " " << d.DValue();
	return os;
}