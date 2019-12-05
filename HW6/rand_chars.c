#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char randl(void);
char randU(void);

int main(){
  srand(time(0)); //seed for rand()
//print 10 lower case letters
  printf("%c\n", randl()); 
  printf("%c\n", randl());
  printf("%c\n", randl());
  printf("%c\n", randl());
  printf("%c\n", randl());
  printf("%c\n", randl());
  printf("%c\n", randl());
  printf("%c\n", randl());
  printf("%c\n", randl());
  printf("%c\n", randl());

//print 10 capital letters
  printf("%c\n", randU());
  printf("%c\n", randU());
  printf("%c\n", randU());
  printf("%c\n", randU());
  printf("%c\n", randU());
  printf("%c\n", randU());
  printf("%c\n", randU());
  printf("%c\n", randU());
  printf("%c\n", randU());
  printf("%c\n", randU());

}
char randl(void){
	return rand()%26 + 'a'; //returns random letter using ASCII
}
char randU(void){
	return rand()%26 + 'A';
}
