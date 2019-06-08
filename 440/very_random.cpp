#include <iostream>
#include <vector>
#include <list>
#include <numeric>
using namespace std;

// int next(int i, int m, int n) { return (i + m - 1) % n + 1; }
// int prev(int i, int m, int n) { return (i - m + n - 1) % n + 1; }

/*
 * For the first time ever I really want those arguments to be copied!
 * */
void generateSteps(int n, int m, list<int> stepsLeft, vector<int> &result)
{
	int reachNext;
	int step = 1;
	while (step < n - 1)
	{
		list<int> temp;
		reachNext = (m - 1) % (n - step);
		auto it = stepsLeft.begin();
		advance(it, reachNext);
		result[step] = *it;
		temp.splice(temp.begin(), stepsLeft, stepsLeft.begin(), it);
		temp.splice(temp.begin(), stepsLeft, ++it, stepsLeft.end());
		stepsLeft = temp;

		step++;
	}

	result[step] = stepsLeft.front();
}

int generateVeryRandomNumber(int n)
{
	vector<int> stepsTaken(n);
	iota(stepsTaken.begin(), stepsTaken.end(), 1);
	list<int> consecutiveSteps(++stepsTaken.begin(), stepsTaken.end());
	for (int m = 2; m < 5 * n; m++) // TODO: what is the upper bound?
	{
		generateSteps(n, m, consecutiveSteps, stepsTaken);
		if (stepsTaken[n - 1] == 2)
		{
			return m;
		}
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	int n; // >= 3
	while (cin >> n, n > 2)
	{
		cout << generateVeryRandomNumber(n) << endl;
	}

	return 0;
}
