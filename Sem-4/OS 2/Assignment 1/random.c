#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	srand(time(0));
	printf("4\n");
	printf("(%d,%d)\n", rand()%100000, rand()%100000);
	int n = atoi(argv[1]);
	// int n;
	// scanf("%d", &n);
	printf("%d\n", n);
	for(int i=0; i<n; ++i)
		printf("(%d,%d) ", rand()%100000, rand()%100000);

	printf("\n");
}