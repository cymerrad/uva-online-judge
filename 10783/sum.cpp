#include <iostream>
#include <stdio.h>

using namespace std;

/*
 * Sum of odd integers up to 2*N-1 is just N^2.
 */
int magic(int lo, int hi)
{
	int trueLo = lo & 1 ? lo : lo + 1; // if odd, then it's fine, else next odd number after
	int trueHi = hi & 1 ? hi : hi - 1; // same story, but we go back by one
	int nLo = (trueLo + 1) >> 1;
	nLo--; // I'm going to calculate nHi^2 and then subtract (nLo-1)^2
	int nHi = (trueHi + 1) >> 1;

	return (nHi * nHi) - (nLo * nLo);
}

int main(int argc, char const *argv[])
{
	int N, lo, hi;
	cin >> N; // discard first

	N = 1;
	while (cin >> lo >> hi)
	{
		printf("Case %d: %d\n", N, magic(lo, hi));
		N++;
	}

	return 0;
}