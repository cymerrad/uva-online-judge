#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

const char *ACCEPTED_F = "The nicest part of route %d is between stops %d and %d\n";
const char *REJECTED_F = "Route %d has no nice parts\n";

pair<int, int> maxSubarray(const vector<int> &array, const int N)
{
	vector<tuple<int, int, int>> allIntervalsFound(0);

	int largestEndingHere = 0;
	int bestStart, thisStart, end, bestSoFar;
	bestStart = thisStart = end = bestSoFar = 0;
	for (int i = 0; i < N; i++)
	{
		largestEndingHere += array.at(i);
		if (largestEndingHere == bestSoFar)
		{
			// we're going to achieve a highest sum for the second time
			allIntervalsFound.push_back({largestEndingHere, bestStart, end});
		}
		bestSoFar = max(bestSoFar, largestEndingHere);
		if (largestEndingHere < 0)
		{
			thisStart = i + 1;
			largestEndingHere = 0;
		}
		else if (largestEndingHere == bestSoFar)
		{
			bestStart = thisStart;
			end = i + 1;
		}
	}

	// last one achieved is going to compete with all the other found
	allIntervalsFound.push_back({bestSoFar, bestStart, end});

	int longestInterval = 0;
	tuple<int, int, int> better;
	for (auto tr : allIntervalsFound)
	{
		if (get<0>(tr) == bestSoFar)
		{
			if (get<2>(tr) - get<1>(tr) > longestInterval)
			{
				longestInterval = get<2>(tr) - get<1>(tr);
				better = tr;
			}
		}
	}

	return {get<1>(better), get<2>(better)};
}

int main(int argc, char const *argv[])
{
	int N, S; // number of cases, number of route S in each
	cin >> N;
	int caseNumber = 1;
	while (cin >> S, cin && S > 1)
	{
		vector<int> segments(S - 1, 0);
		for (int i = 0; i < S - 1; i++)
		{
			cin >> segments[i];
		}
		auto result = maxSubarray(segments, S - 1);
		if (result.first == 0 && result.second == 0)
		{
			printf(REJECTED_F, caseNumber);
		}
		else
		{
			printf(ACCEPTED_F, caseNumber, result.first + 1, result.second + 1);
		}

		caseNumber++;
	}

	return 0;
}
