#pragma once
#include "Card.h"
#include "Resources.h"

class Deck {
private:
	Card cards[Resources::Deck::MAX_CARDS_COUNT];
	
	void initializeCards();
	void initializeNumberCards(size_t index);
	void initializeActionCards(size_t index);
	void initializeWildCards(size_t index);

public:
	Deck();

	const Card* getCards() const;
	const Card* getCards(size_t index) const;

	void shuffle();
};

