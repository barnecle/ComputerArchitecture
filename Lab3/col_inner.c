#include <stdio.h>
#include <time.h>
#define x 50000

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
		A[i][j] = (A[i][j+1] + A[i][j])/2;
	}
}

end = clock();


time = ((double) (end-start)) / CLOCKS_PER_SEC;

printf("Time = %f\n", time);
}
