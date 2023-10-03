#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

/**
 * @brief Struct to hold the co-ordinates of the destinations
 * 
 */
typedef struct pair{
	long int X;
	long int Y;
} Pair;

/**
 * @brief Global variables to hold the data
 * 
 */
int num_of_threads;
Pair pt_0;
int num_of_pts;
Pair *pts;

Pair *closest_pts;

// Forward declaration of utility functions
void read_pair(char* pair, Pair *pt);
double get_distance(Pair* p1, Pair* p2);

/**
 * @brief Returns the closest pair from an array/subarray pointed to by "arr" and of size "size".
 * 
 * @param arr 
 * @param size 
 * @return Pair 
 */
Pair get_closest(Pair* arr, int size){
	Pair* closest = &arr[0];
	double min_dist = get_distance(&pt_0, closest);

	for(int i = 0; i < size; ++i){
		double dist = get_distance(&pt_0, &arr[i]);
		// usleep(1000); // sleep for 1000 microseconds
		if(dist < min_dist){
			min_dist = dist;
			closest = &arr[i];
		}
	}
	return *closest;
}

/**
 * @brief A wrapper function for the get_closest() function. This function is called by the threads.
 * 
 * @param thread_num An integer which keeps track of which thread has called the function.
 * @return void* 
 */
void* get_closest_wrapper(void* thread_num){
	int thread_id = *(int*)thread_num;
	free(thread_num);
	int size = num_of_pts/num_of_threads;

	if(thread_id < (num_of_threads - 1))
		closest_pts[thread_id] = get_closest(pts + thread_id*size, size);
	else
		closest_pts[thread_id] = get_closest(pts + thread_id*size, num_of_pts - thread_id*size);
}

int main(){
	// Read input
	char* filename = "input5000.txt";
	FILE* input_file = fopen(filename, "r");
	if(input_file == NULL){
		printf("Error opening file.\n");
		return EXIT_FAILURE;
	}

	fscanf(input_file, "%d", &num_of_threads);
	closest_pts = (Pair*) malloc(num_of_threads * sizeof(Pair));

	char pair[25];
	fscanf(input_file, "%s", pair);
	read_pair(pair, &pt_0);

	fscanf(input_file, "%d", &num_of_pts);
	pts = (Pair*)malloc(num_of_pts*sizeof(Pair));

	for(int i=0; i<num_of_pts; ++i){
		fscanf(input_file, "%s", pair);
		read_pair(pair, &pts[i]);
	}

	fclose(input_file);

	// Start measuring time
	struct timespec start, end; 
	// clock_gettime(CLOCK_REALTIME, &start);

	// Start the threads
	pthread_t *threads = (pthread_t*) malloc(num_of_threads * sizeof(pthread_t));
	for(int i = 0; i < num_of_threads; ++i){
		int* j = (int*)malloc(sizeof(int));
		*j = i;
		pthread_create(&threads[*j], NULL, &get_closest_wrapper, (void*)(j));
	}

	// Wait for the threads to finish execution
	for(int i = 0; i < num_of_threads; ++i)
		pthread_join(threads[i], NULL);

	// Find the closest point among the closest points found by the different threads
	Pair closest = get_closest(closest_pts, num_of_threads);

	// Find the closest pt using just the main thread. Comment the above code and uncomment the next line to find the closest point sequentially.
	// Pair closest = get_closest(pts, num_of_pts);

	
	// Stop and measure the time.
	// clock_gettime(CLOCK_REALTIME, &end);
    double elapsed_microseconds = (end.tv_sec - start.tv_sec)*1e6 + (end.tv_nsec - start.tv_nsec)*1e-3;

	// printf("Number of threads: %d \t Number of points: %d\n", num_of_threads, num_of_pts);
    printf("%.2lf microseconds\n", elapsed_microseconds);
	printf("(%ld, %ld)\n", closest.X, closest.Y);


	return EXIT_SUCCESS;
}

/**
 * @brief Parses a string of the form (x,y), where x and y are numbers and stores it in pt.
 * 
 * @param pair 
 * @param pt 
 */
void read_pair(char* pair, Pair *pt){
	int l_location, comma_location, r_location;
	for(int i=0; pair[i] != '\0'; ++i){
		if(pair[i] == '(')
			l_location = i;
		if(pair[i] == ',')
			comma_location = i;
		if(pair[i] == ')')
			r_location = i;
	}

	char temp_x[10], temp_y[10];
	strncpy(temp_x, &pair[l_location + 1], comma_location - l_location - 1);
	strncpy(temp_y, &pair[comma_location + 1], r_location - comma_location - 1);
	temp_x[comma_location - l_location - 1] = '\0';
	temp_y[r_location - comma_location - 1] = '\0';
	
	pt->X = atoi(temp_x);
	pt->Y = atoi(temp_y);
}

/**
 * @brief Returns the distance between two points
 * 
 * @param p1 
 * @param p2 
 * @return double 
 */
double get_distance(Pair* p1, Pair* p2){
	double dist_sqr = (p1->X - p2->X)*(p1->X - p2->X) + (p1->Y - p2->Y)*(p1->Y - p2->Y);
	return sqrt(dist_sqr);
}