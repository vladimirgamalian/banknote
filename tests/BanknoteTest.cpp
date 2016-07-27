#include "TestDefines.h"

TEST_CASE("Banknote")
{
	Banknote banknote(Currency("RUB"), 1000);
	REQUIRE(banknote.toString() == "1000 RUB");
	REQUIRE(banknote == Banknote(Currency("RUB"), 1000));
	REQUIRE_FALSE(banknote == Banknote(Currency("RUB"), 100));
	REQUIRE_FALSE(banknote == Banknote(Currency("USD"), 1000));
}
