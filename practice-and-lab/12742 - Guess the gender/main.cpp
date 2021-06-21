#include <iostream>
//#include "function.h"
using namespace std;

class Vertex {
	// class Graph can access the private data of Vertex
	friend class Graph;
private:
	int index;
	Vertex *nextVertex;
public:
	Vertex(int index = 0) {
		this->index = index;
		this->nextVertex = nullptr;
	}
};

/*
 * There are 2 way to save the graph in data structure in general,
 * 1. Adjacency Matrix
 *   Using a 2D array G, G[i][j] = true if (i, j) are connected.
 * 2. Adjancency List
 *   Using N list, where N represent the number of nodes,
 *   G[i] is the ith list and the node in G[i] represent the neighbors of node i
 * Here we are using the second method (Adjancency List), since there are too many edges
 */
class Graph {
private:
	int numberOfVertices;
	Vertex **adjacencyList;
	// Additional property for solving problem
	int *vertexInfo;
public:
	// Default constructor
	Graph() {}
	// TODO: Implement your constructor
	Graph(int n);
	// TODO: Implement function to add edge from source to destination, you can insert Vertex destination at the front of the list of adjacencyList[source]
	void addEdge(int source, int destination);
	// TODO: Implement a depth first search on the graph to solve the problem
	bool dfs(int vertex);
	// TODO: Implement your solver function
	bool solver();
	// TODO: Implement the destructor
	~Graph();
};

Graph::Graph(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            adjacencyList[i][j] = new Vertex();
        }
    }
}

void Graph::addEdge(int source, int destination){

}

bool Graph::dfs(int vertex){

}

bool Graph::solver(){

}

Graph::~Graph(){

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	Graph G(n);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		G.addEdge(x, y);
		G.addEdge(y, x);
	}
	if (G.solver())
		cout << "Possible" << endl;
	else
		cout << "Not Possible" << endl;
	return 0;
}
