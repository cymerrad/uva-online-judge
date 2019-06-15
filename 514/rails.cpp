#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
using namespace std;

// #define DEBUG

const char *ACCEPTED = "Yes\n";
const char *REJECTED = "No\n";

const char *determineIfPossible(const vector<int> &perm, const int n)
{
	stack<int> s;
	int aligned = 0;
	int next = 1; // we always start with sorted elements
	int want = perm[aligned];
	while (aligned < n)
	{
		// there is not much of a choice in reordering the cars
		// we'll try to just get all the cars in order
		// we deduce failure by either:
		// - top of the stack doesn't contain the integer we need
		// - the integer we need is not on the right (is somewhere deep into the stack)
		while (s.empty() || (next <= n && s.top() != want))
		{
			s.push(next);
			next++;
		}

		// if we break out, then either we've run out of elements on the right
		// or the top element of the stack is the the element we need
		// either way: if the top element isn't the one we need, we break and reject the scenario
		if (s.top() == want)
		{
			// good
			s.pop();
			aligned++;
			want = perm[aligned];
		}
		else
		{
			// bad
			return REJECTED;
		}
	}

	return ACCEPTED;
}

bool checkValidBeginning(int a, int b, int c)
{
	// negative examples:
	// 3 1 4
	// 4 2 5
	// 5 3 7
	if ((a - b) > 1)
	{
		// we've descended steeply (> 1) right at the beginning
		if (c > a)
		{
			// and we definitely miss some numbers along the way
			return false;
		}
	}
	return true;
}

const char *determineIfPossibleHeuristic(const vector<int> &perm, const int n)
{
	if (n < 2)
	{
		return ACCEPTED;
	}

	if (!checkValidBeginning(perm[0], perm[1], perm[2]))
	{
		return REJECTED;
	}

	int next;
	int prev = perm[0];
	int maxEncountered = prev;
	bool increasing = true;
	for (int i = 1; i < n; i++)
	{
		next = perm[i];
		// as long as we encounter bigger and bigger values, then it's cool
		// the moment we drop for the first time, we better only DECREASE
		// until we find another new maximum
		if (next > maxEncountered)
		{
			maxEncountered = next;
			increasing = true;
		}
		else
		{
			if (increasing)
			{
				// first drop since reaching maximum
				increasing = false;
			}
			else
			{
				// k-th time we've done that
				if (next < prev)
				{
					// cool
				}
				else
				{
					return REJECTED;
				}
			}
		}

		prev = next;
	}

	return ACCEPTED;
}

int main(int argc, char const *argv[])
{
#ifdef DEBUG
	ifstream cin;
	try
	{
		cin.open("input.txt");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		cin.close();
		return 1;
	}
#endif

	int trainLength;
	int firstCoach;
	vector<int> permutation;

	while (cin >> trainLength, trainLength > 0)
	{
		// always extend?
		permutation.resize(max((int)permutation.size(), trainLength));

		while (cin >> firstCoach, firstCoach > 0)
		{
			permutation[0] = firstCoach;
			for (int i = 1; i < trainLength; i++) // one less, because we have 'firstCoach'
			{
				cin >> permutation[i];
			}
			cout << determineIfPossibleHeuristic(permutation, trainLength);
		}
		cout << endl;
	}

	return 0;
}
