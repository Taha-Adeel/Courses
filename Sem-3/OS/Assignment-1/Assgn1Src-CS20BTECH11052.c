#include <stdio.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

/**
 * @brief Recursive implementation to output Collatz Sequence for positive integer n
 * 
 * @param n 
 */
void CollatzAlgo(int n){
	if(n <= 0){
		printf("ERROR: Negative input provided to CollatzAlgo.\n");
		return;
	}

	// Base case (Stop when sequence reaches 1)
	if(n==1){
		printf("1\n");
		return;
	}

	printf("%d, ", n); // Output the current value in the sequence.
	if(n % 2 == 0) // If n is even
		CollatzAlgo(n/2);
	else // If n is odd
		CollatzAlgo(3*n + 1);
}

int main(){
	// Get input from user
	int n;
	printf("Enter the value of n(positive integer) for which the Collatz Conjecture will be tested: ");
	scanf("%d", &n);
	if(n <= 0){
		printf("ERROR: Invalid value entered.\n");
		return 1;
	}

	// fork the parent process, and store the result of forking in pid
	pid_t pid = fork();

	if(pid < 0){ // If pid < 0, implies forking failed
		printf("ERROR: Child process creation failed!\n");
		return 1;
	}
	else if(pid == 0){ // Value of pid is zero for child process
		printf("\nIn child process.\n");
		printf("Collatz Sequence for %d is as follows: \n", n);
		CollatzAlgo(n);
	}
	else if(pid > 0){ // pid > 0 for parent process
		wait(NULL); // The parent process waits until the child completes execution.
		printf("\nChild process execution successfully completed. \nIn parent process.\n");
	}

	return 0;
}