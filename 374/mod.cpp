#include <iostream>

using namespace std;

/*
 * P = a*1 + b*2 + c*4 + d*8 + ...
 * B^P = (B)^a * (B^2)^b * (B^4)^c + ...
 */
int powerMod(int B, int P, int M)
{
	int R = 1;									// B^0
	unsigned B_squares = B % M; // < 2^16
	int highestBit = 31;				// (1 << 31) = 2^31
	unsigned bit = 1 << highestBit;
	while ((bit & P) == 0)
	{
		highestBit--;
		bit = bit >> 1;
	}
	bit = 1;
	for (int i = 0; i < highestBit; i++) // one less, last one will be outside
	{
		if (bit & P)
		{
			R *= B_squares; // < 2^16 * 2^16
			R %= M;					// < 2^16
		}

		bit = bit << 1;
		B_squares *= B_squares; // < 2^32
		B_squares %= M;					// < 2^16
	}

	R *= B_squares;
	R %= M;

	return R;
}

int main(int argc, char const *argv[])
{
	int B, P, M; // B^P mod M; B,P < 2^31; M < 46340 < 2^16

	while (cin >> B >> P >> M)
	{
		cout << powerMod(B, P, M) << endl;
	}
	return 0;
}
