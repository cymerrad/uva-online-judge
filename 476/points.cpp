#include <iostream>
#include <vector>

// #define DEBUG
#include <fstream>

using namespace std;

const double almostThousand = 9999.9;

// I know that double precision approximates, but they all will be the same approximation so it's fine
bool isEnd(double x, double y)
{
	if (x == almostThousand && y == almostThousand)
		return true;
	return false;
}

using Rect = struct
{
	double ul_x, ul_y, lr_x, lr_y; //upper left, lower right
};

using Point = struct
{
	double x, y;
};

bool isPointContainedInRect(const Point &p, const Rect &r)
{
	if (r.ul_x < p.x && p.x < r.lr_x)
		if (r.lr_y < p.y && p.y < r.ul_y)
			return true;
	return false;
}

void calculateStuff(const vector<Rect> &rectangles, const vector<Point> &points)
{
	int p_ind = 1;
	for (const auto &p : points)
	{
		int incl = 0;
		int r_ind = 1;
		for (const auto &r : rectangles)
		{
			if (isPointContainedInRect(p, r))
			{
				printf("Point %d is contained in figure %d\n", p_ind, r_ind);
				incl++;
			}
			r_ind++;
		}
		if (incl == 0)
		{
			printf("Point %d is not contained in any figure\n", p_ind);
		}
		p_ind++;
	}
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

	char type;
	vector<Rect> rectangles; // <= 10
	vector<Point> points;
	while (cin >> type, cin)
	{
		switch (type)
		{
		case 'r':
			/* read in and continue to next */

			Rect rectTemp;
			cin >> rectTemp.ul_x;
			cin >> rectTemp.ul_y;
			cin >> rectTemp.lr_x;
			cin >> rectTemp.lr_y;
			rectangles.push_back(rectTemp);

			continue;

		default:
			/* anything other than 'r' -> break */
			break;
		}
		break;
	}
	while (cin)
	{
		Point pointTemp;
		cin >> pointTemp.x;
		cin >> pointTemp.y;
		if (isEnd(pointTemp.x, pointTemp.y))
		{
			break;
		}
		points.push_back(pointTemp);
	}

	calculateStuff(rectangles, points);

	return 0;
}
