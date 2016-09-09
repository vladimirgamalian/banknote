[![Build Status](https://travis-ci.org/vladimirgamalian/banknote.svg?branch=master)](https://travis-ci.org/vladimirgamalian/banknote)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/9695/badge.svg)](https://scan.coverity.com/projects/9695)

# banknote

Little header-only C++ library for dealing with banknote wads.

```c++
// Create a new wad
Wad wad{ Banknote(Currency("USD"), 10),
	Banknote(Currency("USD"), 10),
	Banknote(Currency("USD"), 50)
};

assert(wad.getCount(Banknote(Currency("USD"), 10)) == 2);
assert(wad.getCount(Banknote(Currency("USD"), 50)) == 1);
assert(wad.getAmount(Currency("USD")) == 70);

// Add and Sub banknotes
wad.addBanknote(Banknote(Currency("USD"), 50));
wad.subBanknote(Banknote(Currency("USD"), 10));

assert(wad.getCount(Banknote(Currency("USD"), 10)) == 1);
assert(wad.getCount(Banknote(Currency("USD"), 50)) == 2);
assert(wad.getAmount(Currency("USD")) == 110);

// Sub required value
Wad slice = wad.subWad(Currency("USD"), 60);

assert(wad.getCount(Banknote(Currency("USD"), 10)) == 0);
assert(wad.getCount(Banknote(Currency("USD"), 50)) == 1);
assert(wad.getAmount(Currency("USD")) == 50);

```
