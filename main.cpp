#include "graph.hpp"

int main() {
	std::vector<Edge<string, int>> edges;

	Vertex<string> v1(1, "red");
	Vertex<string> v2(2, "orange");
	Vertex<string> v3(3, "yellow");
	Vertex<string> v4(4, "green");
	Vertex<string> v5(5, "blue");
	Vertex<string> v6(6, "purple");

	Edge<string, int> e1(v1, v2, 1, 10);
	Edge<string, int> e2(v1, v3, 1, 12);
	Edge<string, int> e3(v3, v2, -1, 30);
	Edge<string, int> e4(v2, v5, -1, 21);
	Edge<string, int> e5(v3, v5, 1, 19);
	Edge<string, int> e6(v3, v6, -1, 24);
	Edge<string, int> e7(v6, v5, 1, 8);
	Edge<string, int> e8(v4, v5, -1, 17);

	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	edges.push_back(e4);
	edges.push_back(e5);
	edges.push_back(e6);
	edges.push_back(e7);
	edges.push_back(e8);

	Graph<string, int> a(edges);

	a.print_graph();

	edges.clear();

	return 0;
}