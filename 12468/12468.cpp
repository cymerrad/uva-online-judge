#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int from, to;
	while (cin >> from, cin >> to, from > -1 && to > -1)
	{
		// int presses = min(abs(from - to), min(((from + to) % 99) + 1, 99 - ((from + to) % 99)));
		int presses = min(abs(from - to), min(99 - from + to, 99 - to + from) + 1);
		cout << presses << endl;
	}

	return 0;
}
