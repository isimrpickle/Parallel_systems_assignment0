#include "exercise2.h"



int main(int argc,char** argv){
    int thread_count;
    long int thread_loop;
    if(argc>1){
        thread_count = atoi(argv[1]);
        thread_loop = atol(argv[2]); 
    }
    else{
        thread_count=4;
        thread_loop=1000000;
    }
    long  int global_variable;
    printf("the thread count is%d and the thread loop is %ld \n",thread_count, thread_loop);
    global_variable = using_pthreads(thread_count,thread_loop);
    printf("the global_variable of using pthreads is %ld \n",global_variable);fflush(stdout);
    global_variable = using_atomic(thread_count,thread_loop);
    printf("the global_variable of using atomic is %ld \n \n \n \n ",global_variable);fflush(stdout);
}