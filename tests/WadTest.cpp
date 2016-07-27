#include "TestDefines.h"

TEST_CASE("Wad::Wad()")
{
	Wad wad;
	REQUIRE(wad.getAmount(RUB) == 0);
	REQUIRE(wad.getCount(RUB_100) == 0);
	REQUIRE(wad.getCount(RUB_500) == 0);
}

TEST_CASE("Wad::Wad(std::initializer_list<Banknote> l)")
{
	SECTION("test0000")
	{
		Wad wad{ RUB_100, RUB_100, RUB_500 };
		REQUIRE(wad.getCount(RUB_0) == 0);
		REQUIRE(wad.getCount(RUB_100) == 2);
		REQUIRE(wad.getCount(RUB_500) == 1);
		REQUIRE(wad.getAmount(RUB) == 700);
	}

	SECTION("test0001")
	{
		Wad wad{ RUB_0 };
		REQUIRE(wad.getCount(RUB_0) == 0);
		REQUIRE(wad.getAmount(RUB) == 0);
	}

	SECTION("test0002")
	{
		Wad wad{ RUB_100, RUB_0 };
		REQUIRE(wad.getCount(RUB_0) == 0);
		REQUIRE(wad.getCount(RUB_100) == 1);
		REQUIRE(wad.getCount(RUB_500) == 0);
		REQUIRE(wad.getAmount(RUB) == 100);
	}
}

TEST_CASE("Wad::Wad(const std::vector<Banknote>& v)")
{
	std::vector<Banknote> v;
	v.push_back(RUB_100);
	v.push_back(RUB_100);
	v.push_back(RUB_500);
	Wad wad(v);
	REQUIRE(wad.getCount(RUB_100) == 2);
	REQUIRE(wad.getCount(RUB_500) == 1);
}

TEST_CASE("bool Wad::operator == (const Wad& other) const")
{
	Wad wad{ RUB_50, RUB_100 };
	REQUIRE(wad == Wad({ RUB_50, RUB_100 }));
	REQUIRE(wad == Wad({ RUB_100, RUB_50 }));

	REQUIRE_FALSE(wad == Wad());
	REQUIRE_FALSE(wad == Wad({ RUB_50 }));
	REQUIRE_FALSE(wad == Wad({ RUB_50, RUB_50 }));
	REQUIRE_FALSE(wad == Wad({ RUB_50, RUB_500 }));
	REQUIRE_FALSE(wad == Wad({ RUB_50, USD_100 }));
}

TEST_CASE("bool Wad::operator != (const Wad& other) const")
{
	Wad wad{ RUB_50, RUB_100 };
	REQUIRE(wad != Wad());
	REQUIRE(wad != Wad({ RUB_100 }));
	REQUIRE(wad != Wad({ RUB_50, RUB_50 }));
	REQUIRE(wad != Wad({ RUB_50, RUB_500 }));
	REQUIRE(wad != Wad({ RUB_50, USD_100 }));

	REQUIRE_FALSE(wad != Wad({ RUB_50, RUB_100 }));
	REQUIRE_FALSE(wad != Wad({ RUB_100, RUB_50 }));
}

TEST_CASE("void Wad::addBanknote(const Banknote& banknote)")
{
	Wad wad;
	REQUIRE(wad.getAmount(RUB) == 0);
	REQUIRE(wad.getCount(RUB_100) == 0);

	wad.addBanknote(RUB_0);
	REQUIRE(wad.getAmount(RUB) == 0);
	REQUIRE(wad.getCount(RUB_0) == 0);
	REQUIRE(wad.getCount(RUB_100) == 0);

	wad.addBanknote(RUB_100);
	REQUIRE(wad.getAmount(RUB) == 100);
	REQUIRE(wad.getCount(RUB_100) == 1);

	wad.addBanknote(RUB_0);
	REQUIRE(wad.getAmount(RUB) == 100);
	REQUIRE(wad.getCount(RUB_0) == 0);
	REQUIRE(wad.getCount(RUB_100) == 1);

	wad.addBanknote(RUB_100);
	REQUIRE(wad.getAmount(RUB) == 200);
	REQUIRE(wad.getCount(RUB_100) == 2);

	wad.addBanknote(RUB_500);
	REQUIRE(wad.getAmount(RUB) == 700);
	REQUIRE(wad.getCount(RUB_100) == 2);
	REQUIRE(wad.getCount(RUB_500) == 1);
}

TEST_CASE("void Wad::subBanknote(const Banknote& banknote)")
{
	Wad wad{ RUB_100, RUB_100, RUB_500 };

	wad.subBanknote(RUB_100);
	REQUIRE(wad.getAmount(RUB) == 600);
	REQUIRE(wad.getCount(RUB_100) == 1);
	REQUIRE(wad.getCount(RUB_500) == 1);

	wad.subBanknote(RUB_500);
	REQUIRE(wad.getAmount(RUB) == 100);
	REQUIRE(wad.getCount(RUB_100) == 1);
	REQUIRE(wad.getCount(RUB_500) == 0);
}

TEST_CASE("Wad Wad::subWad(const Currency& currency, int totalAmount)")
{
	Wad wad{ RUB_100, RUB_100, RUB_500 };

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

	SECTION("test0002")
	{
		Wad wad{ RUB_100, RUB_100, RUB_100, RUB_100, RUB_100, RUB_100, RUB_500 };

		REQUIRE(wad.getCount(RUB_100) == 6);
		REQUIRE(wad.getCount(RUB_500) == 1);

		Wad w = wad.subWad(RUB, 500);
		REQUIRE(w.getCount(RUB_500) == 1);

		REQUIRE(wad.getCount(RUB_100) == 6);
		REQUIRE(wad.getCount(RUB_500) == 0);
	}
}

TEST_CASE("int getCount(const Banknote& banknote) const")
{

}

TEST_CASE("int getAmount(const Currency& currency) const")
{

}

TEST_CASE("Banknote getHighest(const Currency& currency, int limit) const")
{
	Wad wad{ RUB_100 };
	REQUIRE(wad.getHighest(RUB, 100) == RUB_100);
	REQUIRE(wad.getHighest(RUB, 99) == RUB_0);
	REQUIRE(wad.getHighest(RUB, 500) == RUB_100);
	wad.addBanknote(RUB_500);
	REQUIRE(wad.getHighest(RUB, 500) == RUB_500);
}

TEST_CASE("bool test(const Wad& nominals) const")
{
	//TODO: more tests
	Wad wad{ RUB_50, RUB_100, RUB_500 };
	REQUIRE(wad.test(Nominals::rub()));
	wad.addBanknote(USD_100);
	REQUIRE_FALSE(wad.test(Nominals::rub()));
}

TEST_CASE("std::string toString() const")
{

}
