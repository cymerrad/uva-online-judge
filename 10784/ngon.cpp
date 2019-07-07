#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

template <typename T>
using Polynomial = function<T(const T)>;

const double SQRT_5 = sqrtf64(5);
const double TOLERANCE = 1; // we will be approximating to the next integer
const int MAX_ITERATIONS = 20;

/**
 * Some maths:
 * Shaking hands for n vertices is n(n-1)/2
 * Diagonals is same but with with n less => n(n-3)/2
 *
 * Task:
 * n(n-3)/2 >= N
 * Find minimal n, s.t.
 * n^2 - 3n >= 2N
 *
 *Just calculate a root using a delta...
 */
const long minimalNgonForDiagonals(const long N)
{

    const Polynomial<long> f_val = [N](long x) -> long { return powf64(x, 2) - 3 * x - 2 * N; };

    // polynomial in mind: n^2 -3n - 2N
    long delta_sq_floor = sqrt(9 + 8 * N);
    long positive_root_approx = (3 + delta_sq_floor) / 2;

    long value = f_val(positive_root_approx);
    if (value >= 0)
    {
        return positive_root_approx;
    }
    return positive_root_approx + 1;
}

int main(int argc, char const *argv[])
{
    // #include "../vsdebug.cpp"
    int cs = 1;
    long N;

    while (cin >> N, N > 0)
    {
        cout << "Case " << cs << ": " << minimalNgonForDiagonals(N) << endl;
        cs++;
    }

    return 0;
}

/**
 * We could do few iterations of Newton's method for polynomial n^2 -3n - 2N,
 * find the zero of that and ceil() it.
 */
long whatAmICalculating(const long N)
{
    // this value is kinda close to the zero of n^2 -3n - 2N (at least for big N)
    long x_0 = SQRT_5 * sqrt(N);

    const Polynomial<long> f_val = [N](long x) -> long { return powf64(x, 2) - 3 * x - 2 * N; };
    const Polynomial<long> deriv = [N](long x) -> long { return 2 * x - 3; };

    long y, y_slope;
    long x_1;

    for (int i = 0; i < MAX_ITERATIONS; i++)
    {

        y = f_val(x_0);
        y_slope = deriv(x_0);

        x_1 = x_0 - y / y_slope;

        if (abs(x_1 - x_0) <= TOLERANCE * abs(x_1))
        {
            break;
        }

        x_0 = x_1;
    }

    return ceil(x_1);
}