#include "exercise_4.h"

typedef struct r_w{
pthread_mutex_t mutex;
pthread_cond_t reader,writer;
int reading_threads,waiting_to_read,writing_threads,waiting_to_write;

}reader_writer_lock;


void* unlocking(reader_writer_lock* R_W,int thread_type){
    pthread_mutex_lock(&R_W->mutex);
    if(thread_type == 0){ //thread_type==0 means it's a reading threads, else it's a writing one
        R_W->reading_threads--;
        if(R_W->reading_threads==0 && R_W->writing_threads>=1)
            pthread_cond_signal(&R_W->writer);
    }

    else{  //implementation which gives priority into a reading thread
        R_W->writing_threads--;
        if(R_W->waiting_to_read>=1)  
            pthread_cond_signal(&R_W->reader);
        else{
            pthread_cond_signal(&R_W->writer);
        }
    }

    pthread_mutex_unlock(&R_W->mutex);
}



void*reading_lock(void* r_w_lock){
    reader_writer_lock* R_W = (reader_writer_lock*) r_w_lock;
        
    pthread_mutex_lock(&R_W->mutex);
    while(R_W->writing_threads>=1){
        
        R_W->waiting_to_read++;
        pthread_cond_wait(&R_W->reader,&R_W->mutex);
        
    }
    R_W->waiting_to_read--;
    R_W->reading_threads++;
    pthread_mutex_unlock(&R_W->mutex);
    unlocking(R_W,0);
    }


void* writing_lock(void* r_w_lock){
    reader_writer_lock* R_W = (reader_writer_lock*) r_w_lock;
    pthread_mutex_lock(&R_W->mutex);
    while(R_W->reading_threads>=1 || R_W->writing_threads >=1){
        R_W->waiting_to_write++;
        pthread_cond_wait(&R_W->writer,&R_W->mutex);
    }
    R_W->writing_threads++;;
    pthread_mutex_unlock(&R_W->mutex);
    unlocking(R_W,1);
}








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



}