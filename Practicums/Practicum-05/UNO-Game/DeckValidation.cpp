#include "DeckValidation.h"
#include "Resources.h"

bool isValidDeckIndex(size_t index) {
    return index >= 0 && index < Resources::Deck::MAX_CARDS_COUNT;
}
