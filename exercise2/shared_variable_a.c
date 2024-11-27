#include "exercise2.h"

_Atomic global_counter;


void* computation_a(void* loop_variable){

    intptr_t thread_loop = (intptr_t)loop_variable; //I was getting the warning: cast from pointer to integer of different size
    for(long int i=0;i<thread_loop;i++){
        __atomic_fetch_add(&global_counter,1,__ATOMIC_RELAXED);
    }
    
}


long int using_atomic (int thread_count,long int thread_loop){
    double start,finish;
    GET_TIME(start);
    global_counter=0;
    pthread_t * thread_handles = malloc(thread_count*sizeof(pthread_t)); 
    for(int i=0;i<thread_count;i++){
        pthread_create(&thread_handles[i],NULL,computation_a,(void*)thread_loop);
    }

    for(int i=0;i<thread_count;i++)
        pthread_join(thread_handles[i],NULL);
        
    free(thread_handles);
    GET_TIME(finish);
    printf("the elapsed time is: %lf",finish-start);
    return global_counter;

}


