#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



int j = 0;
int array[SZ];
int sum = 0;

void *add_array(void* limit){
  int nlimit = *(int*) limit; //cast arg
  for(j; j<nlimit; j++){ //add up part of the array
  	sum += array[j];
  }
 
  j = nlimit; //set j equal to the index thread added up to for next thread

}


int main(){
  pthread_t threads[N_THREADS];
  int divs, div, i, h;
  void* arg;
  div = SZ/N_THREADS; //get amount of array each thread will handle
  for (i = 0; i < SZ; i++) { //initialize array
    array[i] = i*5;
    }
  
  divs = div;
  for(i = 0; i <N_THREADS; i++){ //create threads
    arg = &divs; //amount of array given to thread
    pthread_create(&threads[i], NULL, &add_array, arg);
    divs += div; //increment to next index amount
    }
 
 for(h = 0; h<N_THREADS; h++){ //join threads
      pthread_join(threads[h], NULL);
   }

  printf("sum of array: %d\n", sum);
  return 0;
}
