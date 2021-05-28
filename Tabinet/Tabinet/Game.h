#pragma once
#include <unordered_map>
#include <map>
#include <list>
#include "Deck.h"
#include "Player.h"

class Game
{
public:
	void ReadPlayers();

	void Start();
	void DealCards(Player& player, const uint8_t& no_of_cards);

	void EvaluatePlayers();

	void ReadCard(Card& card) const;
	void CorrectCardIfNecessary(Card& card, const std::list<Card> list) const;
	void TakeFromTable(Player& player, Card& card_from_hand);

	void Run();

private:
	std::vector<Player> m_player_list;
	uint8_t m_no_of_players = 0;
	Deck m_deck;
	std::list<Card> m_cards_on_table;
	std::string m_last_player_who_took_cards;

	const uint8_t m_6_cards = 6;
	const uint8_t m_4_cards = 4;
	const uint8_t m_2_cards = 2;
};