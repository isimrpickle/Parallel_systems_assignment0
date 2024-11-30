#include "r_w_lock_functions.h"




void* unlocking(reader_writer_lock* R_W,int thread_type){
    pthread_mutex_lock(&R_W->mutex);
    if(R_W->type_favored==0){ // if readers are favored
        if(thread_type == 0){ //thread_type==0 means it's a reading threads, else it's a writing one
            R_W->reading_threads--;
            if(R_W->reading_threads==0 && R_W->waiting_to_write>=1)
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
    }

    //if writers are favored
    else{
        if(thread_type == 0){ //thread_type==0 means it's a reading threads, else it's a writing one
        R_W->reading_threads--;
        if(R_W->reading_threads==0 && R_W->writing_threads>=1)
            pthread_cond_signal(&R_W->writer);
    }

    else{  //implementation which gives priority into a reading thread
        R_W->writing_threads--;
        if(R_W->waiting_to_write>=1)  
            pthread_cond_signal(&R_W->writer);
        else{
            pthread_cond_signal(&R_W->reader);
        }
    }

    }

    pthread_mutex_unlock(&R_W->mutex);
}



void*reading_lock(void* r_w_lock){ 
    reader_writer_lock* R_W = (reader_writer_lock*) r_w_lock;
    
    pthread_mutex_lock(&R_W->mutex);
    if(R_W->writing_threads>=1){
        R_W->waiting_to_read++;
        while(R_W->writing_threads>=1){
            pthread_cond_wait(&R_W->reader,&R_W->mutex);
    }
    R_W->waiting_to_read--;
    }
    R_W->reading_threads++;
    pthread_mutex_unlock(&R_W->mutex);
    unlocking(R_W,0);
    }


void* writing_lock(void* r_w_lock){
    reader_writer_lock* R_W = (reader_writer_lock*) r_w_lock;
    pthread_mutex_lock(&R_W->mutex);
    if(R_W->reading_threads>=1 || R_W->writing_threads >=1){
        R_W->waiting_to_write++;
        while(R_W->reading_threads>=1 || R_W->writing_threads >=1){
            pthread_cond_wait(&R_W->writer,&R_W->mutex);
        }
        R_W->waiting_to_write--;
    }
    R_W->writing_threads++;
    pthread_mutex_unlock(&R_W->mutex);
    unlocking(R_W,1);
}


void r_w_lock_init(reader_writer_lock* lock,int type_favored){
    pthread_cond_init(&lock->reader,NULL);
    pthread_cond_init(&lock->writer,NULL);
    pthread_mutex_init(&lock->mutex,NULL);    
    lock->reading_threads= 0 ;
    lock->waiting_to_write = 0;
    lock->waiting_to_read= 0 ;
    lock->writing_threads = 0;
    lock->type_favored=type_favored;
}

void destroy_lock(reader_writer_lock* lock) {
    pthread_mutex_destroy(&lock->mutex);
    pthread_cond_destroy(&lock->reader);
    pthread_cond_destroy(&lock->writer);
}