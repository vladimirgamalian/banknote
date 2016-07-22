#include "stdafx.h"
#include "../Wad.h"


#define RUB Currency("RUB")
#define RUB_0 Banknote(RUB, 0)
#define RUB_100 Banknote(RUB, 100)
#define RUB_500 Banknote(RUB, 500)

TEST_CASE("Currency")
{
	Currency currency("RUB");
	REQUIRE(currency.toString() == "RUB");
	REQUIRE(currency == Currency("RUB"));
	REQUIRE_FALSE(currency == Currency("USD"));
}

TEST_CASE("Banknote")
{
	Banknote banknote(Currency("RUB"), 1000);
	REQUIRE(banknote.toString() == "1000 RUB");
	REQUIRE(banknote == Banknote(Currency("RUB"), 1000));
	REQUIRE_FALSE(banknote == Banknote(Currency("RUB"), 100));
	REQUIRE_FALSE(banknote == Banknote(Currency("USD"), 1000));
}

TEST_CASE("Wad")
{
	Wad wad;
	REQUIRE(wad.getAmount(RUB) == 0);
	REQUIRE(wad.getCount(RUB_100) == 0);

	wad.addBanknote(RUB_100);
	REQUIRE(wad.getAmount(RUB) == 100);
	REQUIRE(wad.getCount(RUB_100) == 1);

	wad.addBanknote(RUB_100);
	REQUIRE(wad.getAmount(RUB) == 200);
	REQUIRE(wad.getCount(RUB_100) == 2);

	wad.addBanknote(RUB_500);
	REQUIRE(wad.getAmount(RUB) == 700);
	REQUIRE(wad.getCount(RUB_100) == 2);
	REQUIRE(wad.getCount(RUB_500) == 1);

	// sub banknotes

	wad.subBanknote(RUB_100);
	REQUIRE(wad.getAmount(RUB) == 600);
	REQUIRE(wad.getCount(RUB_100) == 1);
	REQUIRE(wad.getCount(RUB_500) == 1);

	wad.subBanknote(RUB_500);
	REQUIRE(wad.getAmount(RUB) == 100);
	REQUIRE(wad.getCount(RUB_100) == 1);
	REQUIRE(wad.getCount(RUB_500) == 0);

	// find highest

	REQUIRE(wad.getHighest(RUB, 100) == RUB_100);
	REQUIRE(wad.getHighest(RUB, 99) == RUB_0);
	REQUIRE(wad.getHighest(RUB, 500) == RUB_100);
	wad.addBanknote(RUB_500);
	REQUIRE(wad.getHighest(RUB, 500) == RUB_500);


	// sub wad
	{
		Wad wad;
		wad.addBanknote(RUB_100);
		wad.addBanknote(RUB_100);
		wad.addBanknote(RUB_500);

		REQUIRE(wad.getCount(RUB_100) == 2);
		REQUIRE(wad.getCount(RUB_500) == 1);

		Wad w = wad.subWad(RUB, 200);
		REQUIRE(w.getCount(RUB_100) == 2);

		REQUIRE(wad.getCount(RUB_100) == 0);
		REQUIRE(wad.getCount(RUB_500) == 1);
	}

	// sub wad
	{
		Wad wad;
		wad.addBanknote(RUB_100);
		wad.addBanknote(RUB_100);
		wad.addBanknote(RUB_500);

		REQUIRE(wad.getCount(RUB_100) == 2);
		REQUIRE(wad.getCount(RUB_500) == 1);

		Wad w = wad.subWad(RUB, 300);
		REQUIRE(w.getCount(RUB_100) == 2);

		REQUIRE(wad.getCount(RUB_100) == 0);
		REQUIRE(wad.getCount(RUB_500) == 1);
	}
}
