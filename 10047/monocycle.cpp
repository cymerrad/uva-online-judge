#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <queue>

using namespace std;

const int MAX_SIZE = 25;

const char *ACCEPTED = "Case #%d\nminimum time = %d sec\n\n";
const char *REJECTED = "Case #%d\ndestination not reachable\n\n";

enum class InputSquare : char
{
    Blocked = '#',
    Free = '.',
    Start = 'S',
    Target = 'T',
};

enum class Square : char
{
    Blocked,
    Free,
};

Square grid[MAX_SIZE][MAX_SIZE];

enum class Direction : char
{
    West = 'W',
    East = 'E',
    North = 'N',
    South = 'S',
};

using NodeXY = pair<int, int>;
using Node = tuple<int, Direction, Square, NodeXY>;
using Graph = vector<vector<Node>>;

const auto value = [](Node & n) -> typename tuple_element<0, Node>::type & { return get<0>(n); };
const auto dir = [](Node & n) -> typename tuple_element<1, Node>::type & { return get<1>(n); };
const auto type = [](Node & n) -> typename tuple_element<2, Node>::type & { return get<2>(n); };
const auto coord = [](Node & n) -> typename tuple_element<3, Node>::type & { return get<3>(n); };
const auto relative_dir = [](Node &from, Node &to) -> Direction {
    NodeXY &from_c = coord(from);
    NodeXY &to_c = coord(to);
    if (from_c.first > to_c.first)
        return Direction::North;
    if (from_c.first < to_c.first)
        return Direction::South;
    if (from_c.second > to_c.second)
        return Direction::West;
    // if (from_c.second < to_c.second)
    return Direction::East;
};
const auto dist = [](Node &from, Node &to) -> int {
    Direction heading = relative_dir(from, to);
    if (heading == dir(from))
        return 1;
    return 2;
};

using NodeCheck = pair<Node &, bool>;
const Node _get_neighbour_fail_target{0, Direction::North, Square::Blocked, {0, 0}};

template <int M, int N>
NodeCheck get_neighbour(Graph &g, Node &n, Direction towards)
{
    // FUN FACT: move this to the global scope, if you want to see some fireworks

    const NodeCheck _get_neighbour_fail = {_get_neighbour_fail_target, false};
    switch (towards)
    {
    case Direction::North:
        if (coord(n).first == 0)
            return _get_neighbour_fail;
        return {g.at(coord(n).first - 1).at(coord(n).second), true};

    case Direction::South:
        if (coord(n).first == M - 1)
            return _get_neighbour_fail;
        return {g.at(coord(n).first + 1).at(coord(n).second), true};

    case Direction::East:
        if (coord(n).second == N - 1)
            return _get_neighbour_fail;
        return {g.at(coord(n).first).at(coord(n).second + 1), true};

    case Direction::West:
        if (coord(n).second == 0)
            return _get_neighbour_fail;
        return {g.at(coord(n).first).at(coord(n).second - 1), true};
    }
};

int helpTheCyclist(Graph &graph, NodeXY &start, NodeXY &target)
{
    Node &st = graph[start.first][start.second];
    value(st) = 0;
    dir(st) = Direction::North;

    // cout << dist(graph[1][0], graph[0][0]) << endl;
    // cout << dist(graph[0][0], graph[0][1]) << endl;

    Node &cur, &n;
    NodeCheck n_check;
    queue<Node &> node_q;
    node_q.push(st);
    while (!node_q.empty())
    {
        cur = node_q.front();
        node_q.pop();
        for (Direction d : {{'W', 'E', 'N', 'S'}})
        {
            n_check = get_neighbour(graph, cur, d);
            if (n_check.second)
            {
                // exists
                n = n_check.first;
                if (value(n) == INT32_MAX)
                {
                    // unvisited
                    node_q.push(n);
                }
            }
        }
    }

    return -1;
}

int main(int argc, char const *argv[])
{
    int cs = 1;
    int M, N, time;
    char c;

    NodeXY start, target;
    Square sq;
    Graph graph;

#include "../vsdebug.cpp"
    while (cin >> M >> N, M > 0 && N > 0)
    {

        graph = Graph(M, vector<Node>(N));
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> c;
                switch (InputSquare(c))
                {
                case InputSquare::Free:
                    sq = Square::Free;
                    break;

                case InputSquare::Blocked:
                    sq = Square::Blocked;
                    break;

                case InputSquare::Start:
                    sq = Square::Free;
                    start = {i, j};
                    break;

                case InputSquare::Target:
                    sq = Square::Free;
                    target = {i, j};
                    break;

                default:
                    break;
                }
                graph[i][j] = {
                    INT32_MAX,
                    Direction::North,
                    sq,
                    {i, j},
                };
            }
        }

        time = helpTheCyclist(graph, start, target);
        if (time >= 0)
        {
            printf(ACCEPTED, cs, time);
        }
        else
        {
            printf(REJECTED, cs);
        }
        cs++;
    }

    return 0;
}