#pragma once
#include <cstdint>

enum class Number : uint8_t
{
	ace = 1,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	jack = 12,
	queen,
	king,
	joker
};
enum class Symbol : uint8_t
{
	hearts, spades, diamonds, clubs, joker
};