#pragma once
#include <iostream>
#include "CardType.h"

class Card
{
public:
	Card() = default;
	Card(Card const& other) = default;
	~Card() = default;
	Card(const Number& number, const Symbol& symbol);
	Card(const std::string& number, const std::string& symbol);

	Number GetNumber() const;
	Symbol GetSymbol() const;

	std::string ParseNumberToString() const;
	std::string ParseSymbolToString() const;
	Number ParseStringToNumber(const std::string& number) const;
	Symbol ParseStringToSymbol(const std::string& symbol) const;

	bool operator==(const Card& card2) const;
	friend std::ostream& operator<<(std::ostream& print, const Card& card);
private:
	Number m_number;
	Symbol m_symbol;
};