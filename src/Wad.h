#pragma once
#include "Banknote.h"
#include <map>

class Wad
{
public:
	void push(const Banknote& banknote)
	{
		banknotes[banknote]++;
	}

	int getAmount(const Banknote& banknote)
	{
		int total = 0;

		for (auto b : banknotes)
			if (b.first == banknote)
				total += b.second;

		return total;
	}

	int getAmount(const Currency& currency)
	{
		int total = 0;

		for (auto b: banknotes)
			if (b.first.currency == currency)
				total += (b.first.value * b.second);

		return total;
	}

private:
	struct BanknoteCompare
	{
		bool operator() (const Banknote& lhs, const Banknote& rhs) const
		{
			if (lhs.value == rhs.value)
				return lhs.currency.toString() < rhs.currency.toString();
			return lhs.value < rhs.value;
		}
	};
	std::map<Banknote, int, BanknoteCompare> banknotes;
};
