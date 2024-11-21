#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_rand.h"
#pragma once


struct parameters{
    long int number_of_throws;
    long int thread_count;
    short int rank;
};

void parallel_Pi_calculation(const long int number_of_throws,int thread_count);
