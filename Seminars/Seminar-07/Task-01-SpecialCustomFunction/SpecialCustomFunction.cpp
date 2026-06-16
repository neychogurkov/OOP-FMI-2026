#include "SpecialCustomFunction.h"
#include <stdexcept>
#include <utility>

void SpecialCustomFunction::free() {
	delete[] special;
	special = nullptr;
	size = 0;
	func = nullptr;
}

void SpecialCustomFunction::copyFrom(const SpecialCustomFunction& other) {
	size = other.size;
	special = new int[size];

	for (size_t i = 0; i < size; i++) {
		special[i] = other.special[i];
	}

	func = other.func;
}

void SpecialCustomFunction::moveFrom(SpecialCustomFunction&& other) {
	size = other.size;
	other.size = 0;

	special = other.special;
	other.special = nullptr;

	func = other.func;
	other.func = nullptr;
	//func = std::move(other.func);
}

SpecialCustomFunction::SpecialCustomFunction(const int* arr, size_t size, int (*func)(int num) /*std::function<int(int)> func*/) : size(size), func(func) {
	this->special = new int[size];

	for (size_t i = 0; i < this->size; i++) {
		this->special[i] = arr[i];
	}
}

SpecialCustomFunction::SpecialCustomFunction(const SpecialCustomFunction& other) {
	copyFrom(other);
}

SpecialCustomFunction& SpecialCustomFunction::operator=(const SpecialCustomFunction& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

SpecialCustomFunction::SpecialCustomFunction(SpecialCustomFunction&& other) {
	moveFrom(std::move(other));
}

SpecialCustomFunction& SpecialCustomFunction::operator=(SpecialCustomFunction&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

SpecialCustomFunction::~SpecialCustomFunction() {
	free();
}

int SpecialCustomFunction::operator()(int value) const {
	for (size_t i = 0; i < size; i++) {
		if (special[i] == value) {
			return value * value;
		}
	}

	if (!func) {
		throw std::runtime_error("No function");
	}

	return func(value);
}

SpecialCustomFunction& SpecialCustomFunction::operator++() {
	for (size_t i = 0; i < size; i++) {
		special[i]++;
	}

	return *this;
}

SpecialCustomFunction SpecialCustomFunction::operator++(int) {
	SpecialCustomFunction res = *this;

	for (size_t i = 0; i < size; i++) {
		special[i]++;
	}

	return res;
}

SpecialCustomFunction& SpecialCustomFunction::operator--() {
	for (size_t i = 0; i < size; i++) {
		special[i]--;
	}

	return *this;
}

SpecialCustomFunction SpecialCustomFunction::operator--(int) {
	SpecialCustomFunction res = *this;

	for (size_t i = 0; i < size; i++) {
		special[i]--;
	}

	return res;
}

SpecialCustomFunction SpecialCustomFunction::operator!() const {
	SpecialCustomFunction res = *this;

	for (size_t i = 0; i < size; i++) {
		res.special[i] = -res.special[i];
	}

	return res;
}

