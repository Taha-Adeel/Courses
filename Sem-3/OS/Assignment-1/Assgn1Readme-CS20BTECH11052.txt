To compile the source code, run the following command in the terminal (Command line)
	gcc -o Assgn1Src-CS20BTECH11052 Assgn1Src-CS20BTECH11052.c

To run the executable, run the following command in the terminal (Command line)
	./Assgn1Src-CS20BTECH11052

Once the executable starts, it will prompt you for the value (positive integer) for which the Collatz Conjecture will be verified. 
Enter a positive integer in the command line for the process to continue.

A child process will be created which will output the Collatz sequence for above provided input while the parent process waits for the child to finish.

The program completes execution after the child process finishes, and the parent process also completes execution.