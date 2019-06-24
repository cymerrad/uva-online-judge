#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
// #undef DEBUG

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
	int id;
	double ul_x, ul_y, lr_x, lr_y; //upper left, lower right
};

using Circle = struct
{
	int id;
	double x, y, r, r_sq;
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

bool isPointContainedInCircle(const Point &p, const Circle &c)
{
	if (pow(c.x - p.x, 2) + pow(c.y - p.y, 2) < c.r_sq)
		return true;
	return false;
}

void calculateStuff(const vector<Rect> &rectangles, const vector<Circle> &circles, const vector<Point> &points)
{
	int p_ind = 1;
	for (const auto &p : points)
	{
		int incl = 0;
		for (const auto &r : rectangles)
		{
			if (isPointContainedInRect(p, r))
			{
				printf("Point %d is contained in figure %d\n", p_ind, r.id);
				incl++;
			}
		}
		for (const auto &c : circles)
		{
			if (isPointContainedInCircle(p, c))
			{
				printf("Point %d is contained in figure %d\n", p_ind, c.id);
				incl++;
			}
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
	vector<Circle> circles;
	vector<Point> points;
	int id = 0;
	while (cin >> type, cin)
	{
		id++;
		switch (type)
		{
		case 'r':
			/* read in and continue to next */

			Rect rectTemp;
			cin >> rectTemp.ul_x;
			cin >> rectTemp.ul_y;
			cin >> rectTemp.lr_x;
			cin >> rectTemp.lr_y;
			rectTemp.id = id;
			rectangles.push_back(rectTemp);
			continue;

		case 'c':
			Circle circleTemp;
			cin >> circleTemp.x;
			cin >> circleTemp.y;
			cin >> circleTemp.r;
			circleTemp.r_sq = pow(circleTemp.r, 2);
			circleTemp.id = id;
			circles.push_back(circleTemp);
			continue;

		default:
			// unknown or '*'
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

	calculateStuff(rectangles, circles, points);

	return 0;
}
