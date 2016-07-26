#include "stdafx.h"
#include "Defines.h"

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
}

TEST_CASE("Wad zero banknote")
{
	Wad wad {RUB_10, RUB_0};
	REQUIRE(wad.getAmount(RUB) == 10);
	REQUIRE(wad.getCount(RUB_10) == 1);
	REQUIRE(wad.getCount(RUB_0) == 0);
	wad.addBanknote(RUB_0);
	REQUIRE(wad.getCount(RUB_0) == 0);
	REQUIRE(wad.getAmount(RUB) == 10);
}

TEST_CASE("Wad::Wad")
{
	{
		Wad wad{ RUB_50, RUB_100 };
		REQUIRE(wad.getCount(RUB_50) == 1);
		REQUIRE(wad.getCount(RUB_100) == 1);
		REQUIRE(wad.getCount(RUB_500) == 0);
	}
	{
		Wad wad{ RUB_50, RUB_50 };
		REQUIRE(wad.getCount(RUB_50) == 2);
		REQUIRE(wad.getCount(RUB_100) == 0);
	}

	//TODO: separate test
	{
		Wad wad{ RUB_50, RUB_100 };
		REQUIRE(wad == Wad({ RUB_50, RUB_100 }));
		REQUIRE(wad == Wad({ RUB_100, RUB_50 }));
		REQUIRE(wad != Wad({ RUB_100 }));
		REQUIRE(wad != Wad({ RUB_50, RUB_500 }));
	}

}

TEST_CASE("Wad::subWad")
{
	Wad wad;
	wad.addBanknote(RUB_100);
	wad.addBanknote(RUB_100);
	wad.addBanknote(RUB_500);

	SECTION("test0000")
	{
		REQUIRE(wad.getCount(RUB_100) == 2);
		REQUIRE(wad.getCount(RUB_500) == 1);

		Wad w = wad.subWad(RUB, 200);
		REQUIRE(w.getCount(RUB_100) == 2);

		REQUIRE(wad.getCount(RUB_100) == 0);
		REQUIRE(wad.getCount(RUB_500) == 1);
	}

	SECTION("test0001")
	{
		REQUIRE(wad.getCount(RUB_100) == 2);
		REQUIRE(wad.getCount(RUB_500) == 1);

		Wad w = wad.subWad(RUB, 300);
		REQUIRE(w.getCount(RUB_100) == 2);

		REQUIRE(wad.getCount(RUB_100) == 0);
		REQUIRE(wad.getCount(RUB_500) == 1);
	}
}

TEST_CASE("Nominals")
{
	Wad wad = Nominals::rub();
	REQUIRE(wad == Wad({RUB_10, RUB_50, RUB_100, RUB_500, RUB_1000, RUB_5000}));
}

TEST_CASE("Wad::test")
{
	//TODO: more tests
	Wad wad { RUB_50, RUB_100, RUB_500 };
	REQUIRE(wad.test(Nominals::rub()));
	wad.addBanknote(USD_100);
	REQUIRE_FALSE(wad.test(Nominals::rub()));
}
