#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <queue>

using namespace std;

using Color = char;

using Node = tuple<Color, bool, pair<int, int>>;

// what is that objective-programming you say?

const auto get_col = [](Node &n) -> Color & { return get<0>(n); };
const auto get_visited = [](Node &n) -> bool & { return get<1>(n); };
const auto get_x = [](Node &n) -> int & { return get<0>(get<2>(n)); };
const auto get_y = [](Node &n) -> int & { return get<1>(get<2>(n)); };

const int MAX_N = 100;

Node grid[MAX_N][MAX_N];

void zeroGrid(const int size, const Color color)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            grid[i][j] = {color, false, {i, j}};
        }
    }
}

const char *ACCEPTED = "good\n";
const char *REJECTED = "wrong\n";

using Samples = vector<Node>;

vector<Node *> getNeighboring(const int x, const int y, const int N)
{
    vector<Node *> result;
    if (x > 0)
    {
        result.push_back(&grid[x - 1][y]);
    }

    if (x < N - 1)
    {
        result.push_back(&grid[x + 1][y]);
    }

    if (y > 0)
    {
        result.push_back(&grid[x][y - 1]);
    }

    if (y < N - 1)
    {
        result.push_back(&grid[x][y + 1]);
    }
    return result;
}

/**
 *
 */
const char *isEquidivisible(const int N, const Samples &samples)
{
    if (samples.size() != N)
    {
        return REJECTED;
    }

    Color current_color;
    queue<Node *> nodes;
    for (auto s_triple : samples)
    {
        current_color = get_col(s_triple);
        Node *cur = &grid[get_x(s_triple)][get_y(s_triple)];
        nodes.push(cur);
        int found = 0;
        while (!nodes.empty())
        {
            cur = nodes.front();
            nodes.pop();
            get_visited(*cur) = true; // visited
            found++;

            auto neighbors = getNeighboring(get_x(*cur), get_y(*cur), N);
            for (auto n : neighbors)
            {
                if (get_col(*n) == current_color && get_visited(*n) == false)
                {
                    // same color and not yet visited
                    nodes.push(n);
                }
            }
        }

        if (found != N)
        {
            return REJECTED;
        }
    }

    return ACCEPTED;
}

int main(int argc, char const *argv[])
{
    int N;
    int x, y;
    string s;
    // #include "../vsdebug.cpp"
    while (cin >> N, N > 0)
    {
        getline(cin, s); // read to the next new line

        zeroGrid(N, N);
        Samples samples;

        // mind the "< N" => coordinates omitted will have color N
        for (Color color = 1; color < N; color++)
        {
            getline(cin, s);
            istringstream iss(s);
            while (iss >> x >> y)
            {
                grid[x - 1][y - 1] = {color, false, {x - 1, y - 1}};
            }
            samples.push_back({color, false, {x - 1, y - 1}});
        }

        // find an example of a tile colored with N
        int i, j, t;
        for (i = j = t = 0; i < N && j < N; j++, t = j / N, i += t, j %= N)
        {
            if (get_col(grid[i][j]) == Color(N))
            {
                samples.push_back(grid[i][j]);
                break;
            }
        }

        cout << isEquidivisible(N, samples);
    }

    return 0;
}