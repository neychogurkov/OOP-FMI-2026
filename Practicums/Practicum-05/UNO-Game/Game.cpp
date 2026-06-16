#include "Game.h"
#include <iostream>

Game::Game() :currentDeckIndex(0), currentPlayerIndex(0) {
}

void Game::startGame() {
	deck.shuffle();

	for (size_t i = 0; i < Resources::Deck::MAX_CARDS_COUNT; i++) {
		const Card* card = deck.getCards(i);

	}
}
