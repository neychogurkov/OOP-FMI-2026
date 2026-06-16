#include "CardValidation.h"
#include "Resources.h"

bool isValidNumber(int number) {
	return number >= Resources::Card::MIN_NUMBER && number <= Resources::Card::MAX_NUMBER;
}
