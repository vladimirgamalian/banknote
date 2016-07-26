#pragma once
#include "Banknote.h"
#include <map>

class Wad
{
public:
	Wad()
	{

	}

	Wad(std::initializer_list<Banknote> l)
	{
		for (auto i : l)
			addBanknote(i);
	}

	Wad(const std::vector<Banknote>& v)
	{
		for (auto i : v)
			addBanknote(i);
	}

	bool operator == (const Wad& other) const
	{
		return banknotes == other.banknotes;
	}
	bool operator != (const Wad& other) const
	{
		return banknotes != other.banknotes;
	}

	bool test(const Wad& nominals) const
	{
		for (auto b : banknotes)
			if (!nominals.getCount(b.first))
				return false;
		return true;
	}

	void addBanknote(const Banknote& banknote)
	{
		//TODO: test for empty banknote (or prevent construct empty banknote)
		if (banknote.value)
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

	int getCount(const Banknote& banknote) const
	{
		int total = 0;

		for (auto b : banknotes)
			if (b.first == banknote)
				total += b.second;

		return total;
	}

	int getAmount(const Currency& currency) const
	{
		int total = 0;

		for (auto b: banknotes)
			if (b.first.currency == currency)
				total += (b.first.value * b.second);

		return total;
	}

	std::string toString() const
	{
		std::string result;
		for (auto b : banknotes)
			result += b.first.toString() + " (" + std::to_string(b.second) + ")\n";
		return result;
	}

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
			if (lhs.currency.toString() == rhs.currency.toString())
				return lhs.value < rhs.value;
			return lhs.currency.toString() < rhs.currency.toString();
		}
	};

	std::map<Banknote, int, BanknoteCompare> banknotes;
};
