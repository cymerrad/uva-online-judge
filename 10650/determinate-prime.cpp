#include <iostream>

using namespace std;

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
		std::cerr << e.what() << '
';
		cin.close();
		return 1;
	}
#endif
    int numOfCases;
    cin >> numOfCases;

    // code your solution

	return 0;
}