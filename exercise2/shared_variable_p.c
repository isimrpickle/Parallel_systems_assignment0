#include "exercise2.h"
pthread_mutex_t mutex;
long int global_variable;
void* computation_p(void* loop_variable){

    intptr_t thread_loop = (intptr_t)loop_variable; //I was getting the warning: cast from pointer to integer of different size
    for(long int i=0;i<thread_loop;i++){
    pthread_mutex_lock(&mutex);
    global_variable++;
    pthread_mutex_unlock(&mutex);
    }
    
}


long int using_pthreads (int thread_count,long int thread_loop){
    
    pthread_mutex_init(&mutex,NULL);
    global_variable=0;
    pthread_t * thread_handles = malloc(thread_count*sizeof(pthread_t)); 
    for(int i=0;i<thread_count;i++){
        pthread_create(&thread_handles[i],NULL,computation_p,(void*)thread_loop);
    }
    for(int i=0;i<thread_count;i++)
        pthread_join(thread_handles[i],NULL);
    
    pthread_mutex_destroy(&mutex);
    return global_variable;
    free(thread_handles);

}

