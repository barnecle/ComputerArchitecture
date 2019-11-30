#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int factorial(int x);
int F(int x);

int main(){

srand(time(0));
int upper = 10;
int x = rand()%upper;
int pid;

pid = fork();

if(pid<0){ //check if fork() was successful
  exit(EXIT_FAILURE);
}else if(pid>0){ //parent call factorial
  int fact = factorial(x);
  printf("factorial of %d is %d\n", x, fact);
  wait(); //wait for child
}else if(pid == 0){ //child call F, fibonnacci
  int fib = F(x);
  printf("fibonacci sequence for %d is %d\n", x, fib);
}

exit(0);
}
int factorial(int x){
 int i;
 int factorial = 1;
 for(i = x; i>0; i--){
        factorial = factorial * i; //multiply factorial x by x-1, x-2, etc.
 }
 return factorial;
}
int F(int x){
  int j;
  int n[11]; //by function, x<10 so array only needs 11 elements
  int fib;
  for(j=0; j<=x; j++){ //finding element of sequence at certain index, x
        if(j == 0 || j == 1){ //edge cases
          n[j] = j;

        }
        else{
          n[j] = n[j-2] + n[j-1]; //formula for fibonacci

        }
        fib = n[j];
  }
  return fib;
}
