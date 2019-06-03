#include <iostream>
#include <map>

using namespace std;

const int MAX_INPUT = 7489;

// available coins
enum class Coins : int
{
	C1 = 1,
	C5 = 5,
	C10 = 10,
	C25 = 25,
	C50 = 50,
};
const Coins ascending[] = {Coins::C1, Coins::C5, Coins::C10, Coins::C25, Coins::C50};
const Coins nonsingular[] = {Coins::C5, Coins::C10, Coins::C25, Coins::C50};
const Coins MAX_COIN = Coins::C50;

// ns = nonsingular
map<Coins, int> nsWhich = {
		{Coins::C5, 0},
		{Coins::C10, 1},
		{Coins::C25, 2},
		{Coins::C50, 3}};

// global arrays are initialized to zeroes
int cache[MAX_INPUT + 1][4]; // 2nd dimension means: up to (j+2)th available coin
void initCache()
{
	// a lot of prefilling, because of a safe guard that goes back by 1 in nsWhich
	for (auto iter = nsWhich.begin(); iter != nsWhich.end(); ++iter)
	{
		for (int i = 0; i < 5; i++)
		{
			cache[i][iter->second] = 1;
		}
	}
}

int magic(int n, Coins upTo = MAX_COIN)
{
	if (cache[n][nsWhich[upTo]] > 0)
	{
		return cache[n][nsWhich[upTo]];
	}

	// safe guard mentioned in initCache()
	if ((int)upTo > n)
	{
		cache[n][nsWhich[upTo]] = magic(n, nonsingular[nsWhich[upTo] - 1]);
	}

	int ways = 1; // there's always the trivial one: 1 + 1 + ... + 1 = n
	for (auto coin : nonsingular)
	{
		if ((int)coin <= n && coin <= upTo)
		{
			// (int)coin last 1's have been turned into one coin!
			ways += magic(n - (int)coin, coin);
		}
		else
		{
			break;
		}
	}

	cache[n][nsWhich[upTo]] = ways;
	return ways;
}

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	initCache();

	int money; // <= 7489 (this is a prime, 33^2 + 80^2, (7489, 5280, 5311))

	while (cin >> money)
	{
		cout << magic(money) << endl;
	}

	return 0;
}
