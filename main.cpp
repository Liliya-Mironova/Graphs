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
	a.to_dot();

	edges.clear();

// TEST:
	cout << "TEST of move:" << endl;
	cout << "v2 before move ctor:   " << v2.get_num() << " " << v2.get_property() << endl;
	Vertex<string> v8(std::move(v2));
	cout << "v2 after move ctor:    " << v2.get_num() << " " << v2.get_property() << endl;
	cout << "v8 = move ctor of v1:  " << v8.get_num() << " " << v8.get_property() << endl;

	cout << endl;
	cout << "v4 before move= :      " << v4.get_num() << " " << v4.get_property() << endl;
	Vertex<string> v10 = std::move(v4);
	cout << "v4 after move= :       " << v4.get_num() << " " << v4.get_property() << endl;
	cout << "v10 = move= of v4:     " << v10.get_num() << " " << v10.get_property() << endl;

	return 0;
}
