#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

float stockval;
float a = 0.45;
int j = 0;
int c;
sem_t s1;
sem_t s2;
sem_t reader;
sem_t writer;

void *read(){
  int i;
  int k;
  int val;
  while(j != 16){
	 
	  for(c = 0; c<8; c++){
	    sem_wait(&s1); //wait for writers to write

	    printf("\n"); //these printf("\n"); lines for some reason, are needed to make the program work
	    sem_wait(&reader); //only one reader prints at a time
	    for(i = 0; i<5; i++){
 	    	    printf("\t\tThread %d Stock Value = %f\n", pthread_self(), stockval);
	    }
	    sem_post(&reader);
	    printf("\n");
	  }

	  sem_post(&s2); //writers allowed to write


  }
	
}
void *write(){
  int i;
  int k;

  for(i = 0; i<4; i++){
	sem_wait(&s2); //after first writing, wait for readers
	sem_wait(&writer); //only one writer writes at time
	printf("\n");
	stockval = (float)rand() * a; //assign random float
	printf("Thread %d writing value %f\n", pthread_self(), stockval);
	j++; //increment count
	sem_post(&writer);
	printf("\n");
	for(k = 0; k <8; k++){ //post 8 times for 8 readers
        	sem_post(&s1);
        }

  }
  
  if(j == 15){ //for the last writer, post one more time to let readers leave
	for(i = 0; i <8; i++){
	  sem_post(&s1);
	}
  }
}

int main(){
  pthread_t writers[12];
  int i;
  sem_init(&s1, 1, 0);
  sem_init(&s2, 1, 1);
  sem_init(&reader, 1, 1);
  sem_init(&writer, 1, 1);
  for(i = 0; i<12; i++){
     if(i<4){ //four writers
	pthread_create(&writers[i], NULL, &write, NULL);
     }else{ //eight readers
	 pthread_create(&writers[i], NULL, &read, NULL);
     }
  }

  for(i = 0; i<12; i++){
        pthread_join(writers[i], NULL);
  }

  sem_destroy(&s1);
  sem_destroy(&s2);
  sem_destroy(&reader);
  sem_destroy(&writer);
  exit(0);
}
