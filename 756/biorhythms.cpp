#include <iostream>

using namespace std;

const int N = 23 * 28 * 33;
const int m33 = 33;
const int m28m23 = 28*23;
const int Nmulm33 = 2;
const int m28 = 28;
const int m33m23 = 33*23;
const int Nmulm28 = 19;
const int m23 = 23;
const int m33m28 = 33*28;
const int Nmulm23 = 6;


// int mulInv(int a, int b) {
// 	int b0 = b;
// 	int x0 = 0;
// 	int x1 = 1;

// 	if (b == 1) {
// 		return 1;
// 	}

// 	while (a > 1) {
// 		int q = a / b;
// 		int amb = a % b;
// 		a = b;
// 		b = amb;

// 		int xqx = x1 - q * x0;
// 		x1 = x0;
// 		x0 = xqx;
// 	}

// 	if (x1 < 0) {
// 		x1 += b0;
// 	}

// 	return x1;
// }

// int Ndm23 = mulInv(N/m23, m23);
// int Ndm28 = mulInv(N/m28, m28);
// int Ndm33 = mulInv(N/m33, m33);

// chinese remainder theorem for three equations
int solution(int start, int c23, int c28, int c33) {
	int sm = 0;
	sm += c23 * Nmulm23 * m33m28;
	sm += c28 * Nmulm28 * m33m23;
	sm += c33 * Nmulm33 * m28m23;

	// int p = N / m23;
	// sm += c23 * mulInv(p, m23)*p;

	// p = N / m28;
	// sm += c28 * mulInv(p, m28)*p;

	// p = N / m33;
	// sm += c33 * mulInv(p, m33)*p;

	int rem =  sm % N;

	if (rem <= start) {
		return N - (start - rem);
	}

	return rem - start;
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
		std::cerr << e.what() << '
';
		cin.close();
		return 1;
	}
#endif
		// printf("%d %d %d\n", Ndm23, Ndm28, Ndm33);
		int instance = 1;
		int p,e,i,d;
		while (cin >> p >> e >> i >> d, p != -1) {
			printf("Case %d: the next triple peak occurs in %d days.\n", instance, solution(d, p, e, i));
			instance ++;
		}

	return 0;
}

/*
nums = set([23, 28, 33])
for i in nums:
     rest = nums.difference({i})
     a,b = rest.pop(), rest.pop()
     result += f"const int m{i} = {i};\nconst int m{a}m{b} = {a}*{b};\nconst int Nmulm{i} = 0;\nsm += c{i} * Nmulm{i} * m{a}m{b};\n"
*/