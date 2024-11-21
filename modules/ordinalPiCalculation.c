#include "OrdinalPicalculation.h"

//function to generate a  random double number from the range of max-min(1-(-1))
//based on https://stackoverflow.com/questions/33058848/generate-a-random-double-between-1-and-1
double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


void ordinal_Pi_calculation(const long int number_of_throws){
    long int cicrle_arrows=0;
    for(long int i=0;i<number_of_throws;i++){
        double x = randfrom(1.0,-1.0);
        double y = randfrom(1.0,-1.0);
        double squared_distance = x*x + y*y;
        if(squared_distance <= 1)
            cicrle_arrows++;
    }
    double Pi_approximation=4*cicrle_arrows/((double)number_of_throws);
    printf("pi is %f \n",Pi_approximation);
}



