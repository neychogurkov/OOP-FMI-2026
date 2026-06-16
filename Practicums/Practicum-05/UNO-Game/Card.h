#pragma once
#include "Color.h"
#include "Type.h"

class Card {
private:
	Color color;
	Type type;
	int number;

public:
	Card() = default;
	Card(Type type, Color color, int number = -1);

	void setNumber(int number);

	Color getColor() const;
	Type getType() const;
	int getNumber() const;
};

