#pragma once
#include <fstream>
#include "Constants.h"

class KBaseNumber {
private:
	char number[Constants::MAX_NUMBER_LENGTH + 1];
	unsigned numericSystem;

	unsigned charToValue(char ch) const;
	unsigned toDecimal() const;
	KBaseNumber decimalToOtherNumericSystem(unsigned decimalNumber, unsigned numericSystem) const;
public:
	KBaseNumber();
	KBaseNumber(const char* number, unsigned numericSystem);
	int compareWith(const KBaseNumber& other) const;
	void update(const char* number, unsigned numericSystem);
	void print() const;
	void printConvertedTo(unsigned numericSystem) const;
	void saveToFile(const char* path) const;
	void readFromFile(const char* path);

	const char* getNumber() const;
	unsigned getNumericSystem() const;
	void setNumber(const char* number);
	void setNumericSystem(unsigned numericSystem);
};

