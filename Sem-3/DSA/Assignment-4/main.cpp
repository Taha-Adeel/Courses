#include "graph.h"
#include "minHeap.h"
#include "utility.h"

int Time = 0;

int main(){
	srand(time(0));

	// Generate the population
	Graph population;
	int population_size = 100;
	population.generate_random(population_size);

	// Add all nodes to S
	std::unordered_set<Person*> S, I, R; // Susceptible, Infected, Recovered
	for(auto& person: population.m_vertices)
		S.insert(&person);

	MinHeap events; // Q

	// First infection
	int patient_zero = rand()%population_size;
	events.emplace(MinHeapNode{&(population.m_vertices[patient_zero - 1]), EVENT::INFECTION, 0});

	std::cout << "First person to get infected (patient zero) is " << patient_zero << std::endl;

	// Recovery event for patient zero
	int recovery_time = rand()%4 + 1;
	events.emplace(MinHeapNode{&(population.m_vertices[patient_zero - 1]), EVENT::RECOVERY, recovery_time});

	// Begin the simulation. Each iteration, the events which occur at timeStamp == Time are handeled
	for(; !events.empty(); Time++){	
		// Implementation of the pseudo-code in the question
		for(auto e = events.top(); e.m_timeStamp == Time && !events.empty(); e = events.top()){
			events.pop();

			if(e.m_event == EVENT::RECOVERY){
				e.m_person->m_current_state = STATE::RECOVERED;
				R.insert(e.m_person);
				I.erase(e.m_person);
			}
			else if(e.m_event == EVENT::INFECTION){
				e.m_person->m_current_state = STATE::INFECTED;
				I.insert(e.m_person);
				S.erase(e.m_person);

				for(auto& close_contact: e.m_person->m_close_contacts){
					if(close_contact->m_current_state == STATE::SUSCEPTIBLE && close_contact->m_infection_TimeStamp == -1){
						for(int infection_time = 1; infection_time <= 5; infection_time++){
							int coin_toss = rand()%2;
							if(coin_toss == COIN_TOSS::HEAD){
								// Infection event
								close_contact->m_infected_by = e.m_person->m_node_id;
								events.emplace(MinHeapNode{close_contact, EVENT::INFECTION,
													e.m_person->m_infection_TimeStamp + infection_time});

								// Recovery event
								int recovery_time = rand()%4 + 1;
								events.emplace(MinHeapNode{close_contact, EVENT::RECOVERY,
													close_contact->m_infection_TimeStamp + recovery_time});
								
								break;
							}
						}
					}
				}
			}
		}
		
		// After all the events in that time_step are handeled, output the updated number of individuals in different sets
		if(Time == 0){
			std::cout << "\nThe number of susceptible, infected and recovered individuals, plotted against i (Time interval): " << std::endl;

			print_row_separator(4);
			print_element("       TIME       ");	
			print_element("NO. OF SUSCEPTIBLE");		
			print_element(" NO. OF INFECTED  ");		
			print_element(" NO. OF RECOVERED ");
			end_row();
			print_row_separator(4);
		}
		print_element(Time);    print_element(S.size());    print_element(I.size());	 print_element(R.size());   end_row();
		print_row_separator(4);
	}

	// The nodes' datas after the simulation are shown.
	std::vector<int> shortest_distances(population.get_shortest_distances(patient_zero));
	std::cout << "\nThe instant at which a node gets infected compared with it’s shortest distance from the start node s and other information is as follows:" << std::endl;

	print_row_separator(5);
	print_element("     NODE ID      ");	
	print_element("SHORTEST DISTANCE ");		
	print_element("TIME OF INFECTION ");		
	print_element(" TIME OF RECOVERY ");
	print_element("    INFECTED BY   ");
	end_row();
	print_row_separator(5);

	for(auto& person: population.m_vertices){
		print_element(person.m_node_id);	
		print_element(shortest_distances[person.m_node_id - 1]);		
		print_element(person.m_infection_TimeStamp);		
		print_element(person.m_recovery_TimeStamp);
		print_element(person.m_infected_by);
		end_row();
		print_row_separator(5);
	}

	return 0;
}
