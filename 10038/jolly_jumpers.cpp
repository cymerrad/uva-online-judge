#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;
const char *ACCEPTED = "Jolly";
const char *REJECTED = "Not jolly";
const int MAX_INT = 3000;
char checks[MAX_INT] = {0};

const char *validateLine(const string &line)
{
	istringstream iss(line);
	int N, prev, next, diff;
	iss >> N;
	if (N == 0)
		return ACCEPTED;
	if (N == 1)
	{
		return ACCEPTED;
	}

	bool shallBeAccepted = true;
	iss >> prev;

	// each time this function is executed, checks[] are all filled with zeroes
	while (iss >> next)
	{
		diff = abs(next - prev);
		if (diff >= N)
		{
			shallBeAccepted = false;
			break;
		}
		checks[diff - 1] = true;
		prev = next;
	}

	for (int i = 0; i < N - 1; i++)
	{
		if (!checks[i])
			shallBeAccepted = false;
		checks[i] = 0;
	}
	// checks[] are all zeroes now again

	return shallBeAccepted ? ACCEPTED : REJECTED;
}

int main(int argc, char const *argv[])
{
	string line;

	while (getline(cin, line))
	{
		cout << validateLine(line) << endl;
	}

	return 0;
}