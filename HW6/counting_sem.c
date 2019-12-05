#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

void* letter(void *arg){
  char* p = (char *) arg;
  sem_wait(&mutex);
  printf("%s\n", (char*) p);
  sem_post(&mutex); //FIX for code issue
}
int main(){
  sem_init(&mutex, 1, 2);
  pthread_t t[3];
  int i;

  void *arg = (void*) 'A';  
  pthread_create(&t[0], NULL, &letter, &arg);

  void* barg = (void*) 'B';
  pthread_create(&t[1], NULL, &letter, &barg);

  void* carg = (void*)  'C';
  pthread_create(&t[2], NULL, &letter, &carg);

  for(i = 0; i < 3; i++){
	pthread_join(t[i], NULL);
  }

  sem_destroy(&mutex);

}
