#include <iostream>
#include <fstream>
#include <cmath>
#include <list>
#include <numeric>

using namespace std;

// return the last element left
int recThrow(list<int> &cards, int n, bool firstRun = false)
{
	if (n == 1)
	{
		return *cards.begin();
	}

	auto head = cards.begin();
	int throws = n / 2;
	if (n % 2 == 0)
	{
		throws--;
	}
	for (int i = 0; i < throws; i++)
	{
		if (firstRun && i == 0)
		{
		}
		else
		{
			cout << ",";
		}
		auto discard = head;
		advance(head, 2);
		cout << " " << *discard;
		cards.erase(discard);
	}
	if (firstRun && n == 2)
	{
		// I can't believe I'm doing this
		cout << " ";
	}
	else
	{
		cout << ", ";
	}
	cout << *head;
	cards.erase(head);
	if (n % 2 == 1)
	{
		cards.splice(cards.begin(), cards, next(cards.begin()), cards.end());
	}

	n /= 2;
	return recThrow(cards, n);
}

void printCards(int n)
{
	// throw away top
	// move second to the bottom
	// until there is only 1 left
	list<int> cards(n);
	iota(cards.begin(), cards.end(), 1);

	cout << "Discarded cards:";
	int left = recThrow(cards, n, true);
	cout << endl;
	cout << "Remaining card: " << left << endl;
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
		std::cerr << e.what() << std::endl;
		cin.close();
		return 1;
	}
#endif
	int n;
	while (cin >> n, n > 0)
	{
		printCards(n);
	}

	return 0;
}
