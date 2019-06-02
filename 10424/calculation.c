#include <stdio.h>
#include <math.h>

const short HARD_LIMIT = 25 * 26;
const short LOL_LIMIT = 1001;
const char FIRST = 0;
const char SECOND = 1;
const char lowerA = 'a';
const char upperA = 'A';
const char lowerZ = 'z';
const char upperZ = 'Z';
const char lowerShift = 'a' - 1;
const char upperShift = 'A' - 1;
const char primeMap[] = {0, 1, 2, 3, 11, 5, 13, 7, 17, 19};
const char *fractions[] = {0, "100.00", "50.00", "33.33", "100.00", "20.00", "66.67", "14.29", 0, "100.00", "40.00", "25.00", 0, "16.67", "28.57", "60.00", 0, "12.50", 0, "11.11", 0, "42.86", "50.00", 0, 0, "100.00", "33.33", 0, 0, 0, 0, 0, 0, "75.00", "25.00", "71.43", 0, 0, "22.22", "50.00", 0, 0, 0, 0, 0, 0, 0, 0, 0, "100.00", 0, "37.50", 0, 0, 0, "80.00", 0, "33.33", 0, 0, 0, 0, 0, 0, 0, "83.33", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "57.14", 0, 0, 0, 0, 0, 0, 0, "62.50", 0, 0, 0, 0, 0, "85.71", 0, 0, 0, "55.56", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "87.50", 0, "100.00", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "77.78", 0, 0, 0, 0, 0, 0, 0, 0, 0, "66.67", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "100.00", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "50.00", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "44.44", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "75.00", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "66.67", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "100.00", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "88.89", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "100.00"};

char digitize(short number)
{
	short digit = number % 9;
	if (digit == 0)
		return 9;
	return digit;
}

void summary(short *scores)
{
	scores[FIRST] = digitize(*scores);
	scores[SECOND] = digitize(*(scores + 1));

	printf(fractions[primeMap[scores[FIRST]] * primeMap[scores[SECOND]]]);
	printf(" %%\n");

	scores[FIRST] = 0;
	scores[SECOND] = 0;
}

int main(int argc, char const *argv[])
{
	char c;
	char nowCounting = 0;			/* 0 -> 1st, 1 -> 2nd */
	short scores[2] = {0, 0}; /* 26 * 26 < 2^16 */
	while ((c = getchar()) != EOF)
	{
		switch (c)
		{
		case EOF:
			/* end of input might happen without '\n' beforehand */
			summary(scores);
			break;

		case '\n': /* next name */
			nowCounting ^= 1;
			if (nowCounting == FIRST)
			{
				/* we've came back to the first name, so it's time for a summary */
				summary(scores);
			}
			break;

		default:

			if (lowerA <= c && c <= lowerZ)
			{
				scores[nowCounting] += (short)(c - lowerShift);
			}
			else if (upperA <= c && c <= upperZ)
			{
				scores[nowCounting] += (short)(c - upperShift);
			}
			else
			{
				/* ignore */
			}

			break;
		}
	}

	if (nowCounting == SECOND)
	{
		summary(scores);
	}

	return 0;
}
