
#include "OrdinalPicalculation.h"
#include "ParallelPiCalculation.h"

int main(int argc,char** argv){
    long long int number_of_throws;
    int number_of_threads;
    if(argc>1){
        number_of_throws=atoll(argv[1]);
        number_of_threads=atoi(argv[2]);

    }
    else{
        number_of_throws=100000000;
        number_of_threads=4;
    }

    printf("the number of throws are %lld and the threads are %d \n", number_of_throws , number_of_threads);
    printf("The results of oridnal calculation are: \n");
    ordinal_Pi_calculation(number_of_throws);
    printf("The results of parallel calculation are: \n");
    parallel_Pi_calculation(number_of_throws,number_of_threads);
    printf("\n  \n ");


}