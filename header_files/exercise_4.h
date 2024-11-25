#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct r_w{
pthread_mutex_t mutex;
pthread_cond_t reader,writer;
int reading_threads,waiting_to_read,writing_threads,waiting_to_write;

}reader_writer_lock;
void* unlocking(reader_writer_lock* R_W,int thread_type);
void* reading_lock(void* r_w_lock);
void* writing_lock(void* r_w_lock);