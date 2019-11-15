#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int countfile(char* file, char* needle);


int main(){
  char *needle = "football";
  char* file =  "/u/barnecle/E201-Fall-2019/HW5/clickstream-enwiki-2019-09.tsv";
  char* sneedle = "username";
  char* sfile = "/u/barnecle/E201-Fall-2019/HW5/enwik9";  
  int count = countfile(file, needle);
  int count2 = countfile(sfile, sneedle);
 printf("String football found %d times\n", count);
 printf("String username found %d times\n", count2);
 fflush(stdout);
 exit(0);
}


int countfile(char* file, char* needle){
  FILE *fp;
  fp = fopen(file, "r");
  if(fp == NULL){
    exit(EXIT_FAILURE);
  }
  int count = 0;
  char* helper = NULL;
  size_t len = 0;
  ssize_t read;
  char *buf = NULL;
 while((read = getline(&buf, &len, fp)) != -1){
   helper = strstr(buf, needle);
  /* if(helper != NULL){
     strcpy(buf,( helper + strlen(needle)));*/
      while(helper != NULL){
       count ++;
       strcpy(buf,( helper + strlen(needle)));
       helper = strstr(buf, needle);
       }

        }
     
  fclose(fp);
  return count;
}
