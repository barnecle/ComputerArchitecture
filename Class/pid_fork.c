#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	printf("Parent ID (in parent): %d\n", getpid());
	
	int returnval = fork();
	if(returnval == 0){
		printf("Child ID (in child): %d\n", getpid());
		printf("Parent ID (in child): %d\n", getppid());
	}

	return 0;
}
