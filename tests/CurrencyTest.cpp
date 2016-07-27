#include "TestDefines.h"

TEST_CASE("Currency")
{
	Currency currency("RUB");
	REQUIRE(currency.toString() == "RUB");
	REQUIRE(currency == Currency("RUB"));
	REQUIRE_FALSE(currency == Currency("USD"));
}
