#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_NODES = 200;
// const int MAX_EDGES = MAX_NODES * MAX_NODES;

enum class Color : char
{
	NONE,
	BLACK,
	WHITE,
};

Color flipColor(Color c) { return c == Color::BLACK ? Color::WHITE : Color::BLACK; }

const char *ACCEPTED = "BICOLORABLE.";
const char *REJECTED = "NOT BICOLORABLE.";

const string debugCase = "3\n"
												 "3\n"
												 "0 1\n"
												 "1 2\n"
												 "2 0\n"
												 "0";

typedef unsigned char Node; // <= 200 < 256

typedef vector<vector<Node>> BiColorGraph;

typedef Color ColorMap[MAX_NODES];

typedef struct
{
	Node target;
	Color c;
} Coloring;
typedef queue<Coloring> ColoringQueue;

/*
 * This function colors the nodes and their children accordingly.
 * If the function finds a collision, false is returned (otherwise true).
 */
bool colorNode(BiColorGraph &graph, ColorMap &colors, ColoringQueue &coloringsQ, const int target, const Color targetColor)
{
	colors[target] = targetColor;
	const Color flipped = flipColor(targetColor);

	for (auto neighbor = graph[target].begin(); neighbor != graph[target].end(); ++neighbor)
	{
		if (colors[*neighbor] == Color::NONE)
		{
			coloringsQ.push({*neighbor, flipped});
		}
		else
		{
			if (colors[*neighbor] == targetColor)
			{
				// collision
				return false;
			}
			// else ignore
		}
	}

	return true;
}

/*
 * Nodes of the same targetColor form a class of equivalence by relation of not being adjacent.
 * I'll choose 0'th node and assign it to black. This choice doesn't matter.
 */
bool isBicolorable(BiColorGraph &graph, ColorMap &colors)
{
	ColoringQueue coloringsQ;
	bool isColorable = true;
	bool success;

	// pick 0'th as black
	Coloring coloring = {0, Color::BLACK};
	coloringsQ.push(coloring);

	while (!coloringsQ.empty())
	{
		coloring = coloringsQ.front();
		success = colorNode(graph, colors, coloringsQ, coloring.target, coloring.c);
		if (!success)
		{
			return false;
		}
		coloringsQ.pop();
	}

	return true;
}

int main(int argc, char const *argv[])
{
	BiColorGraph graph(MAX_NODES);
	ColorMap colors = {Color::NONE};

	int N; // nodes < 200
	int l; // edges
	// istringstream cin(anotherDebugCase);
	int v1, v2;
	// graph.resize(N);

	while (cin >> N, cin && N > 0)
	{
		cin >> l;
		for (int edge = 0; edge < l; edge++)
		{
			cin >> v1 >> v2;
			graph[v1].push_back(v2);
			graph[v2].push_back(v1);
		}

		cout << (isBicolorable(graph, colors) ? ACCEPTED : REJECTED) << endl;

		// clean up after yourself
		fill(colors, colors + MAX_NODES, Color::NONE);
		fill(graph.begin(), graph.begin() + N, vector<Node>());
	}

	return 0;
}