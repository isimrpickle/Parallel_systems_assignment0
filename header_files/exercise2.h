#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h> //for intptr_t

void* computation_p(void* loop_variable);
void* computation_a(void* loop_variable);

long int using_pthreads (int thread_count,long int thread_loop);
long int using_atomic (int thread_count,long int thread_loop);