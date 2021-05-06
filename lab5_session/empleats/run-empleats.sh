#!/bin/bash

for i in 10000 50000 100000 200000 500000 1000000 2000000 5000000; do
    echo "${i}" >> empleats.numeros.txt
    perf stat -e cycles -o empleats.cycles.txt --append ./empleats.g3 $i > out.txt
done

cat empleats.cycles.txt | grep cycles | awk '{print $1}' > empleats.cycles.clean.txt

