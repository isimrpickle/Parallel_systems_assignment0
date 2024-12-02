#!/usr/bin/env bash
echo -e "Enter the priority: "
read priority

echo -e "Enter the inserts in main: "
read inserts_in_main

echo -e "Enter the total operations: "
read total_ops

echo -e "Enter the percentage of searches: "
read percentage_of_searches

echo -e "Enter the percentage of inserts: "
read percentage_of_inserts

for thread_count in  4 8 16 32; do
    for variable in 1 2 3 4; do
        /root/Parallel_systems_assignment0/output/pth_ll_rwl $thread_count $priority $total_ops $inserts_in_main  $percentage_of_searches $percentage_of_inserts
    done
done
