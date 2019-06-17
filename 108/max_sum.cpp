#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <string>
#include <fstream>
#include <tuple>

// #define DEBUG

using namespace std;

template <typename T>
using Grid = vector<vector<T>>;

const int MAX_N = 100;

template <typename T>
void print2D(const Grid<T> &array, const int N, const int M)
{
	bool negatives;
	int padding = 0;
	int digits;
	for (const vector<int> &cols : array)
	{
		for (const int el : cols)
		{
			if (el < 0)
				negatives = true;

			digits = floor(log10(el)) + 1;
			padding = max(padding, digits);
		}
	}
	padding = negatives ? padding + 1 : padding;
	char outputFormat[15];
	sprintf(outputFormat, "%%%dd ", padding);

	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < M; col++)
		{
			printf(outputFormat, array[row][col]);
		}
		cout << endl;
	}
}

Grid<int> calculatePiecewiseSums(const Grid<int> &array, const int N)
{
	Grid<int> rsums(N, vector<int>(N));
	int partial;

	rsums[0][0] = array[0][0];
	for (int col = 1; col < N; col++)
	{
		rsums[0][col] = array[0][col] + rsums[0][col - 1];
	}

	for (int row = 1; row < N; row++)
	{
		rsums[row][0] = array[row][0] + rsums[row - 1][0];
	}

	for (int row = 1; row < N; row++)
	{
		for (int col = 1; col < N; col++)
		{
			partial = rsums[row - 1][col] + rsums[row][col - 1] - rsums[row - 1][col - 1];
			rsums[row][col] = array[row][col] + partial;
		}
	}

	return rsums;
}
/**
 * ul - up left
 * dr - down right (corners)
 */
int calculateSumInRectangle(const Grid<int> &pSums, const int ul_row, const int ul_col, const int dr_row, const int dr_col)
{
	int total = pSums.at(dr_row).at(dr_col);
	int subtractions = 0;
	if (ul_col > 0)
	{
		total -= pSums.at(dr_row).at(ul_col - 1);
		subtractions++;
	}
	if (ul_row > 0)
	{
		total -= pSums.at(ul_row - 1).at(dr_col);
		subtractions++;
	}
	if (subtractions == 2)
	{
		// subtracted twice the intersection
		total += pSums.at(ul_row - 1).at(ul_col - 1);
	}

	return total;
}

using Corner = struct
{
	int row, col;
};

using BestInRect = struct
{
	Corner ulCorner, drCorner;
	int sum;
};

using BestInRow = struct
{
	int colStart, colEnd, sum;
};

tuple<int, int, int> maxSubarray(const vector<int> &array, const int N)
{
	int largestEndingHere = 0;
	int bestStart, thisStart, end, bestSoFar;
	bestStart = thisStart = end = bestSoFar = 0;
	int maxEl = INT32_MIN;
	int maxElInd;
	for (int i = 0; i < N; i++)
	{
		maxEl = max(maxEl, array[i]);
		if (maxEl == array[i])
		{
			maxElInd = i;
		}
		largestEndingHere += array[i];
		bestSoFar = max(bestSoFar, largestEndingHere);
		if (largestEndingHere <= 0)
		{
			thisStart = i + 1;
			largestEndingHere = 0;
		}
		else if (largestEndingHere == bestSoFar)
		{
			bestStart = thisStart;
			end = i + 1;
		}
	}

	if (bestStart == 0 & end == 0)
	{
		// everything was nonpositive
		return {maxEl, maxElInd, maxElInd + 1};
	}

	return {bestSoFar, bestStart, end};
}

int findMaxSum(const Grid<int> &array, const int N)
{
	Grid<int> sums = calculatePiecewiseSums(array, N);
	// print2D(sums, N, N);
	// Grid<BestInRow> bests(N, vector<BestInRow>(N));
	BestInRow bestInRow = {0, 0, INT32_MIN};
	vector<int> row(N);

	for (int rowHeight = 0; rowHeight < N; rowHeight++)
	{
		for (int rowStart = 0; rowStart < N - rowHeight; rowStart++)
		{
			int sum;
			for (int col = 0; col < N; col++)
			{
				row[col] = calculateSumInRectangle(sums, rowStart, col, rowStart + rowHeight, col);
			}
			tuple<int, int, int> res = maxSubarray(row, N);

			// bests[rowStart][rowStart + rowHeight] =
			if (get<0>(res) > bestInRow.sum)
			{
				bestInRow = {get<1>(res), get<2>(res), get<0>(res)};
			}
		}
	}

	return bestInRow.sum;
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
		std::cerr << e.what() << '\n';
		cin.close();
		return 1;
	}
#endif

	ios_base::sync_with_stdio(true);
	int N;

	while (cin >> N, cin)
	{
		Grid<int> array(N, vector<int>(N));
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> array[i][j];
			}
		}

		cout << findMaxSum(array, N) << endl;
	}
	return 0;
}
