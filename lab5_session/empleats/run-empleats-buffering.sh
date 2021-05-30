#!/bin/bash

echo -n > empleats.numeros.txt
echo -n > empleats.cycles.txt

[[ $# -ne 1 ]] && echo 'Usage: ./run-empleats.sh <binari>' && exit

for (( i=2; i <= 50; i+=1 ))
do
  echo $i
  echo "${i}" >> empleats.numeros.txt
  perf stat -e cycles -o empleats.cycles.txt --append $1 1000000 $i > out.txt
done

cat empleats.cycles.txt | grep cycles | awk '{print $1}' > empleats.cycles.clean.txt

