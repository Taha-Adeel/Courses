#include<stdio.h>
#include<stdlib.h>
#include<seven_segment.h>

int main()
{
	init();
	int input;
	while(1)
	{
		input = readInt();
		select(1);
		if input
		{
			write(strtol(11111100));
		}
		else
		{
			write(strtol(01100000));
		}
		delay(40);
	}
}
