#include <iostream>
#include <math.h>
#include <functional>
using namespace std;

// using Checker = unary_function<int, bool>;
using Checker = function<bool(const int)>;

Checker generateCheckModK(const int k)
{
	const long leftSideNum = pow((k - 1), k);
	// const int leftSideDenom = pow(k, k);
	const long rightSideNum = pow(k, k + 1) - pow(k - 1, k + 1) - pow(k, k);
	// const int rightSideDenom = leftSideDenom;
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

int fewPrimes[] = {2, 3, 5, 7};

int calcumalate(int n)
{
	// int upperBound = ceil(sqrt(n));
	// for (int k = 2; k < upperBound; k++)
	// {
	// if (checkSituation(n, k))
	// {
	// }
	// }
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
