#include <iostream>
#include "Deck.h"
#include "DeckValidation.h"
#include "Resources.h"
#include <cstdlib>

void Deck::initializeCards() {
	size_t index = 0;

	initializeNumberCards(index);
	initializeActionCards(index);
	initializeWildCards(index);
}

void Deck::initializeNumberCards(size_t index) {
	Color colors[4] = { Color::Blue, Color::Green, Color::Red, Color::Yellow };

	for (size_t i = 0; i < 4; i++) {
		Color color = colors[i];
		cards[index++] = Card(Type::Number, color, 0);

		for (size_t j = 1; j <= 9; j++) {
			cards[index++] = Card(Type::Number, color, j);
			cards[index++] = Card(Type::Number, color, j);
		}
	}
}

void Deck::initializeActionCards(size_t index) {
	Color colors[4] = { Color::Blue, Color::Green, Color::Red, Color::Yellow };

	for (size_t i = 0; i < 4; i++) {
		Color color = colors[i];

		for (size_t j = 0; j < 2; j++) {
			cards[index++] = Card(Type::Skip, color);
			cards[index++] = Card(Type::Reverse, color);
			cards[index++] = Card(Type::DrawTwo, color);
		}
	}
}

void Deck::initializeWildCards(size_t index) {
	for (size_t i = 0; i < 4; i++) {
		cards[index++] = Card(Type::Wild, Color::Wild);
		cards[index++] = Card(Type::WildDrawFour, Color::Wild);
	}
}

void Deck::shuffle() {
	for (size_t i = Resources::Deck::MAX_CARDS_COUNT - 1; i >= 0; i--) {
		size_t toSwap = rand() % (i + 1);
		std::swap(cards[i], cards[toSwap]);
	}
}

Deck::Deck() {
	initializeCards();
}

const Card* Deck::getCards() const {
	return cards;
}

const Card* Deck::getCards(size_t index) const {
	if (!isValidDeckIndex(index)) {
		return nullptr;
	}

	return &cards[index];
}
