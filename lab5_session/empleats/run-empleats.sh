#!/bin/bash

echo -n > empleats.numeros.txt
echo -n > empleats.cycles.txt

[[ $# -ne 1 ]] && echo 'Usage: ./run-empleats.sh <binari>' && exit

for i in 10000 50000 100000 200000 500000 1000000 2000000 5000000; do
    echo "${i}" >> empleats.numeros.txt
    perf stat -e cycles -o empleats.cycles.txt --append $1 $i > out.txt
done

cat empleats.cycles.txt | grep cycles | awk '{print $1}' > empleats.cycles.clean.txt

