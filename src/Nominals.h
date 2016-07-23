#pragma once
#include "Wad.h"

class Nominals
{
public:
	static const Wad& rub()
	{
		static Wad w {
			Banknote(Currency("RUB"), 10),
			Banknote(Currency("RUB"), 50),
			Banknote(Currency("RUB"), 100),
			Banknote(Currency("RUB"), 500),
			Banknote(Currency("RUB"), 1000),
			Banknote(Currency("RUB"), 5000)
		};
		return w;
	}
};
