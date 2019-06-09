#include <iostream>
#include <string>
using namespace std;

char convertLineToChar(const string &input)
{
	if (input[0] == '_')
	{
		return -1;
	}

	char sum = 0;
	char bit = 1;
	for (int i = 9; i > 1; i--)
	{
		if (input[i] == 'o')
		{
			sum += bit;
		}
		if (input[i] == '.')
		{
			continue;
		}
		bit <<= 1;
	}

	return sum;
}

int main(int argc, char const *argv[])
{
	string line;
	char toPrint;
	getline(cin, line); // discard first

	while (getline(cin, line))
	{
		toPrint = (char)convertLineToChar(line);
		;
		if (toPrint == -1)
		{
			continue;
		}
		cout << toPrint;
	}

	return 0;
}
