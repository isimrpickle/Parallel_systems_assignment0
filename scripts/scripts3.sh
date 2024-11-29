#!/bin/bash

echo -e "enter the number of times each thread want to add to the global variable \n"


read  thread_loop
for thread_count in 1 2 4 8 16 32; do
    for variable in 1 2 3 4; do
        /root/Parallel_systems_assignment0/output/exercise_3 $thread_count $thread_loop
    done
done
