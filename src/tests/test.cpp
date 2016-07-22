#include "stdafx.h"
#include "../Wad.h"

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
	REQUIRE(wad.getAmount(Currency("RUB")) == 0);
	REQUIRE(wad.getAmount(Banknote(Currency("RUB"), 100)) == 0);

	wad.push(Banknote(Currency("RUB"), 100));
	REQUIRE(wad.getAmount(Currency("RUB")) == 100);
	REQUIRE(wad.getAmount(Banknote(Currency("RUB"), 100)) == 1);

	wad.push(Banknote(Currency("RUB"), 100));
	REQUIRE(wad.getAmount(Currency("RUB")) == 200);
	REQUIRE(wad.getAmount(Banknote(Currency("RUB"), 100)) == 2);

	wad.push(Banknote(Currency("RUB"), 500));
	REQUIRE(wad.getAmount(Currency("RUB")) == 700);
	REQUIRE(wad.getAmount(Banknote(Currency("RUB"), 100)) == 2);
	REQUIRE(wad.getAmount(Banknote(Currency("RUB"), 500)) == 1);
}
