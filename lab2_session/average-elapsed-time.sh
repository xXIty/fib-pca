#!/bin/bash


N=$1
SUM=0

for i in {1..$N} do
	A=$(/usr/bin/time -f "%e" ${@:2})
	SUM=$SUM+$A

done

RESULT=$SUM/$N
echo $RESULT
