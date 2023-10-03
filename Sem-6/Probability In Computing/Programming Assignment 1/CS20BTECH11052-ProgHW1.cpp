#include <iostream>
#include <fstream>
#include <vector>

// Utility functions to perform DSU operations
// Returns the subset u belongs to in the disjoint set
int find(int u, std::vector<int> &parent){
	if(parent[u] == u)
		return u;
	return find(parent[u], parent);
}

// Merges the subsets u and v belong to in the disjoint set
bool merge(int u, int v, std::vector<int> &parent){
	int u_parent = find(u, parent);
	int v_parent = find(v, parent);
	parent[u_parent] = v_parent;

	return u_parent != v_parent; // Returns false if u and v are already in the same subset
}


// Represents an edge in the graph
struct Edge{
	int u, v;
};

// Represents a connected, undirected,sw and unweighted graph
class Graph{
public:
	int num_vertices;
	int num_edges;

	std::vector<Edge> edges;

	// Returns a vector of size num_vertices, where the ith element is 1 if the ith vertex is in set A, and 0 if it is in set B
	std::vector<int> getKargerMinCut(){
		// Create a disjoint set of vertices
		std::vector<int> parent(num_vertices);
		for(int i = 0; i < num_vertices; i++)
			parent[i] = i;

		// Keep contracting edges until there are only 2 vertices left
		int num_vertices_left = num_vertices;
		while(num_vertices_left > 2){
			// Pick a random edge
			int random_edge_index = rand() % edges.size();
			Edge random_edge = edges[random_edge_index];

			// Merge the subsets the edge connects
			if(merge(random_edge.u, random_edge.v, parent))
				num_vertices_left--; // Decrement the number of vertices left if the merge was successful(u, v were not in the same subset)
		}

		// Find the cut, where the ith element is 1 if the ith vertex is in set A, and 0 if it is in set B
		std::vector<int> cut(num_vertices, 0);
		for(int i = 0; i < num_vertices; i++){
			cut[i] = (find(i, parent) == find(0, parent));
		}

		return cut;
	}

	// Returns the size of the cut
	int getCutSize(std::vector<int>& cut){
		int cut_size = 0;
		for(int i = 0; i < num_edges; i++){
			if(cut[edges[i].u] != cut[edges[i].v])
				cut_size++;
		}
		return cut_size;
	}

	// Boost the probability of finding a min cut by running Karger's algorithm multiple times
	std::vector<int> getKargerMinCutBoosted(int num_iterations){
		std::vector<int> min_cut;
		int min_cut_size = num_vertices;

		for(int i = 0; i < num_iterations; i++){
			std::vector<int> cut = getKargerMinCut();
			int cut_size = getCutSize(cut);
			if(cut_size < min_cut_size){
				min_cut = cut;
				min_cut_size = cut_size;
			}
		}

		return min_cut;
	}
};

int main(){
	srand(time(NULL));

	// Read the input graph
	Graph graph;
	std::ifstream input_file("graph1.txt");
	input_file >> graph.num_vertices >> graph.num_edges;
	for(int i = 0; i < graph.num_edges; i++){
		Edge edge;
		input_file >> edge.u >> edge.v; 
		edge.u--; edge.v--; // Convert to 0-based indexing
		graph.edges.push_back(edge);
	}
	
	// Run Karger's algorithm
	int num_iterations = 100;
	std::vector<int> min_cut = graph.getKargerMinCutBoosted(num_iterations);
	int min_cut_size = graph.getCutSize(min_cut);
	std::vector<int> setA, setB;
	for(int i = 0; i < graph.num_vertices; i++){
		if(min_cut[i] == 1)
			setA.push_back(i);
		else
			setB.push_back(i);
	}

	// Print the cut
	std::cout << "Cut: {";
	for(int i = 0; i < setA.size(); i++){
		std::cout << setA[i] + 1;
		if(i != setA.size() - 1)
			std::cout << ", ";
	}
	std::cout << "}, {";
	for(int i = 0; i < setB.size(); i++){
		std::cout << setB[i] + 1;
		if(i != setB.size() - 1)
			std::cout << ", ";
	}
	std::cout << "}. Cut size: " << min_cut_size << std::endl;

	return 0;
}
