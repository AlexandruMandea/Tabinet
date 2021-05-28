#pragma once
#include <list>
#include <string>
#include "Card.h"

class Player
{
public:
	Player(const std::string& name);
	std::string GetName() const;

	void PickCard(const Card& card);
	Card PutCardOnTable(const Card& card);
	std::list<Card> GetCardsInHand() const;

	void AddCardInCollection(const Card& card);
	std::list<Card> GetCollectedCards() const;

	void IncrementTablesCounter();
	uint8_t GetNumberOfTables() const;

	void AddPoints(const uint8_t& points);
	uint8_t GetTotalPoints() const;

	friend std::ostream& operator <<(std::ostream& print, const Player& player);

private:
	std::string m_name;
	std::list<Card> m_cards_in_hand;
	std::list<Card> m_collected_cards;
	std::uint8_t m_tables_counter;
	std::uint8_t m_total_points;
};