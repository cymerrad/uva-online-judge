#include <iostream>
#include <fstream>
#include <string>
// #include <chrono>

using namespace std;

int calcumalateScore(string &line)
{
	int counter = 0;
	int score = 0;
	bool zeroed = false;
	for (auto &&c : line)
	{
		switch (c)
		{
		case 'X':
			if (zeroed)
			{
				score += counter * (counter + 1) / 2;
			}
			zeroed = false;
			counter = 0;
			break;
		case 'O':
			counter++;
			zeroed = true;
			break;
		default:
			break;
		}
	}
	if (zeroed)
	{
		score += counter * (counter + 1) / 2;
	}
	return score;
}

int calcumalateScore2(string &line)
{
	int counter = 0;
	int score = 0;
	for (auto &&c : line)
	{
		switch (c)
		{
		case 'X':
			counter = 0;
			break;
		case 'O':
			counter++;
			score += counter;
			break;
		default:
			break;
		}
	}
	return score;
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
		std::cerr << e.what() << endl;
		cin.close();
		return 1;
	}
#endif
	int numOfCases;
	string line;

	cin >> numOfCases;
	getline(cin, line);
	for (int i = 0; i < numOfCases; i++)
	{
		getline(cin, line);
		cout << calcumalateScore2(line) << endl;
	}

	// while (getline(cin, line))
	// {
	// 	// auto t1 = chrono::high_resolution_clock::now();
	// 	// int s1 = calcumalateScore(line);
	// 	// auto t2 = chrono::high_resolution_clock::now();

	// 	// auto t3 = chrono::high_resolution_clock::now();
	// 	// int s2 = calcumalateScore2(line);
	// 	// auto t4 = chrono::high_resolution_clock::now();

	// 	// auto duration1 = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
	// 	// auto duration2 = chrono::duration_cast<chrono::nanoseconds>(t4 - t3).count();
	// 	// cout << s1 << " " << s2 << " | " << duration1 << " vs " << duration2 << endl;
	// 	cout << calcumalateScore2(line) << endl;
	// }

	return 0;
}
