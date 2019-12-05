#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t upper;
sem_t lower;
sem_t cons;

sem_t mutexi;
sem_t mutexj;
sem_t mutexk;

char buf[5];
int h = 0;

void *randl(void* arg){
  int i;
  sem_wait(&lower);
  sem_wait(&mutexi);
  for(i = 0; i < 5; i++){
	buf[i] = rand()%26 + 'a';
        printf("Thread %d writing %c\n", pthread_self(), buf[i]);
  } 
  sem_post(&lower);
  sem_post(&mutexk);

}
void *randU(void* arg){
  int j;
  sem_wait(&mutexj);
  sem_wait(&upper);
  for(j = 0; j < 5; j++){
	buf[j] = rand()%26 + 'A';
        printf("Thread %d writing %c\n", pthread_self(), buf[j]);
  }
  sem_post(&upper);
  sem_post(&mutexk);
 
}
void *reader(void* arg){
  int k;
  sem_wait(&mutexk);
  sem_wait(&cons);
  for(k = 0; k < 5; k++){
        printf("\t\tThread %d reading %c\n", pthread_self(), buf[k]);
  }
  h++;
  sem_post(&cons);
  if(h< 2){
	sem_post(&mutexj);
  }else{
	sem_post(&mutexi);
  }
}
int main(){
  sem_init(&upper, 1, 1);
  sem_init(&lower, 1, 1);
  sem_init(&cons, 1, 1);
  sem_init(&mutexi, 1, 0);
  sem_init(&mutexj, 1, 1);
  sem_init(&mutexk, 1, 0);

  pthread_t t[8];
  int i;

  for(i = 0; i<8; i++){
	if(i<2){
	  pthread_create(&t[i], NULL, &randU, NULL);
  	}else if(i<4){
	   pthread_create(&t[i], NULL, &randl, NULL);
	}else{
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

