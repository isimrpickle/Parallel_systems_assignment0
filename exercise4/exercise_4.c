#include "r_w_lock_functions.h"



int main(int argc,char* argv){
    int reader_threads_size = 5;
    int writing_threads_size = 2;
    reader_writer_lock* R_W = malloc(sizeof(reader_writer_lock));
    R_W->reading_threads= 0 ;
    R_W->waiting_to_write = 0;
    R_W->waiting_to_read= 0 ;
    R_W->writing_threads = 0;
    pthread_cond_init(&R_W->reader,NULL);
    pthread_cond_init(&R_W->writer,NULL);
    pthread_mutex_init(&R_W->mutex,NULL);
    pthread_t* reader_threads = malloc(sizeof(pthread_t)*reader_threads_size);
    pthread_t* writer_threads = malloc(sizeof(pthread_t)*writing_threads_size);

    for(int i=0; i<reader_threads_size;i++)
        pthread_create(&reader_threads[i],NULL,reading_lock,(void*) R_W);

    for(int i=0; i<writing_threads_size;i++)
        pthread_create(&writer_threads[i],NULL,writing_lock,(void*) R_W);

    for(int i=0;i<reader_threads_size;i++)
        pthread_join(reader_threads[i],NULL);
    
    for(int i=0;i<writing_threads_size;i++)
        pthread_join(writer_threads[i],NULL);

    free(reader_threads);
    free(writer_threads);

    pthread_cond_destroy(&R_W->reader);
    pthread_cond_destroy(&R_W->writer);
    pthread_mutex_init(&R_W->mutex, NULL);
}