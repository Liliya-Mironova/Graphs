#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
class Vertex {
	int num;
	T property;

	public:
	Vertex();
	Vertex(int, T);
	Vertex(const Vertex<T>&);
	Vertex(Vertex<T>&&);
	~Vertex();

	Vertex<T>& operator=(const Vertex<T>&);
	Vertex<T>& operator=(Vertex<T>&&);

	int get_num() const;
	T get_property() const;
};


template<typename T, typename U>
class Edge {
	int beg, end; // begin vertex, end vertex
	int flag; // there is or no edge with a sign (if oriented)
	U cost; // a characteristic of an edge

	public:
	Edge();
	Edge(Vertex<T>&, Vertex<T>&, int, U);
	Edge(const Edge<T, U>&);
	Edge(Edge<T, U>&&);
	~Edge();

	Edge<T, U>& operator=(const Edge<T, U>&);
	Edge<T, U>& operator=(Edge<T, U>&&);

	int get_beg() const;
	int get_end() const;
	int get_flag() const;
	U get_cost() const;
};


template<typename T, typename U>
class Graph {
	int v_num, e_num; // number of vertexes, number of edges
	std::vector<Edge<T, U>> edges; // vector of edges
	U** adj; // adjacency matrix
	int** inc; // incidence matrix

	public:
	Graph();
	explicit Graph(std::vector<Edge<T, U>>&);
	Graph(const Graph<T, U>&);
	Graph(Graph<T, U>&&);
	~Graph();

	void cleanup();
			
	Graph<T, U>& operator=(const Graph<T, U>&);
	Graph<T, U>& operator=(Graph<T, U>&&);

	void print_graph() const;

	int get_v_num() const;
	int get_e_num() const;
	U** get_adj() const;
	int** get_inc() const;
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

// VERTEX:
// default constructor
template<typename T>
Vertex<T>::Vertex() {
	// ??????
}

template<typename T>
Vertex<T>::Vertex(int num_, T property_) : num(num_), property(property_) {}

// copy constructor
template<typename T>
Vertex<T>::Vertex(const Vertex<T>& other) : num(other.num), property(other.property) {}

// move constructor
template<typename T>
Vertex<T>::Vertex(Vertex<T>&& other) : num(other.num), property(property) {
	other.num = 0; // ?
	other.property = nullptr; // ?
}

template<typename T>
Vertex<T>::~Vertex() {
	// ?
	// ?
}

// copy assignment
template<typename T>
Vertex<T>& Vertex<T>::operator=(const Vertex<T>& other) {
	if (this != &other) {
		num = other.num;
		property = other.property;
	}

	return *this;
}

// move assignment
template<typename T>
Vertex<T>& Vertex<T>::operator=(Vertex<T>&& other) {
	if (this != &other) {
		num = other.num;
		property = other.property;

		other.num = 0;
		other.property = nullptr;
	}

	return *this;
}

// getters
template<typename T>
int Vertex<T>::get_num() const { return num; }

template<typename T>
T Vertex<T>::get_property() const { return property; }

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

// EDGE:
// default constructor
template<typename T, typename U>
Edge<T, U>::Edge() {
	//??????
}

template<typename T, typename U>
Edge<T, U>::Edge(Vertex<T>& beg_, Vertex<T>& end_, int flag_, U cost_) : beg(beg_.get_num()), end(end_.get_num()), flag(flag_), cost(cost_) {}
	
// copy constructor
template<typename T, typename U>
Edge<T, U>::Edge(const Edge<T, U>& other) : beg(other.beg), end(other.end), flag(other.flag), cost(other.cost) {}

// move constructor
template<typename T, typename U>
Edge<T, U>::Edge(Edge<T, U>&& other) : beg(other.beg), end(other.end), flag(other.flag), cost(other.cost) {
	other.beg = 0; // ?
	other.end = 0; // ?
	other.flag = 0; // ?
	other.cost = 0; // ?
}

template<typename T, typename U>
Edge<T, U>::~Edge() {
	beg = 0; // ?
	end = 0; // ?
	flag = 0; // ?
	cost = 0; // ?
}

// copy assignment
template<typename T, typename U>
Edge<T, U>& Edge<T, U>::operator=(const Edge<T, U>& other) {
  	if (this != &other) {
    	beg = other.beg;
   		end = other.end;
   		flag = other.flag;
   		cost = other.cost;
    }

    return *this;
}

// move assignment
template<typename T, typename U>
Edge<T, U>& Edge<T, U>::operator=(Edge<T, U>&& other) {
  	if (this != &other) {
   		beg = other.beg;
   		end = other.end;
   		flag = other.flag;
   		cost = other.cost;

   		other.beg = 0;
		other.end = 0;
		other.flag = 0;
		other.cost = 0;
	}

	return *this;
}	

template<typename T, typename U>
int Edge<T, U>::get_beg() const { return beg; }

template<typename T, typename U>
int Edge<T, U>::get_end() const { return end; }

template<typename T, typename U>
int Edge<T, U>::get_flag() const { return flag; }

template<typename T, typename U>
U Edge<T, U>::get_cost() const { return cost; }

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

//GRAPH:
// default constructor
template<typename T, typename U>
Graph<T, U>::Graph() {
	v_num = 0;
	e_num = 0;
	adj = nullptr;
	inc = nullptr;
}

template<typename T, typename U>
Graph<T, U>::Graph(std::vector<Edge<T, U>>& edges_) : edges(edges_) {

	// count v_num and e_num from edges vector
	int max = 0;
	for (unsigned i = 0; i < edges.size(); i++) {
		if (edges[i].get_beg() > max)
			max = edges[i].get_beg();
		if (edges[i].get_end() > max)
			max = edges[i].get_end();
	}
	v_num = max;
	e_num = edges.size();

	// create adjacency matrix
	adj = new U* [v_num];
	adj[0] = new U [v_num * v_num];
	for (int i = 1; i < v_num; i++)
		adj[i] = adj[i - 1] + v_num;

	for (int i = 0; i < v_num; i++)
		for (int j = 0; j <= i; j++) {
			adj[i][j] = 0;
			adj[j][i] = 0;
		}

	for (unsigned i = 0; i < edges.size(); i++) {
		adj[edges[i].get_beg() - 1][edges[i].get_end() - 1] = edges[i].get_cost();
		adj[edges[i].get_end() - 1][edges[i].get_beg() - 1] = edges[i].get_cost();
	}

	// create incidence matrix
	inc = new int* [e_num];
	inc[0] = new int [e_num * v_num];
	for (int i = 1; i < e_num; i++)
		inc[i] = inc[i - 1] + v_num;

	for (int i = 0; i < e_num; i++)
		for (int j = 0; j < v_num; j++)
			inc[i][j] = 0;

	for (unsigned i = 0; i < edges.size(); i++) {
		inc[i][edges[i].get_beg() - 1] = edges[i].get_flag();
		inc[i][edges[i].get_end() - 1] = -edges[i].get_flag();
	}
}

// copy constructor
template<typename T, typename U>
Graph<T, U>::Graph(const Graph<T, U>& other) : v_num(other.v_num), e_num(other.e_num) {
	
	for (unsigned i = 1; i < edges.size(); i++)
		edges.push_back(edges[i]);

	// adjacency matrix
	adj = new U* [v_num];
	adj[0] = new U [v_num * v_num];
	for (int i = 1; i < v_num; i++)
		adj[i] = adj[i - 1] + v_num;

	for (int i = 0; i < v_num; i++)
		for (int j = 0; j < v_num; j++)
			adj[i][j] = other.adj[i][j];

	// incidence matrix
	inc = new int* [e_num];
	inc[0] = new int [e_num * v_num];
	for (int i = 1; i < e_num; i++)
		inc[i] = inc[i - 1] + v_num;

	for (int i = 0; i < e_num; i++)
		for (int j = 0; j < v_num; j++)
			inc[i][j] = other.inc[i][j];
}

// move constructor
template<typename T, typename U>
Graph<T, U>::Graph(Graph<T, U>&& other) : v_num(other.v_num), e_num(other.e_num), edges(other.edges), adj(other.adj), inc(other.inc) {
	other.v_num = 0;
	other.e_num = 0;
	other.edges = nullptr;
	other.adj = nullptr;
	other.inc = nullptr;
}

template<typename T, typename U>
Graph<T, U>::~Graph() {
	cleanup(); // ?
}

template<typename T, typename U>
void Graph<T, U>::cleanup() {
	edges.clear();

	if (adj)
   		delete[] adj[0];
	delete[] adj;

	if (inc)
   		delete[] inc[0];
	delete[] inc;
}
		
// copy assignment
template<typename T, typename U>	
Graph<T, U>& Graph<T, U>::operator=(const Graph& other) {
	if (this != &other) { // compare ptrs, not objects
   		cleanup();
   		v_num = other.v_num;
   		e_num = other.e_num;

   		for (int i = 1; i < edges.size(); i++)
			edges.push_back(edges[i]);

   		// adjacency matrix
   		adj = new U* [v_num];
		adj[0] = new U [v_num * v_num];
		for (int i = 1; i < v_num; i++)
			adj[i] = adj[i - 1] + v_num;

		for (int i = 0; i < v_num; i++)
			for (int j = 0; j < v_num; j++)
				adj[i][j] = other.adj[i][j];

		// incidence matrix
		inc = new int* [e_num];
		inc[0] = new int [e_num * v_num];
		for (int i = 1; i < e_num; i++)
			inc[i] = inc[i - 1] + v_num;

		for (int i = 0; i < e_num; i++)
			for (int j = 0; j < v_num; j++)
				inc[i][j] = other.inc[i][j];
	}

	return *this;
}

// move assignment
template<typename T, typename U>
Graph<T, U>& Graph<T, U>::operator=(Graph&& other) {
	if (this != &other) { // compare ptrs, not objects
   		cleanup();
   		
  		v_num = other.v_num;
   		e_num = other.e_num;
   		edges = other.edges;

   		other.v_num = 0;
		other.e_num = 0;
		other.edges = nullptr;
		other.adj = nullptr;
		other.inc = nullptr;
	}

	return *this;
}

template<typename T, typename U>
void Graph<T, U>::print_graph() const {
	assert(this);

	cout << "GRAPH:" << endl;
	cout << "v_num = " << v_num << endl;
	cout << "e_num = " << e_num << endl << endl;
	cout << "adjacency matrix:" << endl;
	for (int i = 0; i < v_num; i++) {
		for (int j = 0; j < v_num; j++)
			cout << adj[i][j] << " ";
		cout << endl;
	}
		
	cout << endl << "incidence matrix:" << endl;
	for (int i = 0; i < e_num; i++) {
		cout << edges[i].get_cost() << "  ";
		for (int j = 0; j < v_num; j++)
			cout << inc[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

// getters
template<typename T, typename U>
int Graph<T, U>::get_v_num() const { return v_num; }

template<typename T, typename U>
int Graph<T, U>::get_e_num() const { return e_num; }

template<typename T, typename U>
U** Graph<T, U>::get_adj() const { return adj; }

template<typename T, typename U>
int** Graph<T, U>::get_inc() const { return inc; }

#endif