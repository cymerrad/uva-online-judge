#include <iostream>

using namespace std;

// NOTE TO SELF
// compare this file to previous version
// and try to figure out why this program
// completes the task in 0 seconds
// and the other exceeds the time limit

/*
 * P = a*1 + b*2 + c*4 + d*8 + ...
 * B^P = (B)^a * (B^2)^b * (B^4)^c + ...
 */
int powerMod(int B, int P, int M)
{
	int R = 1;						 // B^0
	int B_squares = B % M; // < 2^16
	int bit = 1;
	for (int i = 0; i < 31; i++)
	{
		if (bit & P)
		{
			R *= B_squares; // < 2^16 * 2^16
			R %= M;					// < 2^16
		}

		B_squares = (B_squares * B_squares) % M; // < 2^16
		bit = bit << 1;
	}

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
