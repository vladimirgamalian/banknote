#include "TestDefines.h"

TEST_CASE("Nominals")
{
	Wad wad = Nominals::rub();
	REQUIRE(wad == Wad({ RUB_10, RUB_50, RUB_100, RUB_500, RUB_1000, RUB_5000 }));
}
