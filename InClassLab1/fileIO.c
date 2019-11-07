#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

  int count = 0;
  char* helper = NULL;
  FILE *fp;
  size_t len = 0;
  ssize_t read;
  char *buf;
  char *needle = "Holmes";
  fp = fopen("/u/barnecle/E201-Fall-2019/InClassLab1/big.txt", "r");
  if(fp == NULL){
    exit(EXIT_FAILURE);
  }
  while((read = getline(&buf, &len, fp)) != -1){
    helper = strstr(buf, needle);
    if(helper != NULL){
      count++;
    }
  }
  fclose(fp);
  printf("Holmes is found in %d lines in big.txt\n", count);
  exit(0);
}
