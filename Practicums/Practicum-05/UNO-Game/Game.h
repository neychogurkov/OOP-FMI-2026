#pragma once
#include "Deck.h"
#include "Player.h"
#include "Resources.h"

class Game {
private:
	Deck deck;
	size_t currentDeckIndex;
	Player players[Resources::Game::MAX_PLAYERS_COUNT];
	size_t currentPlayerIndex;

public:
	Game();

	void startGame();
};

