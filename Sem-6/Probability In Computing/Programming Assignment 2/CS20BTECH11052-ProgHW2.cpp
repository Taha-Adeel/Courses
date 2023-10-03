#include <fstream>
#include <vector>

struct Clause{
	std::vector<std::pair<int, bool>> literals;
	bool is_satisfied(std::vector<bool>& assignment){
		for(auto& [xi, sign]: literals)
			if(assignment[xi] == sign) return true;
		return false;
	}
};

std::vector<bool> random_walk_sat(std::vector<Clause>& clauses, int n, int m){
	// Randomly assign values to the variables
	std::vector<bool> assignment(n+1);
	for(int i = 1; i <= n; i++) assignment[i] = rand() % 2;

	bool satisfied = false;
	while(!satisfied){
		// Find a clause that is not satisfied
		for(auto& clause: clauses) if(!clause.is_satisfied(assignment)){
			auto& [xi, sign] = clause.literals[rand() % 2]; // Pick a random literal from the clause
			assignment[xi] = !assignment[xi]; // Flip the value of the literal
			break;
		}

		// Check if the assignment satisfies all the clauses
		satisfied = true;
		for(auto& clause: clauses) satisfied &= clause.is_satisfied(assignment);
	}
	
	return assignment;
}

int main(){
	srand(time(0));
	std::ifstream input_file("2-SAT-instances/2-SAT-input5.txt");
	int n, m; input_file >> n >> m; // Read n, the number of variables, and m, the number of clauses

	// Read the clauses 
	std::vector<Clause> clauses(m);
	for(int i = 0; i < m; i++){
		int xi, xj; char comma; input_file >> xi >> comma >> xj;
		bool signi = xi > 0, signj = xj > 0;
		xi = abs(xi); xj = abs(xj);
		clauses[i].literals.push_back({xi, signi});
		clauses[i].literals.push_back({xj, signj});
	}

	// Run the algorithm
	std::vector<bool> satisfying_assignment = random_walk_sat(clauses, n, m);

	// Output the result
	std::ofstream output_file("2-SAT-instances/2-SAT-output5-CS20BTECH11052.txt");
	for(int i = 1; i <= n; i++) 
		output_file << satisfying_assignment[i];

	return 0;
}