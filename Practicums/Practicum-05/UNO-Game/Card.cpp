#include "Card.h"
#include "CardValidation.h"
#include "Resources.h"

Card::Card(Type type, Color color, int number) {
	this->type = type;
	this->color = color;
	setNumber(number);
}

void Card::setNumber(int number) {
	if (this->type == Type::Number || !isValidNumber(number)) {
		number = Resources::Card::MIN_NUMBER;
	}

	this->number = number;
}

Color Card::getColor() const {
	return color;
}

Type Card::getType() const {
	return type;
}

int Card::getNumber() const {
	return number;
}
