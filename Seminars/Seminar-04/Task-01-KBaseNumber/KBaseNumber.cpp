#include <iostream>
#pragma warning(disable:4996)
#include <cmath>
#include "KBaseNumber.h"

unsigned KBaseNumber::charToValue(char ch) const {
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	else if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 10;
	return 0;
}

unsigned KBaseNumber::toDecimal() const {
	unsigned result = 0;
	size_t length = strlen(number);

	for (size_t i = 0; i < length; i++) {
		unsigned value = charToValue(number[i]);

		if (value >= numericSystem) {
			return 0;
		}

		result += (unsigned)pow(numericSystem, length - i - 1) * value;
	}

	return result;
}

KBaseNumber KBaseNumber::decimalToOtherNumericSystem(unsigned decimalNumber, unsigned newNumericSystem) const {
	char result[Constants::MAX_NUMBER_LENGTH + 1];
	int index = 0;

	if (decimalNumber == 0) {
		return KBaseNumber("0", newNumericSystem);
	}

	while (decimalNumber > 0) {
		int remainder = decimalNumber % newNumericSystem;

		if (remainder < 10) {
			result[index++] = '0' + remainder;
		}
		else {
			result[index++] = 'A' + (remainder - 10);
		}

		decimalNumber /= newNumericSystem;
	}

	result[index] = '\0';

	for (size_t i = 0; i < index / 2; i++) {
		std::swap(result[i], result[index - i - 1]);
	}

	return KBaseNumber(result, newNumericSystem);
}

KBaseNumber::KBaseNumber() : numericSystem(10) {
	setNumber("0");
}

KBaseNumber::KBaseNumber(const char* number, unsigned numericSystem) {
	setNumber(number);
	setNumericSystem(numericSystem);
}

int KBaseNumber::compareWith(const KBaseNumber& other) const {
	unsigned currDecimal = this->toDecimal();
	unsigned otherDecimal = other.toDecimal();

	if (currDecimal < otherDecimal) {
		return -1;
	}
	else if (currDecimal == otherDecimal) {
		return 0;
	}
	else {
		return 1;
	}
}

void KBaseNumber::update(const char* number, unsigned numericSystem) {
	setNumber(number);
	setNumericSystem(numericSystem);
}

void KBaseNumber::print() const {
	std::cout << number << "(" << numericSystem << ")" << std::endl;
}

void KBaseNumber::printConvertedTo(unsigned numericSystem) const {
	int decimalNumber = toDecimal();
	KBaseNumber result = decimalToOtherNumericSystem(decimalNumber, numericSystem);
	result.print();
}

void KBaseNumber::saveToFile(const char* path) const {
	std::ofstream ofs(path, std::ios::binary);

	if (!ofs.is_open()) {
		return;
	}

	ofs.write((const char*)&numericSystem, sizeof(unsigned));
	size_t length = strlen(number) + 1;
	ofs.write((const char*)&length, sizeof(size_t));
	ofs.write(number, length);

	ofs.close();
}

void KBaseNumber::readFromFile(const char* path) {
	std::ifstream ifs(path, std::ios::binary);

	if (!ifs.is_open()) {
		return;
	}

	ifs.read((char*)&numericSystem, sizeof(unsigned));
	size_t size = 0;
	ifs.read((char*)&size, sizeof(size_t));

	if (size > Constants::MAX_NUMBER_LENGTH + 1) {
		return;
	}

	ifs.read(number, size);

	ifs.close();
}

const char* KBaseNumber::getNumber() const {
	return number;
}

unsigned KBaseNumber::getNumericSystem() const {
	return numericSystem;
}

void KBaseNumber::setNumber(const char* number) {
	if (!number || strlen(number) > Constants::MAX_NUMBER_LENGTH) {
		strcpy(this->number, "\0");
		return;
	}

	strcpy(this->number, number);
}

void KBaseNumber::setNumericSystem(unsigned numericSystem) {
	this->numericSystem = numericSystem;
}
