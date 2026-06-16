#pragma once
#include <ostream>
#include <compare>
class NumericalVector {
	int* coordinates;
	size_t size;

	void free();
	void copyFrom(const NumericalVector& other);
	void moveFrom(NumericalVector&& other);

public:
	NumericalVector(size_t size);

	NumericalVector(const NumericalVector& other);
	NumericalVector& operator=(const NumericalVector& other);

	NumericalVector(NumericalVector&& other);
	NumericalVector& operator=(NumericalVector&& other);

	~NumericalVector();

	void setValue(size_t index, int value);

	int& operator[](size_t index);
	const int& operator[](size_t index) const;
	
	NumericalVector& operator+=(const NumericalVector& other);
	friend NumericalVector operator+(const NumericalVector& lhs, const NumericalVector& rhs);
	friend int operator*(const NumericalVector& lhs, const NumericalVector& rhs);
	
	friend std::ostream& operator<<(std::ostream& os, const NumericalVector& vector);

	friend std::strong_ordering operator<=>(const NumericalVector& lhs, const NumericalVector& rhs);
	friend bool operator==(const NumericalVector& lhs, const NumericalVector& rhs);
};

