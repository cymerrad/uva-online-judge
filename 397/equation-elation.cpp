#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v)
{
	s.put('[');
	char comma[3] = {'\0', ' ', '\0'};
	for (const auto &e : v)
	{
		s << comma << e;
		comma[0] = ',';
	}
	return s << ']';
}

struct op_count
{
	int muls, divs, adds, subs;
};

void doTheWork(list<int> &operands, list<char> &symbols, int size, op_count &opc, string &rhs)
{
	auto firstNum = operands.begin();
	auto lastNum = operands.end();
	if (size < 2)
	{
		cout << *firstNum << " = " << rhs << endl;
		return;
	}

	auto first = symbols.begin();
	auto last = symbols.end();

	auto firstN = operands.begin();
	auto firstS = symbols.begin();
	auto lastS = symbols.end();

	for (; firstS != lastS; ++firstN, ++firstS)
	{
		cout << *firstN << " " << *firstS << " ";
	}
	cout << rhs << endl;

	function<int(int, int)> binOp1, binOp2, binOp;
	char lookingFor1, lookingFor2;
	int *counter1, *counter2;

	if (opc.muls || opc.divs)
	{
		lookingFor1 = '*';
		lookingFor2 = '/';
		binOp1 = [](int a, int b) { return a * b; };
		binOp2 = [](int a, int b) { return a / b; };
		counter1 = &opc.muls;
		counter2 = &opc.divs;
	}
	else
	{
		lookingFor1 = '+';
		lookingFor2 = '-';
		binOp1 = [](int a, int b) { return a + b; };
		binOp2 = [](int a, int b) { return a - b; };
		counter1 = &opc.adds;
		counter2 = &opc.subs;
	}

	for (; first != last; ++first, ++firstNum)
	{
		if (*first == lookingFor1)
		{
			*counter1 = *counter1 - 1;
			binOp = binOp1;
			break;
		}
		if (*first == lookingFor2)
		{
			*counter2 = *counter2 - 1;
			binOp = binOp2;
			break;
		}
	}

	auto secondNum = firstNum;
	++secondNum;

	*secondNum = binOp(*firstNum, *secondNum);

	symbols.erase(first);
	operands.erase(firstNum);

	size--;
	return doTheWork(operands, symbols, size, opc, rhs);
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
	string line;
	char symbol;
	int number;

	bool firstIteration = true;
	while (getline(cin, line))
	{
		if (firstIteration)
		{
			firstIteration = false;
		}
		else
		{
			cout << endl;
		}
		stringstream sstring(line);
		list<int> operands;
		list<char> symbols;
		string rhs;
		op_count opc = {0, 0, 0, 0};

		int n = 0;
		while (sstring >> number >> symbol)
		{
			operands.push_back(number);
			symbols.push_back(symbol);

			n++;
			switch (symbol)
			{
			case '+':
				opc.adds++;
				continue;
			case '-':
				opc.subs++;
				continue;
			case '*':
				opc.muls++;
				continue;
			case '/':
				opc.divs++;
				continue;

			default:
				break;
			}

			break;
		}
		sstring >> rhs;

		doTheWork(operands, symbols, n, opc, rhs);
	}

	return 0;
}
