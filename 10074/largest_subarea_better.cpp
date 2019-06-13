#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <cassert>

#define DEBUG

using namespace std;

const int MAX_M = 100;
const int MAX_N = 100;
const int BOUNDARY = 2;

enum class Patch : char
{
	Nothing,
	Tree
};

template <typename T>
using Grid = vector<vector<T>>;

using Forest = Grid<Patch>;

// we are going to create F and the helpers only once
Forest F(MAX_M + BOUNDARY, vector<Patch>(MAX_N + BOUNDARY));
Grid<int> heights(MAX_M + BOUNDARY, vector<int>(MAX_N + BOUNDARY));
Grid<int> lefts(MAX_M + BOUNDARY, vector<int>(MAX_N + BOUNDARY));
Grid<int> rights(MAX_M + BOUNDARY, vector<int>(MAX_N + BOUNDARY));

// algorithm used requires boundary of trees
void init()
{
	// WARNING, this assumes:
	// MAX_M == MAX_N
	for (int ind = 0; ind < MAX_M + BOUNDARY; ind++)
	{
		F[ind][0] = Patch::Tree;
		F[ind][MAX_M + 1] = Patch::Tree;
		F[0][ind] = Patch::Tree;
		F[MAX_M + 1][ind] = Patch::Tree;
	}

	for (int col = 0; col < MAX_N + BOUNDARY; col++)
	{
		// 'performStep' pre-calculated on the first row to avoid out of bound error
		lefts[0][col] = 1;
		rights[0][col] = 1;

		// pre-calculated heights
		heights[0][col] = 0;
	}

	for (int row = 0; row < MAX_M + BOUNDARY; row++)
	{
		// overwriting previous step with left and right starting values (it still makes sense)
		lefts[row][0] = 0;
		rights[row][MAX_N + 1] = 0;
	}
}

/**
 * This function adds a virtual barrier for the 'rights' grid and in the forest F.
 *
*/
void initForMN(int M, int N)
{
	// this should be (M + BOUNDARY - 1) for clarity, but meh
	for (int col = 0; col < N + BOUNDARY; col++)
	{
		F[M + 1][col] = Patch::Tree; // adding boundary at the bottom

		// default values for 'rights' and 'lefts':
		rights[0][col] = 1;			// start off with 1's, covering potential 0's
		rights[M + 1][col] = 1; // both at the top and bottom
		lefts[M + 1][col] = 1;

		heights[M + 1][col] = 0;
	}

	for (int row = 0; row < M + BOUNDARY; row++)
	{
		F[row][N + 1] = Patch::Tree; // adding boundary on the right
		rights[row][N + 1] = 0;			 // starting value when counting right -> left
		lefts[row][0] = 0;					 // same, but covers potential 1's
	}

	// almost all 1's at the top of 'lefts' should be untouchable
}

/*
 * lefts -> (c - p)
 * rights -> (p - c)
 * row > 0
 */
void performStepLR(Grid<int> &leftsOrRights, int row, int col, int condAssignment)
{
	if (F[row - 1][col] == Patch::Tree)
	{
		leftsOrRights[row][col] = condAssignment;
	}
	else
	{
		leftsOrRights[row][col] = min(leftsOrRights[row - 1][col], condAssignment);
	}
}

/**
 * row > 0
*/
void performStepH(int row, int col)
{
	if (F[row][col] == Patch::Tree)
	{
		heights[row][col] = 0;
	}
	else
	{
		heights[row][col] = heights[row - 1][col] + 1;
	}
}

int valueCalculation(int row, int col)
{
	return heights[row][col] * (lefts[row][col] + rights[row][col] - 1);
}

#ifdef DEBUG
template <typename T>
void showGrid(Grid<T> &grid, int M, int N)
{
	for (int row = 0; row < M + BOUNDARY; row++)
	{
		for (int col = 0; col < N + BOUNDARY; col++)
		{
			cout << grid[row][col] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void debugSituation(int M, int N)
{
	showGrid(heights, M, N);
	showGrid(lefts, M, N);
	showGrid(rights, M, N);
}
#endif

int calculateLargestPatchOfLand(const int M, const int N)
{
	// N columns > 1
	// M rows > 1
	int pL, pR; // previously encountered trees: from left and from right
	int colRev; // we will perform calculations on columns in both ways in one loop

	// all first rows are precomputed and last ones don't matter
	for (int row = 1; row < M + 1; row++)
	{
		pL = 0;			// there are always previous trees on the boundaries
		pR = N + 1; // and we are resetting this every new row

		for (int col = 0; col < N + BOUNDARY; col++)
		{
			colRev = N + BOUNDARY - col;
			performStepH(row, col);
			performStepLR(lefts, row, col, col - pL);
			performStepLR(rights, row, colRev, pR - colRev);

			if (F[row][col] == Patch::Tree)
			{
				pL = col;
			}

			if (F[row][colRev] == Patch::Tree)
			{
				pR = colRev;
			}
		}
	}

	int curVal, maxVal, maxRow, maxCol;
	maxRow = maxCol = maxVal = 0;
	int height, width, maxProduct; // these will store the max size and their product
	int heightT, widthT;					 // temps
	height = width = maxProduct = 0;

	for (int row = 1; row < M + 1; row++)
	{
		for (int col = 1; col < N + 1; col++)
		{
			curVal = valueCalculation(row, col);
			if (curVal >= maxVal)
			{
				maxVal = curVal;
				maxRow = row;
				maxCol = col;

				heightT = heights[maxRow][maxCol];
				widthT = lefts[maxRow][maxCol] + rights[maxRow][maxCol] - 1; // -1 + -1 +1

				// funny corner-case:
				/* 0 1 0
				 * 0 0 0
				 * 0 0 0 <
				 *   ^   this is where h == 2, l == 2, r == 2
				*/
				// if (lefts[maxRow][maxCol] == rights[maxRow][maxCol])
				// {
				// 	// this if means, that we can expand in both directions
				// 	// and we defnitely should
				// 	widthT = (lefts[maxRow][maxCol] - 1) * 2 + 1;
				// }

				if (heightT * widthT > maxProduct)
				{
					height = heightT; // storing for debugging reasons
					width = widthT;
					maxProduct = height * width;
				}
			}
		}
	}

	// debugSituation(M, N);

	return maxProduct;
}

int main(int argc, char const *argv[])
{
	// std::ios_base::sync_with_stdio(false);

	int M, N; // both <= 100 < 128 (char)
	int temp;

	init();

#ifdef DEBUG
	ifstream cin;
	try
	{
		cin.open("input3.txt");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		cin.close();
		return 1;
	}

	int count = 0;
#endif

	while (cin >> M >> N, cin && M > 0 && N > 0)
	{
		for (int i = 1; i <= M; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> temp;
				F[i][j] = (Patch)temp;
			}
		}

		initForMN(M, N);

		cout << calculateLargestPatchOfLand(M, N) << endl;

#ifdef DEBUG
		count++;
		if (count == 6)
		{
			debugSituation(M, N);
		}
#endif
	}

#ifdef DEBUG
	cin.close();
#endif

	return 0;
}
