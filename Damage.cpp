#include "Damage.h"

Damage::Damage() : dtype_(DamageType::Pure), dvalue_(0){}

Damage::Damage(const DamageType& type, const uint64_t& value) : dtype_(type) , dvalue_(value){}

uint64_t& Damage::DValue() {
	return dvalue_;
}

DamageType& Damage::DType() {
	return dtype_;
}

const uint64_t& Damage::DValue() const {
	return dvalue_;
}

const DamageType& Damage::DType() const {
	return dtype_;
}