#pragma once
#include "Card.h"
#include "Resources.h"

class Player {
	Card hand[Resources::Player::MAX_HAND_COUNT];
	size_t handCount;
};

