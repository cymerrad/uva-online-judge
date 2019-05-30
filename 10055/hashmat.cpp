#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	int64_t first, second, value;

	while (cin >> first >> second)
	{
		// printf("Read %d %d; cin %d", first, second, !!cin);
		value = (second - first);
		uint64_t temp = value >> 63; // make a mask of the sign bit
		value ^= temp;							 // toggle the bits if value is negative
		value += temp & 1;					 // add one if value was negative
		cout << value << endl;
	}

	return 0;
}
