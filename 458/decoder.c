#include <stdio.h>

const int SHIFT = 7;
int main(int argc, char const *argv[])
{
	char c;
	while ((c = getchar()) != EOF)
	{
		switch (c)
		{
		case '\n':
			putchar('\n');
			break;

		default:
			putchar((char)(c - SHIFT));
			break;
		}
	}
	return 0;
}
