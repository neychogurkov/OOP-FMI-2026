#pragma once

namespace Resources {
	namespace Card {
		const int MIN_NUMBER = 0;
		const int MAX_NUMBER = 9;
	}

	namespace Deck {
		const size_t MAX_CARDS_COUNT = 108;
	}

	namespace Player {
		const size_t MAX_HAND_COUNT = Deck::MAX_CARDS_COUNT - 1;
	}

	namespace Game {
		const size_t MAX_PLAYERS_COUNT = 4;
	}
}