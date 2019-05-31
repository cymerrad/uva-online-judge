#include <stdio.h>

const char leftQuote = (char)96;	// `
const char rightQuote = (char)39; // '

int main(int argc, char const *argv[])
{
	char c;
	bool firstQuote = true;
	while ((c = getchar()) != EOF)
	{
		switch (c)
		{
		case '"':
			if (firstQuote)
			{
				putchar(leftQuote);
				putchar(leftQuote);
			}
			else
			{
				putchar(rightQuote);
				putchar(rightQuote);
			}
			firstQuote = !firstQuote;
			break;
		default:
			putchar(c);
		}
	}
	return 0;
}
