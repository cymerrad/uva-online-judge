#include <iostream>
#include <math.h>
#include <functional>
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

const int CHECKERS_COUNT = 13;
Checker checkers[CHECKERS_COUNT + 1];
void init()
{
	for (int i = 1; i <= CHECKERS_COUNT; i++)
	{
		checkers[i] = generateCheckModK(i);
	}
}

int calcumalate(int n)
{
	int maxEncountered = 0;
	Checker lambda;
	for (int i = 2; i <= CHECKERS_COUNT; i++)
	{
		lambda = checkers[i];
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
	int coco, people;
	while (cin >> coco, coco > -1)
	{
		people = calcumalate(coco);
		if (people > 0)
		{
			cout << coco << " coconuts, " << people << " people and 1 monkey" << endl;
		}
		else
		{
			cout << coco << " coconuts, no solution" << endl;
		}
	}
	return 0;
}
