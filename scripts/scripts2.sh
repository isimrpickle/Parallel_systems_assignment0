#!/usr/bin/bash

echo -e "enter the thread count and the number of times each thread want to add to the global variable \n"

read thread_count thread_loop
/root/Parallel_systems_assignment0/output/exercise_1 $thread_count $thread_loop
