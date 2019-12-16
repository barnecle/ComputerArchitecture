#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

float stockval;
float a = 0.45;
int count = 0;
sem_t buf;
sem_t mutex;

void *read(){
  int i;

  for(i = 0; i<5; i++){
	sem_wait(&mutex); //only one reader has access to count at a time
	count++;
	if(count == 1){ //if the first reader, wait for buffer to be filled
		sem_wait(&buf);
	}
	sem_post(&mutex); //release count section
	printf("\t\tThread %d Stock Value = %f\n", pthread_self(), stockval);
	sem_wait(&mutex); //lock to modify count
	count--;
	if(count == 0){ //if last reader, release buffer
		sem_post(&buf);
	}
	sem_post(&mutex); //release count
  }

	
}
void *write(){
  int i;
 
  for(i = 0; i<4; i++){
	sem_wait(&buf); //wait for buffer
	stockval = (float)rand() * a; //assign random float
	printf("Thread %d writing value %f\n", pthread_self(), stockval);

	sem_post(&buf); //release buffer for next thread
        

  }
  

}

int main(){
  pthread_t writers[12];
  int i;
  sem_init(&buf, 1, 1);
  sem_init(&mutex, 1, 1);
 

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

  sem_destroy(&mutex);
  sem_destroy(&buf); 
  exit(0);
}
