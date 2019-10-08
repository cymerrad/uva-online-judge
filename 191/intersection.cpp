#include <iostream>
#include <tuple>
#include <fstream>

using namespace std;

const char *ACCEPTED = "T\n";
const char *REJECTED = "F\n";

/**
 * begin_z <= end_z
 */
// class LineSegment2D
// {
// public:
//     int begin_x, begin_y, end_x, end_y;

//     LineSegment2D(int begin_x, int begin_y, int end_x, int end_y) : begin_x(min(begin_x, end_x)),
//                                                                     end_x(max(begin_x, end_x)),
//                                                                     begin_y(min(begin_y, end_y)),
//                                                                     end_y(max(begin_y, end_y)){};
// };

struct LineSegment2D
{
    int begin_x, begin_y, end_x, end_y;
};

bool checkCrossingSegmentsHH(const LineSegment2D &horizontal1, const LineSegment2D &horizontal2)
{
    if (horizontal1.begin_y != horizontal2.begin_y)
        return false;
    if (horizontal1.begin_x == horizontal2.begin_x)
        return true;
    if (horizontal1.begin_x < horizontal2.begin_x)
    {
        if (horizontal1.end_x >= horizontal2.begin_x)
        {
            return true;
        }
    }
    else
    {
        return checkCrossingSegmentsHH(horizontal2, horizontal1);
    }

    return false;
}

bool checkCrossingSegmentsVV(const LineSegment2D &vertical1, const LineSegment2D &vertical2)
{
    if (vertical1.begin_x != vertical2.begin_x)
        return false;
    if (vertical1.begin_y == vertical2.begin_y)
        return true;
    if (vertical1.begin_y < vertical2.begin_y)
    {
        if (vertical1.end_y >= vertical2.begin_y)
        {
            return true;
        }
    }
    else
    {
        return checkCrossingSegmentsVV(vertical2, vertical1);
    }

    return false;
}

bool checkCrossingSegmentsVH(const LineSegment2D &vertical, const LineSegment2D &horizontal)
{
    if (horizontal.begin_x <= vertical.begin_x && vertical.begin_x <= horizontal.end_x)
    {
        if (vertical.begin_y <= horizontal.begin_y && horizontal.begin_y <= vertical.end_y)
        {
            return true;
        }
    }

    return false;
}

bool fuckIt(const LineSegment2D &segment1, const LineSegment2D &segment2)
{
}

const char *doesIntersect(int xstart, int ystart, int xend, int yend, int xleft, int ytop, int xright, int ybottom)
{
    LineSegment2D horizontal[2] = {
        {xleft, ytop, xright, ytop},
        {xleft, ybottom, xright, ybottom},
    };

    LineSegment2D vertical[2] = {
        {xleft, ytop, xleft, ybottom},
        {xright, ytop, xright, ybottom},
    };

    LineSegment2D crossing{min(xstart, xend), min(ystart, yend), max(xstart, xend), max(ystart, yend)};

    return REJECTED;
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

    int N; // test cases
    cin >> N;

    int xstart, ystart, xend, yend, xleft, ytop, xright, ybottom;
    for (int caseNo = 0; caseNo < N; caseNo++)
    {
        cin >> xstart >> ystart >> xend >> yend >> xleft >> ytop >> xright >> ybottom;
        cout << doesIntersect(xstart, ystart, xend, yend, xleft, ytop, xright, ybottom);
    }

    return 0;
}
