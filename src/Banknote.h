#pragma once
#include "Currency.h"

class Banknote
{
public:
	friend class Wad;

	Banknote(const Currency& currency, int value) :
		currency(currency), value(value)
	{

	}

	std::string toString() const
	{
		return std::to_string(value) + " " + currency.toString();
	}

	bool operator == (const Banknote& other) const
	{
		return (currency == other.currency) && (value == other.value);
	}

private:
	Currency currency;
	int value;
};
