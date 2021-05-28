#include "Player.h"

Player::Player(const std::string& name)
	:m_name(name)
{
	m_tables_counter = (uint8_t)0;
	m_total_points = (uint8_t)0;
}

void Player::PickCard(const Card& card)
{
	m_cards_in_hand.push_back(card);
}

std::string Player::GetName() const
{
	return m_name;
}

Card Player::PutCardOnTable(const Card& card)
{
	m_cards_in_hand.remove(card);
	return card;
}

std::list<Card> Player::GetCardsInHand() const
{
	return m_cards_in_hand;
}

void Player::IncrementTablesCounter()
{
	++m_tables_counter;
}

void Player::AddCardInCollection(const Card& card)
{
	m_collected_cards.push_back(card);
}

std::list<Card> Player::GetCollectedCards() const
{
	return m_collected_cards;
}

uint8_t Player::GetNumberOfTables() const
{
	return m_tables_counter;
}

void Player::AddPoints(const uint8_t& points)
{
	m_total_points += points;
}

uint8_t Player::GetTotalPoints() const
{
	return m_total_points;
}

std::ostream& operator<<(std::ostream& print, const Player& player)
{
	print << player.GetName() << "\n\n"<<"Carti in mana:\n\n";
	for (Card card : player.GetCardsInHand())
		print << card << ";\n";
	return print;
}