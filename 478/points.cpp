#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <type_traits>
#include <list>
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

template <typename T>
struct Point2D
{
	T x, y;
};

using Point = Point2D<double>;

// template <
// 		int Dim,
// 		typename T,
// 		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
// class TrueVector
// {
// private:
// 	vector<T> data;

// public:
// 	TrueVector()
// 	{
// 		data = vector<T>(Dim);
// 	}
// 	TrueVector(const vector<T> &data) : data(data){};
// 	TrueVector(initializer_list<T> data) : data(data){};

// 	TrueVector<Dim, T>
// 	operator+(TrueVector<Dim, T> &vec)
// 	{
// 		TrueVector<Dim, T> temp;
// 		for (int i = 0; i < Dim; i++)
// 		{
// 			temp.data[i] = this->data[i] + vec.data[i];
// 		}
// 		return temp;
// 	}

// 	T operator*(TrueVector<Dim, T> &vec)
// 	{
// 		T temp{0};
// 		for (int i = 0; i < Dim; i++)
// 		{
// 			temp += (this->data[i] * vec.data[i]);
// 		}
// 		return temp;
// 	}
// };

// template <int Dim, typename T>
// ostream &operator<<(ostream &output, const TrueVector<Dim, T> &vec)
// {
// 	output << '(';
// 	for (int i = 0; i < Dim - 1; i++)
// 	{
// 		output << vec[i] << ", ";
// 	}
// 	output << vec[Dim - 1] << ')';

// 	return output;
// }

template <
		typename T,
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vector2D
{
private:
	typedef Vector2D<T, T> _vec2D;

public:
	T x, y;
	Vector2D() : x{0}, y{0} {};
	Vector2D(const T x, const T y) : x{x}, y{y} {};
	Vector2D(const Point2D<T> &begin, const Point2D<T> &end) : x{end.x - begin.x}, y{end.y - begin.y} {};

	_vec2D
	operator+(const _vec2D &vec) const
	{
		return Vector2D(this->x + vec.x, this->y + vec.y);
	}

	T operator*(const _vec2D &vec) const
	{
		return this->x * vec.x + this->y * vec.y;
	}

	static T cross_product(const _vec2D &vec1, const _vec2D &vec2)
	{
		return vec1.x * vec2.y - vec1.y * vec2.x;
	}
};

template <typename T>
ostream &operator<<(ostream &output, const Vector2D<T, T> &vec)
{
	output << '(' << vec.x << ',' << vec.y << ')';

	return output;
}

class Shape
{
public:
	const int id;
	Shape(const int id) : id(id){};
	virtual ~Shape() = default;
	virtual bool doesContain(const Point &p) const = 0;
};

class Rectangle : public Shape
{
public:
	const Point ul;
	const Point lr;
	Rectangle(int id, Point ul, Point lr) : Shape{id}, ul{ul}, lr{lr} {}
	bool doesContain(const Point &p) const
	{
		if (this->ul.x < p.x && p.x < this->lr.x)
			if (this->lr.y < p.y && p.y < this->ul.y)
				return true;
		return false;
	};
};

class Circle : public Shape
{
private:
	const double r_squared;

public:
	const Point c;
	const double r;
	Circle(int id, Point c, double r) : Shape{id}, c{c}, r{r}, r_squared{pow(r, 2)} {}
	bool doesContain(const Point &p) const
	{

		if (pow(c.x - p.x, 2) + pow(c.y - p.y, 2) < r_squared)
			return true;
		return false;
	};
};

class Triangle : public Shape
{
private:
	const Vector2D<double> s1, s2, s3; // sides of the triangle vectorized
	const list<pair<Point, Vector2D<double>>> paired;

public:
	const Point p1, p2, p3;
	Triangle(int id, Point p1, Point p2, Point p3) : Shape{id},
																									 p1{p1},
																									 p2{p2},
																									 p3{p3},
																									 s1{p1, p2},
																									 s2{p2, p3},
																									 s3{p3, p1},
																									 paired{{p1, s1}, {p2, s2}, {p3, s3}} {}
	bool doesContain(const Point &p) const
	{
		int sign = 0;
		for (auto pointEdge : paired)
		{
			const Vector2D<double> pointVec(pointEdge.first, p);
			double product = Vector2D<double>::cross_product(pointEdge.second, pointVec);
			if (product < 0)
			{
				sign--;
			}
			if (product > 0)
			{
				sign++;
			}

			// if 0 do nothing, this means that point lies on the edge
			// so it isn't contained "inside" (per the specification)
		}

		if (sign == 3 || sign == -3)
			return true;

		return false;
	};
};

void calculateStuff(const vector<Shape *> &shapes, const vector<Point> &points)
{
	int p_ind = 1;
	for (const auto &p : points)
	{
		int incl = 0;
		for (auto sh : shapes)
		{
			if (sh->doesContain(p))
			{
				printf("Point %d is contained in figure %d\n", p_ind, sh->id);
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
	vector<Shape *> shapes; // <= 10
	vector<Point> points;
	int id = 0;
	double t1, t2, t3, t4, t5, t6;
	while (cin >> type, cin)
	{
		id++;
		switch (type)
		{
		case 'r':
		{
			cin >> t1;
			cin >> t2;
			cin >> t3;
			cin >> t4;
			Rectangle *rect = new Rectangle{id, {t1, t2}, {t3, t4}};

			shapes.push_back(rect);
			continue;
		}
		case 'c':
		{
			cin >> t1;
			cin >> t2;
			cin >> t3;
			Circle *circ = new Circle{id, {t1, t2}, t3};
			shapes.push_back(circ);
			continue;
		}

		case 't':
		{
			cin >> t1;
			cin >> t2;
			cin >> t3;
			cin >> t4;
			cin >> t5;
			cin >> t6;
			Triangle *trian = new Triangle{id, {t1, t2}, {t3, t4}, {t5, t6}};
			shapes.push_back(trian);
			continue;
		}

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

	calculateStuff(shapes, points);

	return 0;
}
