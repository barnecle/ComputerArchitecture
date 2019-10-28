#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[]){
  
  char buf[30];
  int p[2], pid, nbytes, i, j;

  memset(buf, 0, 30);

  printf("Parent ID: %d\n", getpid());
  
  if(pipe(p) < 0)
    {
      perror("pipe");
      exit(EXIT_FAILURE);
    }

  if((pid = fork()) > 0){
    printf("I am a parent, my P.I.D = %d\n", getpid()); 
    close(p[0]);
    write(p[1], argv, argc);
    close(p[1]);
    wait(NULL);
  }
 
  if(pid == 0){
    printf("I am a child! My P.I.D. = %d\n", getpid());
    printf("My parent P.I.D = %d\n", getppid());
    close(p[1]);
    printf("here\n");
    read(p[0], buf, 30);
    printf("here\n");
    printf("here bad word\n");
    char path[30];
    printf("here\n");
    strcpy(path, buf);
    printf("here\n");
    strcat("/bin/", path);
    printf("here\n");
    fflush(stdout);
    for(i=0; i<30; i++){
	printf("%s", path[i]);
     }
      //execl(path, buf, 0, 0);
    

    }
    
    return 0;

}
