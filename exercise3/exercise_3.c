#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>


void calculation(void*){

}

void array_thread(int number_of_threads,int thread_loop){
pthread_t * thread_handles = malloc(sizeof(thread_handles)*number_of_threads);

for(int i=0;i<thread_handles;i++){
    int thread_id=i;
    pthread_create(thread_handles[i],NULL,calculation,(void*)thread_id);
}

}