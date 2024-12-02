#include "r_w_lock_functions.h"



// typedef struct r_w{
// pthread_mutex_t mutex;
// pthread_cond_t reader,writer;
// int reading_threads,waiting_to_read,writing_threads,waiting_to_write,type_favored;

// }reader_writer_lock; it's defined in the .h file, left it here for reference


void* unlocking(reader_writer_lock* R_W, int thread_type) {
    pthread_mutex_lock(&R_W->mutex);
    
    if (thread_type== 0) { // zero is for reading thread, (it was called by a reader)
        R_W->reading_threads--;
        //if all reader
        if (R_W->reading_threads == 0) {
            if (R_W->waiting_to_write> 0) {  
                if (R_W->type_favored== 1) // if writers preffered
                    pthread_cond_signal(&R_W-> writer);
                else if (R_W->waiting_to_read== 0) //if readers are preffered but there is no one waiting then still we signal a writer.
                    pthread_cond_signal(&R_W-> writer);
            }
        }
    }

    else { // unlocking was called  by a writer thread
        R_W->writing_threads--;
        
        // if it's readers favored and waiting readers exit then signal a reader, if no reader is waiting signal a writer if anyone waiting exists
        if (R_W->type_favored ==0) { // readers favored
            if (R_W->waiting_to_read >0)
                pthread_cond_broadcast(&R_W-> reader); //without waking every reader i was getting a deadlock.
            else if (R_W->waiting_to_write > 0)
                pthread_cond_signal(&R_W->writer);
        }
        //if it's writers favored check if there is any writer waiting and if it does signal writer, otherwise signal a reader
        else { // writers favored
            if (R_W->waiting_to_write >0)
                pthread_cond_signal(&R_W-> writer);
            else if (R_W->waiting_to_read > 0)
                pthread_cond_broadcast(&R_W-> reader);
        }
    }
    
    pthread_mutex_unlock(&R_W-> mutex);
    return NULL;
}

void* reading_lock(void* r_w_lock) {
    reader_writer_lock* R_W = (reader_writer_lock*) r_w_lock;
   
    pthread_mutex_lock(&R_W-> mutex);
    
    // if a writer is active or a writer is active we're waiting
    while (R_W->writing_threads > 0 || 
           (R_W->type_favored ==1 && R_W->waiting_to_write > 0)) {
        R_W->waiting_to_read++;
        pthread_cond_wait(&R_W-> reader, &R_W-> mutex);
        R_W->waiting_to_read--;
    }
    
    R_W->reading_threads++;
    pthread_mutex_unlock(&R_W->mutex);
    
}

void* writing_lock(void* r_w_lock) {
    reader_writer_lock* R_W =(reader_writer_lock*) r_w_lock;
    
    pthread_mutex_lock(&R_W->mutex);
    
    // Wait if readers are active or another writer is active
    while (R_W->reading_threads > 0 || R_W->writing_threads > 0 ||
           (R_W->type_favored == 0 && R_W->waiting_to_read > 0)) {
        R_W->waiting_to_write++;
        pthread_cond_wait(&R_W->writer, &R_W->mutex);
        R_W->waiting_to_write--;
    }
    
    R_W->writing_threads++;
    pthread_mutex_unlock(&R_W->mutex);
    
}

void r_w_lock_init(reader_writer_lock* lock, int type_favored) { //we pass the type we want to favor in this execution in the pth file
    pthread_cond_init(&lock->reader, NULL);
    pthread_cond_init(&lock->writer, NULL);
    pthread_mutex_init(&lock->mutex, NULL);    
    lock->reading_threads = 0;
    lock->waiting_to_write = 0;
    lock->waiting_to_read = 0;
    lock->writing_threads = 0;
    lock->type_favored = type_favored;
}

void destroy_lock(reader_writer_lock* lock) {
    pthread_mutex_destroy(&lock->mutex);
    pthread_cond_destroy(&lock->reader);
    pthread_cond_destroy(&lock->writer);
}