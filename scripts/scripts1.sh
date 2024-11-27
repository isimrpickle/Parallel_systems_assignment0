#!/usr/bin/bash

echo -e "Enter the number of throws you want for exercise 1:\n"

read number_of_throws 

for thread_number in 1 2 4 8 16 32; do
    for iteration in 1 2 3 4; do
        /root/Parallel_systems_assignment0/output/exercise_1 $number_of_throws $thread_number
    done
done
