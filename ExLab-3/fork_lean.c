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

if(pid<0){
  exit(EXIT_FAILURE);
}else if(pid>0){
  int fact = factorial(x);
  printf("factorial of %d is %d\n", x, fact);
  wait();
}else if(pid == 0){
  int fib = F(x);
  printf("fibonacci sequence for %d is %d\n", x, fib);
}

exit(0);
}
int factorial(int x){
 int i;
  int factorial = 1;
  for(i = x; i>0; i--){
        factorial = factorial * i;

  }
  return factorial;
}
int F(int x){
  int j;
  int n[11];
  int fib;
  for(j=0; j<=x; j++){
        if(j == 0 || j == 1){
          n[j] = j;

        }
        else{
          n[j] = n[j-2] + n[j-1];

        }
        fib = n[j];
  }
  return fib;
}
