#pragma once
#include <string.h>

class Currency
{
public:
	Currency(const std::string& code) : code(code)
	{

	}

	std::string toString() const
	{
		return code;
	}

	bool operator == (const Currency& other) const
	{
		return code == other.code;
	}

private:
	std::string code;
};
