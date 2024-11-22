#include "exercise2.h"



int main(){
    int thread_count=4;
    long int thread_loop=1000000;
    long int glboal_variable;
    printf("the thread count is%d and the thread loop is %ld \n",thread_count, thread_loop);
    glboal_variable = using_pthreads(thread_count,thread_loop);
    printf("the global_variable of using pthreads is %ld \n",glboal_variable);fflush(stdout);
    using_atomic(4,1000);
    printf("the global_variable of using atomic is %ld \n",glboal_variable);fflush(stdout);
}