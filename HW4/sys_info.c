#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

extern int errno;

int main(int argc, char* argv[]){
  
  int errnum;
  char rbuf[30];
  int fd[2], pid, nbytes, i, p;
  int j = 0;
  if(argc<2){ //errors for too many or few args
    perror("Too few arguments, please enter 1 argument\n");
    exit(EXIT_FAILURE);
  } else if(argc>2){
    perror("Too many arguments, please enter 1 argument\n");
    exit(EXIT_FAILURE);
  }

  printf("Parent ID: %d\n", getpid());
  p = pipe(fd); //create pipe
  if(p < 0) //error for pipe failure
    {
      perror("pipe");
      exit(EXIT_FAILURE);
    }
  if((pid = fork()) <0){ //fork and error for fork failure
    perror("fork");
    exit(EXIT_FAILURE);
  
  }else  if(pid > 0){ //Parent Function
    printf("I am a parent, my P.I.D = %d\n", getpid()); 
    close(fd[0]); //Write into pipe cmdline arg
    write(fd[1], argv[argc-1], (strlen(argv[argc-1])+1));
    close(fd[1]);
    wait(NULL); //wait for child

  }else{ //Child Function
    printf("I am a child! My P.I.D. = %d\n", getpid());
    printf("My parent P.I.D = %d\n", getppid());
    close(fd[1]); //Read from pipe
    read(fd[0], rbuf, 30);
    
    char path[40];
    if(rbuf[0] == '/'){ //if cmdline arg has path in it
	
	for(i = 5; i<30; i++, j++){ //copy name of function into path
		path[j] = rbuf[i];
	}
	path[++j]='\0';//make a string
	
	execl(rbuf, path, 0, 0); //execute command
	if(errno != 0){ //if execl fails, error message
		printf("%s, please enter valid command\n", strerror(errno));
	}
    }else{
	
	strcpy(path,"/bin/"); //if arg w/o path, copy path /bin/ to path
       	strcat(path, rbuf);  //then add name of command
	execl(path, rbuf, 0, 0);
	if(errno != 0){ //if execl fails, error message
                printf("%s, please enter valid command\n", strerror(errno));
        }

    }       
    close(fd[0]);
 }
    
    exit(0);

}
