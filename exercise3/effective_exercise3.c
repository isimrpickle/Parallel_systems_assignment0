#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h> //intptr
#include <string.h> //memset
#include "timer.h"


typedef struct padded_array{
    long int array_counter;
    char padding[64 - sizeof(long int)]; //chars are 1 byte and a cache line is 64 byte, so we fill the remaining space with chars
} alligned_array;

alligned_array*  my_array;
int loop;


void* calculation(void* thread_id){
intptr_t rank = (intptr_t) thread_id;
    for(int i=0;i<loop;i++)
        (my_array + rank)->array_counter+=1; //accesing the equivalent element of the specific thread's rank and incrementing by one.
}


int  main(int argc,char**argv ){
    printf("I am the one that uses padding \n");
    int number_of_threads=4;
    long int thread_loop=100000;
    if(argc>1){
        number_of_threads = atoi(argv[1]);
        thread_loop = atol(argv[2]);
    }
    double start, finish;
    GET_TIME(start);
    printf("for number of threads %d and loop being %ld \n",number_of_threads,thread_loop);
    pthread_t * thread_handles = malloc(sizeof(pthread_t)*number_of_threads);
    my_array = malloc(number_of_threads*sizeof(struct padded_array));
    for(int i=0; i <number_of_threads;i++){
        (my_array+i)->array_counter=0; //initializing each counter with zero
    }

     loop=thread_loop; //will be accesed by the threads function
    for(int i=0;i<number_of_threads;i++){
        long thread_id=i;
        pthread_create(&thread_handles[i],NULL,calculation,(void*)thread_id);
    }

    for(int i = 0; i<number_of_threads;i++)
        pthread_join(thread_handles[i],NULL);

    printf("the value of each element is: \n");
    for(int i=0;i<number_of_threads;i++){
        printf("the value for %d element is %ld \n",i,(my_array+i)->array_counter);
    }
    GET_TIME(finish);
    printf("the elapsed time is : %lf \n \n \n ",finish-start);
    free(thread_handles);
    free(my_array);
}
