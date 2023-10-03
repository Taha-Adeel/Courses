#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <random>
#include <semaphore.h>
#include <atomic>

int nw, nr;										// The number of writer and reader threads respectively
int kw, kr; 									// Number of times the critical section is executed per writer and reader thread respectively
int mu_cs, mu_rem;								// The average value of simulation time of critical section and remainder section respectively in milliseconds
std::ifstream input_file("inp-params.txt");		// The input file
std::ofstream log_file("FRW-log.txt");			// The output file where the logs are stored
std::ofstream stats_file("FRW-Average_time.txt");		// The output file where the waiting time stats are stored
std::vector<double> avg_waiting_t_w, avg_waiting_t_r;		// Vector holding the average waiting times of the different threads
std::vector<double> worst_waiting_t_w, worst_waiting_t_r;	// Vector holding the worst case waiting times of the threads


sem_t rw_mutex, queue;				// The semaphore to ensure writersand readers are mutually exculsive and ensure fair priorities
sem_t read_counter_lock;			// Semaphore to ensure read_count is used atomically
int read_count = 0;					// Counter to the number of readers currently active

// Class to represent time in a format convenient to us. 
class Time{
public:
	std::chrono::time_point<std::chrono::high_resolution_clock> time_point;
	struct tm *time;	// Time represented in fields of DD:MM:YYYY HH:MM:SS

	// Returns the time in (HH:MM:SS) format.
	std::string str(){
		std::stringstream temp;
		temp << std::put_time(time, "%T");

		return temp.str();
	}

	// Overloads the subraction operator to returns time difference in milliseconds
	double operator-(Time& t2){
		return std::chrono::duration_cast<std::chrono::milliseconds>(time_point - t2.time_point).count();
	}
};

// Function for returning the current time of the day.
Time getSysTime(){
	Time curr_t;
	auto t = std::time(0);
	curr_t.time_point = std::chrono::high_resolution_clock::now();
	curr_t.time = std::localtime(&t);

	return curr_t;
}

// Function to make the invoking thread sleep for 't' milliseconds
inline void sleep(double t){
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(t)));
}

// The writer thread simulating writing
void writer(int id){
	auto pid = std::this_thread::get_id();

	// generate our random execution times for CS and remaining section
	std::default_random_engine seed;
	std::exponential_distribution<double> CS_distr(1.0/mu_cs), rem_distr(1.0/mu_rem); 
	double randCSTime = CS_distr(seed);
	double randRemTime = rem_distr(seed);
	

	for(int i=0; i<kw; ++i){
		// Entry Section
		Time reqTime = getSysTime();
		std::stringstream request_statement, entry_statement, exit_statement;
		request_statement << i + 1 << "th CS Request\t at " << reqTime.str() << " by Writer Thread " << id + 1 << " \t(pid = " << pid << ")" << std::endl;
		log_file << request_statement.str();

		sem_wait(&queue);
		sem_wait(&rw_mutex);		// Blocks other readers and writers
		sem_post(&queue);

	// Critical section starts		
		Time EnterTime = getSysTime();
		log_file << i + 1 << "th CS Entry\t at " << EnterTime.str() << " by Writer Thread " << id + 1 << " \t(pid = " << pid << ")" << std::endl;

		avg_waiting_t_w[id] += EnterTime - reqTime;
		if(EnterTime - reqTime > worst_waiting_t_w[id])
			worst_waiting_t_w[id] = EnterTime - reqTime;

		// Simulation of critical section(writing)
		sleep(randCSTime);

		// Exit Section
		Time exitTime = getSysTime();
		exit_statement << i + 1 << "th CS Exit \t at " << exitTime.str() << " by Writer Thread " << id + 1 << " \t(pid = " << pid << ")" << std::endl;
		log_file << exit_statement.str();

		sem_post(&rw_mutex);	// Releases the mutex, allowing other thrreads to proceed
	// Critical section ends

		// Simulation of remainder section
		sleep(randRemTime);
	}

	avg_waiting_t_w[id] /= kw;
}

// The reader thread simulating reading
void reader(int id){
	auto pid = std::this_thread::get_id();

	// generate our random execution times for CS and remaining section
	std::default_random_engine seed;
	std::exponential_distribution<double> CS_distr(1.0/mu_cs), rem_distr(1.0/mu_rem); 
	double randCSTime = CS_distr(seed);
	double randRemTime = rem_distr(seed);
	

	for(int i=0; i<kr; ++i){
		// Entry Section
		Time reqTime = getSysTime();
		std::stringstream request_statement, entry_statement, exit_statement;
		request_statement << i + 1 << "th CS Request\t at " << reqTime.str() << " by Reader Thread " << id + 1 << " \t(pid = " << pid << ")" << std::endl;
		log_file << request_statement.str();

		sem_wait(&queue);
		sem_wait(&read_counter_lock);
		if(++read_count == 1){ // Increment and compare the reader count atomically, and block the writers when we have a reader
			sem_post(&read_counter_lock);
			sem_wait(&rw_mutex);
		}
		else sem_post(&read_counter_lock);
		sem_post(&queue);

	// Critical section starts		
		Time EnterTime = getSysTime();
		entry_statement << i + 1 << "th CS Entry\t at " << EnterTime.str() << " by Reader Thread " << id + 1 << " \t(pid = " << pid << ")" << std::endl;
		log_file << entry_statement.str();

		avg_waiting_t_r[id] += EnterTime - reqTime;
		if(EnterTime - reqTime > worst_waiting_t_r[id])
			worst_waiting_t_r[id] = EnterTime - reqTime;

		// Simulation of critical section(reading)
		sleep(randCSTime);

		// Exit Section
		Time exitTime = getSysTime();
		exit_statement << i + 1 << "th CS Exit \t at " << exitTime.str() << " by Reader Thread " << id + 1 << " \t(pid = " << pid << ")" << std::endl;
		log_file << exit_statement.str();

		sem_wait(&read_counter_lock);
		if(--read_count == 0) // Atomically decrement the reader count, and release the rw_mutex only if their are no more readers left
			sem_post(&rw_mutex);
		sem_post(&read_counter_lock);
	// Critical section ends

		// Simulation of remainder section
		sleep(randRemTime);
	}

	avg_waiting_t_r[id] /= kr;
}


int main(){
	// read the input from the file
	input_file >> nw >> nr >> kw >> kr >> mu_cs >> mu_rem;
	input_file.close();

	std::vector<std::thread> writer_threads;
	std::vector<std::thread> reader_threads;
	
	sem_init(&rw_mutex, 0, 1);
	sem_init(&queue, 0, 1);
	sem_init(&read_counter_lock, 0 ,1);
	
	// Start the n writer threads
	for(int i=0; i<nw; ++i){
		avg_waiting_t_w.push_back(0);
		worst_waiting_t_w.push_back(0);
		writer_threads.emplace_back(std::thread(writer, i));
	}
	// Start the n reader threads
	for(int i=0; i<nr; ++i){
		avg_waiting_t_r.push_back(0);
		worst_waiting_t_r.push_back(0);
		reader_threads.emplace_back(std::thread(reader, i));
	}

	for(auto& w:writer_threads)	w.join();
	for(auto& r:reader_threads)	r.join();

	double total_avg_t_w = 0, total_avg_t_r = 0;
	double total_worst_t_w = 0, total_worst_t_r = 0;
	for(int i=0; i<nw; ++i){
		stats_file << "Writer Thread " << i+1 << ":\tAverage waiting time(in ms) = " << avg_waiting_t_w[i] 
			<< "\t\tWorst waiting time(in ms) = " << worst_waiting_t_w[i] << std::endl;

		total_avg_t_w += avg_waiting_t_w[i];
		if(worst_waiting_t_w[i] > total_worst_t_w)
			total_worst_t_w = worst_waiting_t_w[i];
	}
	stats_file << std::endl;
	for(int i=0; i<nr; ++i){
		stats_file << "Reader Thread " << i+1 << ":\tAverage waiting time(in ms) = " << avg_waiting_t_r[i] 
			<< "\t\tWorst waiting time(in ms) = " << worst_waiting_t_r[i] << std::endl;

		total_avg_t_r += avg_waiting_t_r[i];
		if(worst_waiting_t_r[i] > total_worst_t_r)
			total_worst_t_r = worst_waiting_t_r[i];
	}
	total_avg_t_w /= nw;
	total_avg_t_r /= nr;

	stats_file << "\nOverall average waiting time for writers(in ms) = " << total_avg_t_w << std::endl;
	stats_file << "Overall worst case waiting time for writers(in ms) = " << total_worst_t_w << std::endl;

	stats_file << "\nOverall average waiting time for readers(in ms) = " << total_avg_t_r << std::endl;
	stats_file << "Overall worst case waiting time for readers(in ms) = " << total_worst_t_r << std::endl;

	return 0;
}