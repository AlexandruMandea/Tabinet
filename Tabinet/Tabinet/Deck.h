#pragma once
#include <vector>
#include "Card.h"

class Deck
{
public:
	Deck();
	void GenerateCards();
	Card PickRandomCard();

	std::vector<Card> GetDeck() const;

	uint8_t GetNumberOfRemainingCards() const;

private:
	std::vector<Card> m_deck;
	uint8_t m_remaining_cards;
};