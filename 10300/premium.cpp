#include <iostream>

using namespace std;

// const string debugCase = "1\n"
// 												 "5\n"
// 												 "51927 56551 48919\n"
// 												 "14433 22446 13324\n"
// 												 "85506 99376 63634\n"
// 												 "93997 63631 83866\n"
// 												 "41720 16645 16267\n";

long maths(long size, long animals, long env)
{
	// (space per animal) * env * animals
	return size * env;
}

int main(int argc, char const *argv[])
{
	int N;														// test cases < 20
	long farmers, size, animals, env; // per case: farmers (0 < f < 20), size of farm, no. of animals, environment friendliness (0 < x < 100_000)
	long totalMONIES;
	// istringstream cin(debugCase);

	cin >> N;

	for (int caseInd = 0; caseInd < N; caseInd++)
	{
		totalMONIES = 0;
		cin >> farmers;
		for (int farmer = 0; farmer < farmers; farmer++)
		{
			cin >> size >> animals >> env;
			totalMONIES += maths(size, animals, env);
		}
		cout << totalMONIES << endl;
	}

	return 0;
}