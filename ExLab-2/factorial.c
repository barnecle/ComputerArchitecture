#include <stdio.h>
#include <stdlib.h>

int factorial(int x);

int main(){
    int input = 5;
    printf("factorial %d = %d\n", input, factorial(input) );
    input = 10;
    printf("factorial %d = %d\n", input, factorial(input) );
    input = 4;
    printf("factorial %d = %d\n", input, factorial(input) );
    input = 8;
    printf("factorial %d = %d\n", input, factorial(input) );
    input = 12;
    printf("factorial %d = %d\n", input, factorial(input) );
}
int factorial(int x){
    int i;
    int ret = 1;
    for(i = x; i>0; i--){
        ret = ret * i;
    }
    return ret;
}