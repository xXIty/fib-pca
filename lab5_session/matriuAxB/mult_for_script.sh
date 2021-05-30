#!/bin/bash

for b in 2 4 8 16 32 64 128 256; do
  echo "BS=$b"
  gcc -DBS=$b -O3 -fno-inline -o mult1_blocking_A.g3.$b mult1_blocking_A.c
  perf stat -d -d -r3 ./mult1_blocking_A.g3.$b >/dev/null
done

gcc -O3 -fno-inline -o mult1_noblocking.g3 mult1_noblocking.c
perf stat -d -d -r3 ./mult1_noblocking.g3 >/dev/null
