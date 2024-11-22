#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include "my_rand.h"
#pragma once


void parallel_Pi_calculation(const long int number_of_throws,int thread_count);
