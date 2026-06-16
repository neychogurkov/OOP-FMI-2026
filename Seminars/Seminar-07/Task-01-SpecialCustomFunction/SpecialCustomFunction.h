#pragma once
#include <functional>

class SpecialCustomFunction {
	int* special;
	size_t size;
	//std::function<int(int)> func;
	int (*func)(int num);

	void free();
	void copyFrom(const SpecialCustomFunction& other);
	void moveFrom(SpecialCustomFunction&& other);

public:
	SpecialCustomFunction(const int* arr, size_t size, int (*func)(int num)/*std::function<int(int)> func*/);
	
	SpecialCustomFunction(const SpecialCustomFunction& other);
	SpecialCustomFunction& operator=(const SpecialCustomFunction& other);

	SpecialCustomFunction(SpecialCustomFunction&& other);
	SpecialCustomFunction& operator=(SpecialCustomFunction&& other);

	~SpecialCustomFunction();

	int operator()(int value) const;

	SpecialCustomFunction& operator++();
	SpecialCustomFunction operator++(int);

	SpecialCustomFunction& operator--();
	SpecialCustomFunction operator--(int);

	SpecialCustomFunction operator!() const;
};

