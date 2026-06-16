#include <iostream>
#include "NumericalVector.h"

int main() {
	NumericalVector v1(2);
	NumericalVector v2(2);

	v1.setValue(0, 2);
	v1.setValue(1, -3);
	v2[0] = -3;
	v2[1] = 5;

	std::cout << v1[0] << " " << v1[1] << std::endl;
	std::cout << v2[0] << " " << v2[1] << std::endl;

	std::cout << v1 + v2 << std::endl;
	v1 += v2;
	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;

	std::cout << v1 * v2 << std::endl;

	std::cout << (v1 < v2) << std::endl;
	std::cout << (v1 == v2) << std::endl;
	std::cout << (v1 != v2) << std::endl;
	std::cout << (v1 > v2) << std::endl;
	std::cout << (v1 >= v2) << std::endl;
}