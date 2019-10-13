#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int printCards(int n)
{
	// throw away top
	// move second to the bottom
	// until there is only 1 left

	int totalIterations = log2(n);
	for (int i = 0; i < totalIterations; i++)
	{
	}
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
		std::cerr << e.what() << std::endl;
		cin.close();
		return 1;
	}
#endif
	int numOfCases;
	cin >> numOfCases;

	// code your solution

	return 0;
}
