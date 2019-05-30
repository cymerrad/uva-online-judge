#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
struct Pair
{
	int first;
	int second;
};

map<int, int> cache;
void cacheInit() { cache[1] = 1; }

int collatzStep(int input)
{
	if (input == 1)
		return 1;
	if (input % 2 == 1)
		return 3 * input + 1;
	else
		return input >> 1;
}

/**
 * Calculates Collatz func value using a cache.
 * Observation:
 * when called for start = N, there exist values in cache
 * for all n < N. But it's trivial and not that useful.
 *
 * */
int calculateCycleLength(int start)
{
	int n = start;
	if (n == 1)
		return 1; // trivial
	int steps = 0;
	vector<int> visited;
	auto cacheHit = cache.end();

	while (n != 1)
	{
		// if (debug) printf("Trying %d\n", n);
		cacheHit = cache.find(n);
		if (cacheHit != cache.end())
		{
			steps = steps + cacheHit->second;
			// if (debug) printf("Hit cache: %d -> %d\n", n, cacheHit->second);
			break;
		}
		else
		{
			visited.push_back(n);
			n = collatzStep(n);
			steps++;
		}
	}

	if (n == 1)
		steps++; // last one also counts

	int stepsToCache = cacheHit != cache.end() ? cacheHit->second + 1 : 2;
	// if (debug) printf("Adding %zu entries to cache\n", visited.size());
	for (auto valueToCache = visited.rbegin(); valueToCache != visited.rend();
			 ++valueToCache)
	{
		// if (debug) printf("Update cache: %d -> %d\n", *valueToCache,
		// stepsToCache);
		cache[*valueToCache] = stepsToCache;
		stepsToCache++;
	}
	cache[start] = steps;

	return steps;
}

int calculateMaxCycleLength(int lower, int upper)
{
	int max = 0;
	for (int n = lower; n <= upper; n++)
	{
		int cycleLen = calculateCycleLength(n);
		max = cycleLen > max ? cycleLen : max;
	}

	return max;
}

// void debugCycleLength(int input) {
// 	int cycleLength = calculateCycleLength(input, true);
// 	cout << input << " -> " << cycleLength << endl;
// }

int main(int argc, char const *argv[])
{
	string line;
	vector<Pair> pairs;

	int N, M;
	while (getline(cin, line))
	{
		istringstream lineStream(line);
		lineStream >> N >> M;
		pairs.push_back({N, M});
	}

	cacheInit();

	for (auto i = pairs.begin(); i != pairs.end(); ++i)
	{
		int lower = (*i).first;
		int upper = (*i).second;
		if (lower > upper)
			swap(lower, upper); // IT WASN'T IN THE SPECIFICATION
		int maxLen = calculateMaxCycleLength(lower, upper);
		cout << (*i).first << ' ' << (*i).second << ' ' << maxLen
				 << endl; // preserving order
	}

	// for (auto i = cache.begin(); i != cache.end(); ++i) {
	// 	cout << (*i).first << ' ' << (*i).second << endl;
	// }

	// for (int n = 1; n < 20; n++) {
	// 	debugCycleLength(n);
	// }

	return 0;
}
