#include <iostream>
#include <math.h>
#include <functional>
#include <map>
using namespace std;

// using Checker = unary_function<int, bool>;
using Checker = function<bool(const int)>;

// we are generating this:
// n*((k-1)/k)^k - k*(1 - ((k-1)/k)^(k+1)) + 1 mod k
// https://www.wolframalpha.com/input/?i=n*((k-1)%2Fk)%5Ek+-+k*(1+-+((k-1)%2Fk)%5E(k%2B1))+%2B+1+mod+k
Checker generateCheckModK(const int k)
{
	const long leftSideNum = pow((k - 1), k);
	const long rightSideNum = pow(k, k + 1) - pow(k - 1, k + 1) - pow(k, k);
	const long denominator = pow(k, k);

	return [leftSideNum, rightSideNum, denominator, k](int n) -> bool {
		long numerator = n * leftSideNum - rightSideNum;
		if (numerator % denominator)
		{
			return false;
		}
		long division = numerator / denominator; // clear the lobby!
		if (division % k)
		{
			return false;
		}
		return true;
	};
}

int fewPrimes[] = {2, 3, 5, 7, 11, 13};
map<int, int> whichPrime = {{2, 0}, {3, 1}, {5, 2}, {7, 3}, {11, 4}, {13, 5}};

const int CHECKERS_COUNT = 13;
Checker naiveCheckers[CHECKERS_COUNT + 1];

Checker checkers[sizeof(fewPrimes)];
void init()
{
	int i;
	for (int p : fewPrimes)
	{
		i = whichPrime[p];
		checkers[i] = generateCheckModK(p);
	}
	for (int i = 2; i <= CHECKERS_COUNT; i++)
	{
		naiveCheckers[i] = generateCheckModK(i);
	}
}

// int calcumalate(int n)
// {
// 	int maxEncountered = 0;
// 	Checker lambda;
// 	int i;
// 	for (int p : fewPrimes)
// 	{
// 		i = whichPrime[p];
// 		lambda = checkers[i];
// 		if (lambda(n))
// 		{
// 			maxEncountered = p;
// 		}
// 	}

// 	return maxEncountered;
// }

int calcumalate(int n)
{
	int maxEncountered = 0;
	Checker lambda;
	for (int i = 2; i <= CHECKERS_COUNT; i++)
	{
		lambda = naiveCheckers[i];
		if (lambda(n))
		{
			maxEncountered = i;
		}
	}

	return maxEncountered;
}

int main(int argc, char const *argv[])
{
	init();
	int coco, people, i;
	coco = 0;
	const int max_coco = 1073741824;
	while (coco < max_coco)
	{
		people = calcumalate(coco);
		if (people > 0)
		{
			try
			{
				whichPrime.at(people);
			}
			catch (out_of_range)
			{
				// I'm going to print only those remarkable situations
				cout << coco << " coconuts, " << people << " people and 1 monkey" << endl;
			}
		}

		coco++;
	}
	return 0;
}
