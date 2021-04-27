#!/bin/bash

usage() {
  cat <<EOF
Usage: paraevaluar.sh optimized_program N [--original original_program] [[args], args..]

Executes optimized_program N times and displays maximum, minimum and average elapsed time and CPU utilisation time.
If given the original program, gives the same information for the original program, obtains a golden output and checks its correctness.

Available options:

--original original_program      Original program to check golden output and calculate speedup

EOF
  exit
}

ORIGINAL_EX=""
OPTIMIZED_EX=""
ORIG_GIVEN=0
ARGS=""

[[ $# -lt 2 ]] && usage


if [ "$3" = "--original" ]
then
    ORIG_GIVEN=1
    ORIGINAL=$4
    ARGS=${@:5}
else
    ARGS=${@:3}
fi


N=$2
RAW_OUTPUT=""

echo "Running executable ${1} with arguments \"${ARGS}\"  ${N} times:"

for i in $(seq 1 $N); do
    echo "Run number ${i}"
    RAW_OUTPUT+=$(/usr/bin/time -f "%e %U %S" ${1} ${ARGS} 2>&1>/dev/null)
    if [[ $i -ne $N ]]; then RAW_OUTPUT+="\n"; fi;

done

#LIST_ELAPSED=$(echo -e $RAW_OUTPUT | awk 'BEGIN{sum=0.0} {printf("%f %f\n", $1, $2+$3); sum+=$1} END{printf("Avg: %f\n", sum/NR)}')

#LIST_ELAPSED="$(echo -e $RAW_OUTPUT | cut -d ' ' -f 1)"
#LIST_ELAPSED=$(echo -e $RAW_OUTPUT | awk '{printf("%f\n", $1)}')
#echo -e $RAW_OUTPUT | cut -d " " -f 1
#echo -e $RAW_OUTPUT | awk '{printf("%f\n", $1)}'
#LIST_CPU=$(echo -e $RAW_OUTPUT | awk '{printf("%f\n", $2+$3)}')

#echo -e $LIST_ELAPSED

AVG_ELAPSED=$(echo -e $RAW_OUTPUT | awk 'BEGIN{sum=0.0} {sum+=$1} END{printf("%f\n", sum/NR)}')
AVG_CPU=$(echo -e $RAW_OUTPUT | awk 'BEGIN{sum=0.0} {sum+=($2+$3)} END{printf("%f\n", sum/NR)}')


MAX_ELAPSED=$(echo -e $RAW_OUTPUT | awk '{printf("%f\n", $1)}' | sort -g | tail -n 1)
MIN_ELAPSED=$(echo -e $RAW_OUTPUT | awk '{printf("%f\n", $1)}' | sort -g | head -n 1)

MAX_CPU=$(echo -e $RAW_OUTPUT | awk '{printf("%f\n", $2+$3)}' | sort -g | tail -n 1)
MIN_CPU=$(echo -e $RAW_OUTPUT | awk '{printf("%f\n", $2+$3)}' | sort -g | head -n 1)

echo ""
## We do the same for original code if given

echo "Running executable ${ORIGINAL} with arguments \"${ARGS}\" ${N} times:"

if [[ $ORIG_GIVEN -eq 1 ]] 
then

for i in $(seq 1 $N); do
    echo "Run number ${i}"
    ORIG_RAW_OUTPUT+=$(/usr/bin/time -f "%e %U %S" ${ORIGINAL} ${ARGS} 2>&1>/dev/null)
    if [[ $i -ne $N ]]; then ORIG_RAW_OUTPUT+="\n"; fi;

done

#LIST_ELAPSED=$(echo -e $ORIG_RAW_OUTPUT | awk 'BEGIN{sum=0.0} {printf("%f %f\n", $1, $2+$3); sum+=$1} END{printf("Avg: %f\n", sum/NR)}')

#LIST_ELAPSED="$(echo -e $ORIG_RAW_OUTPUT | cut -d ' ' -f 1)"
#LIST_ELAPSED=$(echo -e $ORIG_RAW_OUTPUT | awk '{printf("%f\n", $1)}')
#echo -e $ORIG_RAW_OUTPUT | cut -d " " -f 1
#echo -e $ORIG_RAW_OUTPUT | awk '{printf("%f\n", $1)}'
#LIST_CPU=$(echo -e $ORIG_RAW_OUTPUT | awk '{printf("%f\n", $2+$3)}')

#echo -e $LIST_ELAPSED

ORIG_AVG_ELAPSED=$(echo -e $ORIG_RAW_OUTPUT | awk 'BEGIN{sum=0.0} {sum+=$1} END{printf("%f\n", sum/NR)}')
ORIG_AVG_CPU=$(echo -e $ORIG_RAW_OUTPUT | awk 'BEGIN{sum=0.0} {sum+=($2+$3)} END{printf("%f\n", sum/NR)}')


ORIG_MAX_ELAPSED=$(echo -e $ORIG_RAW_OUTPUT | awk '{printf("%f\n", $1)}' | sort -g | tail -n 1)
ORIG_MIN_ELAPSED=$(echo -e $ORIG_RAW_OUTPUT | awk '{printf("%f\n", $1)}' | sort -g | head -n 1)

ORIG_MAX_CPU=$(echo -e $ORIG_RAW_OUTPUT | awk '{printf("%f\n", $2+$3)}' | sort -g | tail -n 1)
ORIG_MIN_CPU=$(echo -e $ORIG_RAW_OUTPUT | awk '{printf("%f\n", $2+$3)}' | sort -g | head -n 1)

ELAPSED_SPEEDUP=$(echo "scale=3;$ORIG_AVG_ELAPSED/$AVG_ELAPSED" | bc -q -l)
CPU_SPEEDUP=$( echo "scale=3;$ORIG_AVG_CPU/$AVG_CPU" | bc -q -l)

echo ""

GOLDEN_TMP_FILE=$(mktemp)
OPTIMIZED_TMP_FILE=$(mktemp)

$ORIGINAL $ARGS > $GOLDEN_TMP_FILE
${1} $ARGS > $OPTIMIZED_TMP_FILE
diff $GOLDEN_TMP_FILE $OPTIMIZED_TMP_FILE > /dev/null
if [[ $? -eq 0 ]]
then
    echo "Output of optimized version is the same as the golden output"
else
    echo "Output of optimized version is different than the golden output! Please check the correctness of your optimization."
fi

rm $GOLDEN_TMP_FILE
rm $OPTIMIZED_TMP_FILE

fi
echo ""



## MOSTREM ELS RESULTATS FINALS

echo "Execution times for optimized code:"
echo "CPU      ->   Min: ${MIN_CPU} Max: ${MAX_CPU} Average: ${AVG_CPU}"
echo "Elapsed  ->   Min: ${MIN_ELAPSED} Max: ${MAX_ELAPSED} Average: ${AVG_ELAPSED}"

echo ""

if [[ $ORIG_GIVEN -eq 1 ]] 
then
echo "Execution times for original code:"
echo "CPU      ->   Min: ${ORIG_MIN_CPU} Max: ${ORIG_MAX_CPU} Average: ${ORIG_AVG_CPU}"
echo "Elapsed  ->   Min: ${ORIG_MIN_ELAPSED} Max: ${ORIG_MAX_ELAPSED} Average: ${ORIG_AVG_ELAPSED}"
echo ""

echo "Speedup of elapsed time: ${ELAPSED_SPEEDUP}x"
echo "Speedup of CPU time:     ${CPU_SPEEDUP}x"

fi
