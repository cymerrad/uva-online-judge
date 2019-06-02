#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <cassert>

using namespace std;

enum class Patch : char
{
	Nothing,
	Tree
};
using Forest = vector<vector<Patch>>;

// Top left corner of a rectangle block in the forest
using TopLeftCorner = struct
{
	char xx, yy;
};

class DiagonalPairSequence :
		// (implicit aliases)
		public std::iterator<
				std::input_iterator_tag,
				std::pair<int, int>>
{
	// C++03
	// typedef void (DiagonalPairSequence::*BoolLike)();
	// void non_comparable();

public:
	// C++11 (explicit aliases)
	using iterator_category = std::input_iterator_tag;
	using value_type = std::pair<int, int>;
	using reference = value_type const &;
	using pointer = value_type const *;
	using difference_type = ptrdiff_t;

	// C++03 (explicit aliases)
	// typedef std::input_iterator_tag iterator_category;
	// typedef std::pair<int, int> value_type;
	// typedef value_type const &reference;
	// typedef value_type const *pointer;
	// typedef ptrdiff_t difference_type;

	DiagonalPairSequence(const int M, const int N)
			: done(false), M(M), N(N), totalPairs(M * N), pairsGiven(1), directionUp(true), diagonalSum(1), diagonalCur(1), whichDiagonal(1) {}

	// C++11
	explicit operator bool() const { return !done; }

	// C++03
	// Safe Bool idiom
	// operator BoolLike() const
	// {
	// 	return done ? 0 : &DiagonalPairSequence::non_comparable;
	// }

	reference operator*() const { return ij; }
	pointer operator->() const { return &ij; }

	DiagonalPairSequence &operator++()
	{
		// static int const Max = numeric_limits<int>::max();

		assert(!done);

		if (pairsGiven < totalPairs)
		{
			if (diagonalCur < diagonalSum)
			{
				diagonalCur++;

				if (directionUp)
				{
					--ij.first;
					++ij.second;
				}
				else
				{
					++ij.first;
					--ij.second;
				}

				pairsGiven++;
				return *this;
			}
			else
			{
				// whichDiagonal++ -> start from the next edge, change the sum accordingly,
				// zero current location on diagonal, and flip directionUp
				whichDiagonal++;

				if (directionUp)
				{

					ij.first = 0;
					ij.second = min(whichDiagonal, N) - 1; // diagonal to coordinate conversion
					if (whichDiagonal > N)
					{
						// M should be increased by (whichDiagonal - N)
						ij.first += whichDiagonal - N;
					}
				}
				else
				{
					ij.first = min(whichDiagonal, M) - 1;
					ij.second = 0;
					if (whichDiagonal > M)
					{
						// N should be increased by (whichDiagonal - M)
						ij.second += whichDiagonal - M;
					}
				}
				int sumCorrection = 0;
				sumCorrection += whichDiagonal > N ? whichDiagonal - N : 0;
				sumCorrection += whichDiagonal > M ? whichDiagonal - M : 0;
				diagonalSum = whichDiagonal - sumCorrection;
				diagonalCur = 1;

				directionUp = !directionUp;

				pairsGiven++;
				return *this;
			}
		}

		done = true;
		return *this;
	}

	DiagonalPairSequence operator++(int)
	{
		DiagonalPairSequence const tmp(*this);
		++*this;
		return tmp;
	}

private:
	bool done;
	const int M;
	const int N;
	const int totalPairs;

	bool directionUp;
	int pairsGiven;
	int diagonalSum;
	int whichDiagonal;
	int diagonalCur;

	value_type ij;
};

using BlocksData = vector<TopLeftCorner>;

void findBlocksOfSize(Forest &F, BlocksData *grownBlocks, const int M, const int N, const int sM, const int sN, BlocksData *up = NULL, BlocksData *left = NULL)
{

	// we'll try to grow existing blocks only to the right and down

	bool valid;
	int i, j;
	// these we will grow to the bottom
	if (up != NULL)
	{
		for (auto block : *up)
		{

			valid = true;
			i = block.xx + sM - 1;
			if (i >= M)
				continue;

			for (int j = block.yy; j < block.yy + sN; j++)
			{
				if (F[i][j] == Patch::Tree)
				{
					valid = false;
					break;
				}
			}

			if (valid)
			{
				grownBlocks->push_back(block);
			}
		}
	}

	// these we will grow to the right
	if (left != NULL)
	{
		for (auto block : *left)
		{

			valid = true;
			j = block.yy + sN - 1;
			if (j >= N)
				continue;

			for (int i = block.xx; i < block.xx + sM; i++)
			{
				if (F[i][j] == Patch::Tree)
				{
					valid = false;
					break;
				}
			}

			if (valid)
			{
				grownBlocks->push_back(block);
			}
		}
	}

	if (up == NULL && left == NULL)
	{
		// this case happens exactly once, for sM and sN == 1
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (F[i][j] == Patch::Nothing)
				{
					grownBlocks->push_back({(char)i, (char)j});
				}
			}
		}
	}
}

int calculateLargestPatchOfLand(Forest &F, const int M, const int N)
{
	// this represents example rectangles of size m x n (e.g. 2 x 3, 2 rows, 3 columns)
	// and holds information where are they located by remembering top-left corner (+ m x n size is all we need)
	vector<TopLeftCorner> rectanglesOfSize[M][N];

	int maxSize = 0;
	int i, j;
	for (DiagonalPairSequence iter(M, N); iter; ++iter)
	{
		i = iter->first;
		j = iter->second;

		BlocksData *up = i > 0 ? &rectanglesOfSize[i - 1][j] : NULL;
		BlocksData *left = j > 0 ? &rectanglesOfSize[i][j - 1] : NULL;
		if (left != NULL && up != NULL && left->size() == 0 && up->size() == 0)
			continue;
		if (up == NULL xor left == NULL)
		{
			if (up == NULL && left->size() == 0)
				continue;
			if (left == NULL && up->size() == 0)
				continue;
		}

		findBlocksOfSize(F, &rectanglesOfSize[i][j], M, N, i + 1, j + 1, up, left);

		if (rectanglesOfSize[i][j].size() != 0)
		{
			maxSize = max(maxSize, (i + 1) * (j + 1));
		}
	}

	return maxSize;
}

int main(int argc, char const *argv[])
{
	std::ios_base::sync_with_stdio(false);

	int M, N; // both <= 100 < 128 (char)
	Forest F;
	int temp;

	// DEBUG
	// ifstream cin;
	// // try
	// // {
	// // 	cin.open("input.txt");
	// // }
	// // catch (const std::exception &e)
	// // {
	// 	// std::cerr << e.what() << '\n';
	// // cin.close();
	// 	// return 1;
	// }

	while (cin >> M >> N, cin && M > 0 && N > 0)
	{
		F = Forest(M, vector<Patch>(N));
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> temp;
				F[i][j] = (Patch)temp;
			}
		}
		cout << calculateLargestPatchOfLand(F, M, N) << endl;
	}

	// DEBUG
	// cin.close();

	return 0;
}
