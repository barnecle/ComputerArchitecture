#include <stdio.h>
#include <stdlib.h>
#define STACK_SZ 5
int pop(int top, int stack[]);
int insert(int top, int stack[], int x);

int main(){
    int stack[STACK_SZ] = {0};
    int top = 0;
    int i;
    top = insert(top, stack, 2);
    
    top = insert(top, stack, 4);    
    top = insert(top, stack, 5);
    top = insert(top, stack, 7);
    
    for(i = 0; i<STACK_SZ; i++){
        printf("stack at %d = %d\n", i, stack[i]);
    }
    top = pop(top, stack);
    top = pop(top, stack);

    for(i = 0; i<STACK_SZ; i++){
        printf("stack at %d = %d\n", i, stack[i]);
    }
    top = insert(top, stack, 4);
    top = insert(top, stack, 6);
    top = insert(top, stack, 7);
    for(i = 0; i<STACK_SZ; i++){
        printf("stack at %d = %d\n", i, stack[i]);
    }
    top = insert(top, stack, 7);
    for(i = 0; i<5; i++){
        printf("stack at %d = %d\n", i, stack[i]);
    }
}
int insert(int top, int  stack[], int x){
    if(top == STACK_SZ){ //check if full
        printf("Stack full\n");
        return top;
    }else{
        stack[top] = x; //add element and increment top
        top++;
        return top; //return new top
    }
}
int pop(int top, int stack[]){
    if(top == 0){ //check if empty
        printf("Stack empty\n");
        return top;
    }
    stack[--top] = 0; //using 0 to show empty instead of having random dump print out
    return top;
}