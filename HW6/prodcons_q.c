#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

//for use within function
sem_t upper;
sem_t lower;
sem_t cons;

//for use between functions
sem_t mutexi;
sem_t mutexj;
sem_t mutexk;

char buf[5];
int h = 0; //for reader to call either randl or randU

void *randl(void* arg){
  int i;
  sem_wait(&mutexi); //wait for reader to empty buf
  sem_wait(&lower); //only one thread at a time
  for(i = 0; i < 5; i++){
    buf[i] = rand()%26 + 'a'; //random letter
        printf("Thread %d writing %c\n", pthread_self(), buf[i]);
  } 
  sem_post(&lower);
  sem_post(&mutexk); //signal to reader

}
void *randU(void* arg){
  int j;
  sem_wait(&mutexj); //wait for reader after first write
  sem_wait(&upper); //only one thread can write at a time
  for(j = 0; j < 5; j++){
	buf[j] = rand()%26 + 'A';
        printf("Thread %d writing %c\n", pthread_self(), buf[j]);
  }
  sem_post(&upper);
  sem_post(&mutexk);
 
}
void *reader(void* arg){
  int k;
  sem_wait(&mutexk); //wait for full buffer
  sem_wait(&cons); //one reader at a time
  for(k = 0; k < 5; k++){
        printf("\t\tThread %d reading %c\n", pthread_self(), buf[k]);
  }
  h++; //keep track of amount of times reader operates
  sem_post(&cons); 
  if(h< 2){ //after the 2 randU() threads execute go to randl()
    sem_post(&mutexj); 
  }else{
	sem_post(&mutexi);
  }
}
int main(){
  sem_init(&upper, 1, 1);
  sem_init(&lower, 1, 1);
  sem_init(&cons, 1, 1);
  sem_init(&mutexi, 1, 0); //second writer
  sem_init(&mutexj, 1, 1); //first writer
  sem_init(&mutexk, 1, 0); //reader

  pthread_t t[8];
  int i;
  srand(time(0)); //seed for rand()

  for(i = 0; i<8; i++){
    if(i<2){ //two threads to randU
	  pthread_create(&t[i], NULL, &randU, NULL);
    }else if(i<4){ //two threads to randl
	   pthread_create(&t[i], NULL, &randl, NULL);
    }else{ //4 threads to reader
	   pthread_create(&t[i], NULL, &reader, NULL);
  	}
  }

  for(i = 0; i<8; i++){
	pthread_join(t[i], NULL);
  }

  sem_destroy(&upper);
  sem_destroy(&lower);
  sem_destroy(&cons);
  sem_destroy(&mutexi);
  sem_destroy(&mutexj);
  sem_destroy(&mutexk);

}

