#include <iostream>

using namespace std;

/*
 * AFAIremember
 * x(t) = x_0 + x'(0)*t + x''(0)/2 * t^2 = x_0 + v(0)*t + a(0)/2 * t^2
 * where x_0 = 0, a(t) is constant and v(t) is linear, so
 * x(t) = v_0 * t + a_0 * t^2/2
 * v_1, t_1 come from input
 * v_1 = x'(t) = v_0 + a_0 * t => v_0 = v_1 - a_0 * t
 * x(2*t_1) = 2 * v_0 * t_1 + 2 * a_0 * t_1^2
 *          = MATHS
 *          = 2 * v_1 * t_1
 */
int magic(int v, int t)
{
	return 2 * v * t;
}

int main(int argc, char const *argv[])
{
	int v, t;

	while (cin >> v >> t)
	{
		cout << magic(v, t) << endl;
	}

	return 0;
}
