#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define SZ 1000

int main(){

  int i, j, p, pid, sum=0, sum1=0, sum2=0;
  int array[SZ];
  int fd[2];

  for (i = 0; i < SZ; i++) { //initialize array
    array[i] = i*5;
  }
  
  p = pipe(fd);

  if((pid = fork())<0){ //create fork, error if fails
    perror("fork");
    exit(EXIT_FAILURE);
  }else if(pid > 0){ //Parent Process
    for(i = 0; i < (SZ/2); i ++){ //add up first half of array
      sum1 += array[i];

    }
    
    close(fd[0]);
    write(fd[1], &sum1, sizeof(sum1));
    close(fd[1]);
    wait(NULL); //wait for child process to finish

  }else{ //Child Process
    for(j = (SZ/2); j < SZ; j++){ //add up 2nd half of array
	sum2 += array[j];
      }
    close(fd[1]);
    read(fd[0], &sum1, sizeof(sum1));
    sum2+=sum1;
    close(fd[0]);
    printf("sum of array = %d\n", sum2);
    }
    
  return 0;

}
