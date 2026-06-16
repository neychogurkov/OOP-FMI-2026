#include "NumericalVector.h"
#include <utility>
#include <stdexcept>
#include <ostream>
#include <algorithm>
#include <compare>

void NumericalVector::free() {
	delete[] coordinates;
	coordinates = nullptr;
	size = 0;
}

void NumericalVector::copyFrom(const NumericalVector& other) {
	size = other.size;

	coordinates = new int[size];

	for (size_t i = 0; i < size; i++) {
		coordinates[i] = other.coordinates[i];
	}
}

void NumericalVector::moveFrom(NumericalVector&& other) {
	coordinates = other.coordinates;
	other.coordinates = nullptr;
	size = other.size;
	other.size = 0;
}

NumericalVector::NumericalVector(size_t size) :size(size) {
	coordinates = new int[size] {};
}

NumericalVector::NumericalVector(const NumericalVector& other) {
	copyFrom(other);
}

NumericalVector& NumericalVector::operator=(const NumericalVector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

NumericalVector::NumericalVector(NumericalVector&& other) {
	moveFrom(std::move(other));
}

NumericalVector& NumericalVector::operator=(NumericalVector&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

NumericalVector::~NumericalVector() {
	free();
}

void NumericalVector::setValue(size_t index, int value) {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Invalid index!");
	}

	coordinates[index] = value;
}

int& NumericalVector::operator[](size_t index) {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Invalid index!");
	}

	return coordinates[index];
}

const int& NumericalVector::operator[](size_t index) const {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Invalid index!");
	}

	return coordinates[index];
}

NumericalVector& NumericalVector::operator+=(const NumericalVector& other) {
	if (size != other.size) {
		throw std::invalid_argument("Cannot add vectors of different dimensions.");
	}

	for (size_t i = 0; i < size; i++) {
		coordinates[i] += other.coordinates[i];
	}

	return *this;
}

NumericalVector operator+(const NumericalVector& lhs, const NumericalVector& rhs) {
	if (lhs.size != rhs.size) {
		throw std::invalid_argument("Cannot add vectors of different dimensions.");
	}

	NumericalVector res(lhs);

	res += rhs;

	return res;
}

int operator*(const NumericalVector& lhs, const NumericalVector& rhs) {
	if (lhs.size != rhs.size) {
		throw std::invalid_argument("Cannot multiply vectors of different dimensions.");
	}

	int res = 0;

	for (size_t i = 0; i < lhs.size; i++) {
		res += lhs.coordinates[i] * rhs.coordinates[i];
	}

	return res;
}

std::ostream& operator<<(std::ostream& os, const NumericalVector& vector) {
	os << "[";

	for (size_t i = 0; i < vector.size; i++) {
		os << vector.coordinates[i];

		if (i != vector.size - 1) {
			os << ", ";
		}
	}

	os << "]";

	return os;
}

bool operator==(const NumericalVector& lhs, const NumericalVector& rhs) {
	if (lhs.size != rhs.size) {
		return false;
	}

	for (size_t i = 0; i < lhs.size; i++) {
		if (lhs.coordinates[i] != rhs.coordinates[i]) {
			return false;
		}
	}

	return true;
}

std::strong_ordering operator<=>(const NumericalVector& lhs, const NumericalVector& rhs) {
	if (lhs.size < rhs.size)
		return std::strong_ordering::less;

	if (lhs.size > rhs.size)
		return std::strong_ordering::greater;


	for (size_t i = 0; i < lhs.size; i++) {
		auto res = lhs.coordinates[i] <=> rhs.coordinates[i];

		if (res != std::strong_ordering::equal) {
			return res;
		}
	}

	return std::strong_ordering::equal;
}
