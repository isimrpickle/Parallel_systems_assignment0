#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_rand.h"
#include "OrdinalPicalculation.h"
#include "ParallelPiCalculation.h"

int main(){
    long int number_of_throws=10000;
    printf("the number of throws are %ld \n", number_of_throws);
    ordinal_Pi_calculation(number_of_throws);
    int number_of_threads=4;
    parallel_Pi_calculation(number_of_throws,number_of_threads);
}