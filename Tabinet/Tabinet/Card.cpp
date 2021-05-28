#include "Card.h"

Card::Card(const Number& number, const Symbol& symbol)
	:m_number(number), m_symbol(symbol)
{

}

Card::Card(const std::string& number, const std::string& symbol)
	: m_number(ParseStringToNumber(number)), m_symbol(ParseStringToSymbol(symbol))
{

}

Number Card::GetNumber() const
{
	return m_number;
}

Symbol Card::GetSymbol() const
{
	return m_symbol;
}

std::string Card::ParseNumberToString() const
{
	switch (m_number)
	{
	case Number::ace: return "A"; break;
	case Number::two: return "2"; break;
	case Number::three: return "3"; break;
	case Number::four: return "4"; break;
	case Number::five: return "5"; break;
	case Number::six: return "6"; break;
	case Number::seven: return "7"; break;
	case Number::eight: return "8"; break;
	case Number::nine: return "9"; break;
	case Number::ten: return "10"; break;
	case Number::jack: return "J"; break;
	case Number::queen: return "Q"; break;
	case Number::king: return "K"; break;
	}
	return "";
}

std::string Card::ParseSymbolToString() const
{
	switch (m_symbol)
	{
	case Symbol::hearts:
		return "de inima rosie";
		break;
	case Symbol::spades:
		return "de inima neagra";
		break;
	case Symbol::diamonds:
		return "de romb";
		break;
	case Symbol::clubs:
		return "de trefla";
		break;
	}
	return "";
}

Number Card::ParseStringToNumber(const std::string& number) const
{
	if (number == "A") return Number::ace;
	if (number == "2") return Number::two;
	if (number == "3") return Number::three;
	if (number == "4") return Number::four;
	if (number == "5") return Number::five;
	if (number == "6") return Number::six;
	if (number == "7") return Number::seven;
	if (number == "8") return Number::eight;
	if (number == "9") return Number::nine;
	if (number == "10") return Number::ten;
	if (number == "J") return Number::jack;
	if (number == "Q") return Number::queen;
	if (number == "K") return Number::king;
	std::cout << "*Joker* ";
	return Number::joker;
}

Symbol Card::ParseStringToSymbol(const std::string& symbol) const
{
	if (symbol == "de_inima_rosie") return Symbol::hearts;
	if (symbol == "de_inima_neagra") return Symbol::spades;
	if (symbol == "de_romb") return Symbol::diamonds;
	if (symbol == "de_trefla") return Symbol::clubs;
	std::cout << "*Joker* ";
	return Symbol::joker;
}

bool Card::operator==(const Card& card2) const
{
	return (m_number == card2.m_number && m_symbol == card2.m_symbol);
}

std::ostream& operator<<(std::ostream& print, const Card& card)
{
	print << card.ParseNumberToString() << " " << card.ParseSymbolToString();
	return print;
}