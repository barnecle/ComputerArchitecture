#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void *countfile(void* arg);


int main(){
  char *needle = "football";
  char* file =  "/u/barnecle/E201-Fall-2019/HW5/clickstream-enwiki-2019-09.tsv";
  char* sneedle = "username";
  char* sfile = "/u/barnecle/E201-Fall-2019/HW5/enwik9";
  char* pth1[] = {"/u/barnecle/E201-Fall-2019/HW5/clickstream-enwiki-2019-09.tsv","football"};
  char* pth2[] = {"/u/barnecle/E201-Fall-2019/HW5/enwik9", "username"};
  pthread_t threads[2];
  void* arg;
  
  arg = &pth1;
  pthread_create(&threads[0], NULL, &countfile, arg);
  arg = &pth2;
  pthread_create(&threads[1], NULL, &countfile, arg);
  
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);


 exit(0);
}


void *countfile(void* arg){
  
  char** str = (char **) arg; 
  
  printf("%s\n", (*str));
  
  FILE *fp;
  char* file;
    
  fp = fopen((*str), "r");
  if(fp == NULL){
    exit(EXIT_FAILURE);
  }
  int count = 0;
  char* helper = NULL;
  size_t len = 0;
  ssize_t read;
  char *buf = NULL;
 while((read = getline(&buf, &len, fp)) != -1){
   helper = strstr(buf, str[1]);
      while(helper != NULL){
       count ++;
       strcpy(buf,( helper + strlen(str[1])));
       helper = strstr(buf, str[1]);
       }

        }
     
  fclose(fp);
  printf("String %s found %d times\n", str[1], count);

}
