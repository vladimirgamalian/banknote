#pragma once
#include "Banknote.h"
#include <map>

class Wad
{
public:
	void addBanknote(const Banknote& banknote)
	{
		banknotes[banknote]++;
	}

	Wad subWad(const Currency& currency, int totalAmount)
	{
		Wad result;
		for (;;)
		{
			Banknote b = getHighest(currency, totalAmount);
			if (b == Banknote(currency, 0))
				break;

			subBanknote(b);
			result.addBanknote(b);
		}
		return result;
	}

	// will throw exception, when banknote not exists
	void subBanknote(const Banknote& banknote)
	{
		if ((--banknotes.at(banknote)) == 0)
			banknotes.erase(banknote);
	}

	int getCount(const Banknote& banknote)
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

	//TODO: adapt to divider
	Banknote getHighest(const Currency& currency, int limit) const
	{
		Banknote result(currency, 0);
		for (auto b : banknotes)
			if (b.first.currency == currency)
				if (b.first.value <= limit)
					if (b.first.value > result.value)
						result = b.first;
		return result;
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
