#!/bin/bash

for i in {1..640}; do 
    echo -n "count=${i}00 "; 
    command="./swap.pca ${i}00 >/dev/null < $1"
    perf stat -r 3 sh -c "${command}" 2>&1 | awk '/time elapsed/ {print $1}' | column -t 
done 
