#include"ParallelPiCalculation.h"

long int arrows_in_circle;
pthread_mutex_t mutex;
long int number_of_throws=0;
int thread_count=0;


void* Pi_thread_approximation(void* rank){
    
    intptr_t thread_Id =(intptr_t) rank;
    unsigned int seed=2468 + thread_Id ; //giving a random seed?
    long int local_count=0;
    long int loops=number_of_throws/thread_count;
    if(thread_Id==thread_count-1) //if it's the last thread
        loops+=number_of_throws % thread_count; //maybe the tasks do not share equally to each thread. One of them must work harder
    for(long int i=0;i<loops;i++){
        double x=2*my_drand(&seed)-1; //drand returns 0 - 1 so we multiply it by 2 (0 - 2) and sybtract 1 (-1 - 1)
        double y=2 * my_drand(&seed) -1;
        double squared_distance = x*x + y*y;
        if(squared_distance<=1)
            local_count++;
    }
    //accessing global counter variable,so we use lock before we increase it with each thread computation
    pthread_mutex_lock(&mutex);
    arrows_in_circle+=local_count;
    pthread_mutex_unlock(&mutex);

}



void parallel_Pi_calculation(const long int throws,int threads_total_number){
    double start,finish,elapsed_time;
    GET_TIME(start);
    pthread_mutex_init(&mutex,NULL); //initializing mutex
    number_of_throws=throws;
    thread_count=threads_total_number;
    //initialization of threads

    pthread_t* thread_handles = malloc(thread_count*sizeof(pthread_t)); 
    if(thread_handles==NULL)
        printf("there is an error in malloc");fflush(stdout);

    //creating threads and executing the thread function

    for(int thread=0; thread<thread_count;thread++){
        long thread_Id=thread ;
        pthread_create(&thread_handles[thread],NULL,Pi_thread_approximation,(void*)thread_Id);
    }

    for(long int i=0; i<thread_count;i++)
        pthread_join(thread_handles[i],NULL);
    pthread_mutex_destroy(&mutex);
    free(thread_handles);
    double Pi_approximation=4*arrows_in_circle/((double)number_of_throws);
    GET_TIME(finish);
    elapsed_time=finish - start;
    printf("Elapsed_time is %lf and pi is %lf \n",elapsed_time,Pi_approximation);fflush(stdout);

}



