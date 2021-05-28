#include <iostream>
#include <fstream>
#include "Game.h"

void Game::ReadPlayers()
{
	std::cout << "Scrieti numarul de jucatori:\n";
	int no_of_players;
	std::cin >> no_of_players;
	while (no_of_players < 2)
	{
		std::cout << "Nu pot fi mai putin de 2 jucatori. Cheama mai multi:\n";
		std::cin >> no_of_players;
	}
	m_no_of_players = no_of_players;

	std::cout << "\n";
	for (uint8_t index = 0; index < m_no_of_players; index++)
	{
		std::string name;

		std::cout << "Scrie numele jucatorului " << index + 1 << ":\n";
		std::cin >> name;

		m_player_list.push_back(std::move(*(new Player(name))));
	}
}

void Game::Start()
{
	std::ofstream show("your_cards.txt");

	DealCards(m_player_list.front(), m_4_cards);

	show << m_player_list.front();
	show.close();

	std::cout << "\n" << m_player_list.front().GetName() << ", pastrezi cartile? (y/n)\n";

	char option = '-';
	while (option != 'y' && option != 'n')
		std::cin >> option;

	std::cout << "\n*****";

	switch (option)
	{
	case 'y':
		DealCards(m_player_list.front(), m_2_cards);

		for (uint8_t index = 1; index < m_player_list.size(); ++index)
			DealCards(m_player_list[index], m_6_cards);

		for (uint8_t counter = 0; counter < m_4_cards; ++counter)
			m_cards_on_table.push_back(std::move(m_deck.PickRandomCard()));
		break;

	case 'n':
		for (Card& card : m_player_list.front().GetCardsInHand())
			m_cards_on_table.push_back(m_player_list.front().PutCardOnTable(card));

		for (auto& player : m_player_list)
			DealCards(player, m_6_cards);
		break;
	}
}

void Game::DealCards(Player& player, const uint8_t& no_of_cards)
{
	for (uint8_t index = 0; index < no_of_cards; ++index)
		player.PickCard(std::move(m_deck.PickRandomCard()));
}

void Game::EvaluatePlayers()
{
	uint8_t biggest_no_of_cards = (uint8_t)0;
	uint8_t biggest_score = (uint8_t)0;
	std::string player_name;

	for (auto& player : m_player_list)
	{
		for (Card& card : player.GetCollectedCards())
		{
			switch (card.GetNumber())
			{
			case Number::ten:
				if (card.GetSymbol() == Symbol::diamonds)
					player.AddPoints((uint8_t)2);

				else
					player.AddPoints((uint8_t)1);
				break;

			case Number::ace: case Number::queen: case Number::jack: case Number::king:
				player.AddPoints((uint8_t)1);
				break;

			default:
				if (card.GetSymbol() == Symbol::clubs)

					if (card.GetNumber() == Number::two)
						player.AddPoints((uint8_t)2);

					else
						player.AddPoints((uint8_t)1);

				break;
			}
		}

		player.AddPoints(player.GetNumberOfTables());

		if (biggest_no_of_cards < player.GetCollectedCards().size())
			biggest_no_of_cards = (uint8_t)player.GetCollectedCards().size();
	}

	for (auto& player : m_player_list)
	{
		if (biggest_no_of_cards == player.GetCollectedCards().size())
			player.AddPoints((uint8_t)3);
	}

	for (auto& player : m_player_list)
	{
		if (player.GetTotalPoints() > biggest_score)
		{
			player_name = player.GetName();
			biggest_score = player.GetTotalPoints();
		}
	}

	std::cout << "*** Castigatorul este " << player_name << " cu scorul " << biggest_score << "! ***";
}

void Game::ReadCard(Card& card) const
{
	std::string number, symbol;
	std::cin >> number >> symbol;
	card = *(new Card(number, symbol));
}

void Game::CorrectCardIfNecessary(Card& card, const std::list<Card> list) const
{
	bool found = (std::find(list.begin(), list.end(), card) != list.end());;
	while (!found)
	{
		std::cout << "Nu poti alege cartea aceasta. Scrie alta:\n";
		
		ReadCard(card);

		found = (std::find(list.begin(), list.end(), card) != list.end());
	}
}

void Game::TakeFromTable(Player& player, Card& card_from_hand)
{
	const uint8_t value2_of_ace = (uint8_t)11;
	int no_of_cards;
	std::list<Card> cards_to_collect;

	bool correct = false;
	while (!correct)
	{
		std::cout << "Cate carti vrei sa iei?\n";
		std::cin >> no_of_cards;
		while ((uint8_t)no_of_cards > m_cards_on_table.size())
		{
			std::cout << "Nu sunt asa de multe carti pe masa. Scrie alt numar:\n";
			std::cin >> no_of_cards;
		}

		std::cout << "Scrie cartea/cartile:\n";

		for (uint8_t counter = 0; counter < no_of_cards; ++counter)
		{
			Card card_from_table = *(new Card(Number::joker, Symbol::joker));

			ReadCard(card_from_table);

			CorrectCardIfNecessary(card_from_table, m_cards_on_table);

			cards_to_collect.push_back(card_from_table);
		}

		uint8_t total_value1 = (uint8_t)0;
		uint8_t total_value2 = (uint8_t)0;
		for (auto& card : cards_to_collect)
		{
			total_value1 += (uint8_t)card.GetNumber();
			total_value2 += (uint8_t)card.GetNumber();

			if (card.GetNumber() == Number::ace)
				total_value2 += value2_of_ace - 1;
		}

		if (total_value1 == (uint8_t)card_from_hand.GetNumber() ||
			(total_value1 == value2_of_ace && card_from_hand.GetNumber() == Number::ace) ||
			(total_value2 == value2_of_ace && card_from_hand.GetNumber() == Number::ace) ||
			(total_value2 == (uint8_t)card_from_hand.GetNumber()))
		{
			correct = true;
			for (auto& card : cards_to_collect)
			{
				m_cards_on_table.remove(card);
				player.AddCardInCollection(card);
			}
			player.AddCardInCollection(player.PutCardOnTable(card_from_hand));
		}
		else
		{
			std::cout << "Ai calculat gresit, rescrie cartile pe care vrei sa le iei.\n";
		}
	}
}

void Game::Run()
{
	bool finish = false;

	ReadPlayers();
	Start();

	while (!finish)
	{
		char option;

		if (m_player_list.front().GetCardsInHand().size() > 0)
		{
			for (auto& player : m_player_list)
			{
				option = '-';

				std::ofstream show("your_cards.txt");
				Card card_from_hand = *(new Card);

				std::cout << "\n\nEste randul lui " << player.GetName() << "\n";
				std::cout << "\nCartile de pe masa:\n\n";
				for (Card& card : m_cards_on_table)
					std::cout << card << "\n";

				show << player;
				show.close();

				std::cout << "\nScrie optiunea (1, daca nu ai ce schimba, sau 2, pentru a lua de pe masa o combinatie):\n";
				while (option != '1' && option != '2')
					std::cin >> option;

				std::cout << "Ce carte vrei sa pui jos?\n";

				ReadCard(card_from_hand);

				CorrectCardIfNecessary(card_from_hand, player.GetCardsInHand());

				switch (option)
				{
				case '1':
					m_cards_on_table.push_back(player.PutCardOnTable(card_from_hand));
					break;

				case '2':
					TakeFromTable(player, card_from_hand);

					m_last_player_who_took_cards = player.GetName();

					if (m_cards_on_table.size() == 0)
						player.IncrementTablesCounter();
					break;
				}

				std::ofstream show2("your_cards.txt");
				show2 << "-";
				show2.close();

				std::cout << "\n*****";

				char ready = 'n';
				while (ready == 'n' || ready != 'y')
				{
					std::cout << "\n\nPregatit? (y/n)\n";
					std::cin >> ready;
				}
			}
		}
		else
		{
			if (m_deck.GetNumberOfRemainingCards() / m_6_cards >= m_no_of_players)
				for (auto& player : m_player_list)
					DealCards(player, m_6_cards);
			else
				if (m_deck.GetNumberOfRemainingCards() / m_6_cards < m_no_of_players && m_deck.GetNumberOfRemainingCards() >= m_no_of_players)
					for (auto& player : m_player_list)
						DealCards(player, m_deck.GetNumberOfRemainingCards() / m_6_cards);
				else
				{
					if (m_cards_on_table.size() > 0)
						for (auto& player_aux : m_player_list)
							if (player_aux.GetName() == m_last_player_who_took_cards)
								for (auto& card_aux : m_cards_on_table)
								{
									player_aux.PickCard(card_aux);
									m_cards_on_table.remove(card_aux);
								}
					finish = true;
				}
		}
	}

	EvaluatePlayers();
}
