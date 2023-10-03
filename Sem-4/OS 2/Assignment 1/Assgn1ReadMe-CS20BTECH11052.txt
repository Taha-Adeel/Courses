To compile the source code, run the following command in the terminal (Command line)
	gcc -o Assgn1Src-CS20BTECH11052 Assgn1Src-CS20BTECH11052.c -lpthread -lm

To run the executable, run the following command in the terminal (Command line)
	./Assgn1Src-CS20BTECH11052

To generate a new input file called "<filename>.txt" (with n destination points), run
	./random n >> <filename>.txt

The program takes input from the files input1000.txt, input2000.txt, ... which were generated using random.c.

The input file can be changed by changing the variable "filename" on line 74 to change the number of input points.
The number of threads can be changed on the first line of the input files.


In this program, the main thread creates n worker threads. The set of destination points are equally divided
among the n threads and each thread finds the nearest point from the source among its sub-set. Then the
thread terminates the closest point found to the main thread and then terminates. The main thread then 
determines the nearest point from the points given by the threads.