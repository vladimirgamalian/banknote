#include "stdafx.h"
#include "Defines.h"

TEST_CASE("Wad()")
{
	Wad wad;
	REQUIRE(wad.getAmount(RUB) == 0);
	REQUIRE(wad.getCount(RUB_100) == 0);
	REQUIRE(wad.getCount(RUB_500) == 0);
}

TEST_CASE("Wad(std::initializer_list<Banknote> l)")
{
	Wad wad({ RUB_100, RUB_100, RUB_500 });
	REQUIRE(wad.getCount(RUB_100) == 2);
	REQUIRE(wad.getCount(RUB_500) == 1);
}

TEST_CASE("Wad(const std::vector<Banknote>& v)")
{
	std::vector<Banknote> v;
	v.push_back(RUB_100);
	v.push_back(RUB_100);
	v.push_back(RUB_500);
	Wad wad(v);
	REQUIRE(wad.getCount(RUB_100) == 2);
	REQUIRE(wad.getCount(RUB_500) == 1);
}
