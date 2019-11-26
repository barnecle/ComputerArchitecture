#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#define N_THREADS 5

sem_t mutex;
int count = 30;

void* increment(void *arg){
   int test = 0;
   int consumed = 0; 
   while(!test){ 
    sem_wait(&mutex);
    if(count==0){
	test = 1;
    }else{
    count--;
    consumed++;
    printf("Thread: %d\n count has %d remaining!\n", pthread_self(), count);
   }
   sem_post(&mutex);
 }
 printf("Thread %d consumed %d\n", pthread_self(), consumed);
}	
int main(){
  int i;
  pthread_t threads[N_THREADS];
  sem_init(&mutex, 1, 1);
  
  for(i = 0; i<N_THREADS; i++){
	pthread_create(&threads[i], NULL, &increment, NULL);
  }
  
  for(i = 0; i<N_THREADS; i++){
	pthread_join(threads[i], NULL);
  }
  sem_destroy(&mutex);
}
