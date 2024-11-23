#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h> //intptr
#include <string.h> //memset

long int* array;
int loop;
void* calculation(void* thread_id){
intptr_t rank = (intptr_t) thread_id;
    for(int i=0;i<loop;i++)
        *(array + rank)+=1; //accesing the equivalent element of the specific thread's rank and incrementing by one.
}

int  main(int number_of_threads,int thread_loop){
number_of_threads=4;
thread_loop=100000;
pthread_t * thread_handles = malloc(sizeof(pthread_t)*number_of_threads);
array=malloc(sizeof( long int)*number_of_threads);
memset(array, 0, sizeof(long int) * number_of_threads);
loop=thread_loop;
for(int i=0;i<number_of_threads;i++){
    long thread_id=i;
    pthread_create(&thread_handles[i],NULL,calculation,(void*)thread_id);
}

for(int i = 0; i<number_of_threads;i++)
    pthread_join(thread_handles[i],NULL);

printf("the value of each element is: \n");
for(int i=0;i<number_of_threads;i++){
    printf("the value for %d element is %ld \n",i,*(array+i));
}

free(thread_handles);
free(array);
}