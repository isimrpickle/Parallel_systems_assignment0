#include "r_w_lock_functions.h"

void* unlocking(reader_writer_lock* R_W, int thread_type) {
    pthread_mutex_lock(&R_W->mutex);
    
    if (thread_type == 0) { // reading thread
        R_W->reading_threads--;
        
        // If no more readers and writers waiting, or if writers have priority
        if (R_W->reading_threads == 0) {
            if (R_W->waiting_to_write > 0) {
                if (R_W->type_favored == 1) // writers favored
                    pthread_cond_signal(&R_W->writer);
                else if (R_W->waiting_to_read == 0) 
                    pthread_cond_signal(&R_W->writer);
            }
        }
    }
    else { // writing thread
        R_W->writing_threads--;
        
        // Decide who to wake based on priority
        if (R_W->type_favored == 0) { // readers favored
            if (R_W->waiting_to_read > 0)
                pthread_cond_broadcast(&R_W->reader);
            else if (R_W->waiting_to_write > 0)
                pthread_cond_signal(&R_W->writer);
        }
        else { // writers favored
            if (R_W->waiting_to_write > 0)
                pthread_cond_signal(&R_W->writer);
            else if (R_W->waiting_to_read > 0)
                pthread_cond_broadcast(&R_W->reader);
        }
    }
    
    pthread_mutex_unlock(&R_W->mutex);
    return NULL;
}

void* reading_lock(void* r_w_lock) {
    reader_writer_lock* R_W = (reader_writer_lock*) r_w_lock;
   
    pthread_mutex_lock(&R_W->mutex);
    
    // Wait if writer is active or writers are favored and waiting
    while (R_W->writing_threads > 0 || 
           (R_W->type_favored == 1 && R_W->waiting_to_write > 0)) {
        R_W->waiting_to_read++;
        pthread_cond_wait(&R_W->reader, &R_W->mutex);
        R_W->waiting_to_read--;
    }
    
    R_W->reading_threads++;
    pthread_mutex_unlock(&R_W->mutex);
    
    return NULL;
}

void* writing_lock(void* r_w_lock) {
    reader_writer_lock* R_W = (reader_writer_lock*) r_w_lock;
    
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
    
    return NULL;
}

void r_w_lock_init(reader_writer_lock* lock, int type_favored) {
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