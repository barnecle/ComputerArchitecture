#include <stdio.h>
#include <time.h>
#define x 10

float A[x][x] = {0};

int main(){

int i, j;

clock_t start, end;
double time;


start = clock();

for(i = 0; i<x; i++)
{
	for(j = 0; j<x; j++)
	{
		A[j][i] = (A[j][i+1] + A[j][i])/2;
	}
}

end = clock();


time = ((double) (end-start)) / CLOCKS_PER_SEC;

printf("Time = %f\n", time);
}
