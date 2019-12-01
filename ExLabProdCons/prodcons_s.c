#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#define STACK_SZ 5

//coordination between programs
sem_t mutexj; 
sem_t mutexi;
sem_t mutexk;
//coordination between threads
sem_t prodU; 
sem_t prodl;
sem_t con;

char stack[STACK_SZ];
int top = 0;
int test = 0;

void *prod_upper(void *arg){
    int i;
    sem_wait(&mutexi); //mutexi = 1, starts immediately
    sem_wait(&prodU); //only one thread writes at a time
    for(i = 0; i < 5; i++){
        stack[top] = 'A' + (rand() % 26); //random letter
        printf("%ld writing %c\n", pthread_self(), stack[top]);
        top++; //increment top of stack
    }
    sem_post(&prodU); 
    sem_post(&mutexj); //signal stack full to consumer
}
void *prod_lower(void *arg){
    int k;
    sem_wait(&mutexk); //writes after prod_upper done
    sem_wait(&prodl); //only one thread writes at a time
    for(k = 0; k < 5; k++){
        stack[top] = 'a' + (rand() % 26); //rand lower case letter
        printf("%ld writing %c\n", pthread_self(), stack[top]);
        top++; 
    }
    sem_post(&prodl);
    sem_post(&mutexj); //signal stack full to consumer
}
void *cons(void *arg){
    int j;
    
    sem_wait(&mutexj); //wait for stack to be full
    sem_wait(&con);
    for(j = 0; j<5; j++){
        printf("\t\t%ld consuming %c\n", pthread_self(), stack[--top]);
        
    }
    test ++; //to decide to use prod_upper or _lower
    sem_post(&con);
    if(test<2){
        sem_post(&mutexi); //signal to prod_upper
    }else{
        sem_post(&mutexk); //signal to prod_lower
    }
}
int main(){
    sem_init(&mutexi, 1, 1);
    sem_init(&mutexj, 1, 0);
    sem_init(&mutexk, 1, 0);
    sem_init(&prodU, 1, 1);
    sem_init(&prodl, 1, 1);
    sem_init(&con, 1, 1);
    srand(time(0)); //to randomize
    pthread_t threads[8];
    int i;
    for(i =0; i<8; i++){ //create pthreads
        if(i<2){ //Upper case writers
            pthread_create(&threads[i], NULL, &prod_upper, NULL);
        }else if(i<4){ //Lower case writers
            pthread_create(&threads[i], NULL, &prod_lower, NULL);
        }else{ //readers
            pthread_create(&threads[i], NULL, &cons, NULL);
        }
        
    }

    for(i = 0; i<8; i++){ //join pthreads
        pthread_join(threads[i], NULL);
    }
    
    //destroy semaphores
    sem_destroy(&prodl);
    sem_destroy(&prodU);
    sem_destroy(&con);
    sem_destroy(&mutexi);
    sem_destroy(&mutexj);
    sem_destroy(&mutexk);
    exit(0);

}