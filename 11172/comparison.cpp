#include <iostream>

using namespace std;

template <typename T>
int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

char compare(int left, int right)
{
	switch (sgn(right - left))
	{
	case -1:
		return '>';
	case 0:
		return '=';
	case 1:
		return '<';
	}
}

int main(int argc, char const *argv[])
{
	int N;
	int left, right; // < 1000000001, 30 bits tops

	cin >> N;

	while (cin >> left >> right)
	{
		cout << compare(left, right) << endl;
	}

	return 0;
}