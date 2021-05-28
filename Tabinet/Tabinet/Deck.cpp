#include <chrono>
#include <random>
#include "Deck.h"

Deck::Deck()
{
	unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	GenerateCards();
}

void Deck::GenerateCards()
{
	const std::vector<Number> m_numbers =
	{
		Number::ace, Number::two, Number::three, Number::four, Number::five, Number::six, Number::seven,
		Number::eight, Number::nine,Number::ten, Number::jack, Number::queen, Number::king
	};
	const std::vector<Symbol> m_symbols =
	{
		Symbol::hearts, Symbol::spades, Symbol::diamonds, Symbol::clubs
	};

	for (auto number : m_numbers)
		for (auto symbol : m_symbols)
		{
			m_deck.push_back(std::move(*(new Card(number, symbol))));
			++m_remaining_cards;
		}
}

Card Deck::PickRandomCard()
{
	uint8_t random_index = rand() % m_remaining_cards;

	Card card = std::move(m_deck[random_index]);
	m_deck.erase(m_deck.begin() + random_index);

	--m_remaining_cards;

	return std::move(card);
}

std::vector<Card> Deck::GetDeck() const
{
	return m_deck;
}

uint8_t Deck::GetNumberOfRemainingCards() const
{
	return m_remaining_cards;
}