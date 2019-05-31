#include <iostream>

using namespace std;

// fastest sort on three elements is just 3 comparisons
int getMiddleOutOfThree(int fst, int snd, int trd)
{
	if (fst <= snd)
	{
	}
	else
	{
		swap(fst, snd);
	}

	if (snd <= trd)
	{
		// fst <= snd <= trd
		// good
		return snd;
	}
	else
	{
		swap(snd, trd);
	}

	if (fst <= snd)
	{
		// good
		return snd;
	}
	else
	{
		swap(fst, snd);
	}

	return snd;
}

int main(int argc, char const *argv[])
{
	int N;
	int fst, snd, trd;
	int casus = 1;

	cin >> N;

	while (cin >> fst >> snd >> trd)
	{
		printf("Case %d: %d\n", casus, getMiddleOutOfThree(fst, snd, trd));
		casus++;
	}

	return 0;
}