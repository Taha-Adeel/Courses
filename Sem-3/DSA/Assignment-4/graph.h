#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <queue>

enum class STATE {SUSCEPTIBLE, INFECTED, RECOVERED};
enum class EVENT {INFECTION, RECOVERY};
enum COIN_TOSS {TAIL = 0, HEAD = 1};

// Class storing data about a person. The graph consists of nodes of this type.
class Person{
public:
	int m_node_id;
	STATE m_current_state;
	int m_infection_TimeStamp;
	int m_recovery_TimeStamp;
	int m_infected_by; // node_id of person infected by
	std::vector<Person*> m_close_contacts;

	// Constructor with some default parameters
	Person(int node_id, STATE state = STATE::SUSCEPTIBLE, int infection_timestamp = -1, int recovery_timestamp = -1):
		m_node_id(node_id),
		m_current_state(state),
		m_infection_TimeStamp(infection_timestamp),
		m_recovery_TimeStamp(recovery_timestamp),
		m_infected_by(-1)
	{
	}
};

using Edge = std::pair<const Person*,const Person*>;

class Graph{
public:
	std::vector<Person> m_vertices;
	std::vector<Edge> m_edges; // If the there is an edge between vertice[i] and vertice[j], contains {i,j}, where i<j

	int no_of_vertices(){return m_vertices.size();}
	int no_of_edges(){return m_edges.size();};
	void generate_random(int n);
	std::vector<int> get_shortest_distances(int root);
};

// Generates a random graph with n nodes and random edges between them as in the question.
void Graph::generate_random(int n){
	for(int i = 1; i <= n; ++i){
		m_vertices.emplace_back(Person(i, STATE::SUSCEPTIBLE));
	}

	for(int i = 0; i < no_of_vertices(); ++i){
		for(int j = i + 1; j < no_of_vertices(); ++j){
			int coin_toss = rand() % 2;
			if(coin_toss == COIN_TOSS::HEAD){
				m_edges.push_back({&m_vertices[i], &m_vertices[j]});

				m_vertices[i].m_close_contacts.push_back(&m_vertices[j]);
				m_vertices[j].m_close_contacts.push_back(&m_vertices[i]);
			}
		}
	}
}

// Uses BFS to find the shortest distances of the nodes from the node with id = root_id
std::vector<int> Graph::get_shortest_distances(int root_id){
	std::vector<bool> found(this->no_of_vertices(), false);
	std::vector<int> shortest_distances(this->no_of_vertices(), 99999);

	std::queue<int> nodes_to_visit;

	found[root_id - 1] = true;
	shortest_distances[root_id - 1] = 0;
	nodes_to_visit.push(root_id);

	while(!nodes_to_visit.empty()){
		Person* current_node = &m_vertices[nodes_to_visit.front() - 1];
		for(auto& neighbour: current_node->m_close_contacts){
			if(found[neighbour->m_node_id - 1] == false){
				found[neighbour->m_node_id - 1] = true;
				shortest_distances[neighbour->m_node_id - 1] = shortest_distances[current_node->m_node_id - 1] + 1;
				nodes_to_visit.push(neighbour->m_node_id);
			}
		}
		nodes_to_visit.pop();
	}

	return shortest_distances;
}


#endif