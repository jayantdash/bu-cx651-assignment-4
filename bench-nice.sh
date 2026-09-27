#!/bin/bash


echo $(date)
echo "starting matrix multiply"

mkdir -p data/bench-nice

for i in $(seq 100 100 100)
do
    /usr/bin/time -f "CPU: %P\n" -o data/bench-nice/mm-${i}-cpu.out nice -n 10 ./bench ${i} ${i} ${i} 0 > data/bench-nice/mm-${i}.out 
    pids[${i}]=$!
    echo $(date)
done

echo "waiting for multiplies"
# wait for all pids
for pid in ${pids[*]}; do
    wait $pid
done
echo $(date)

echo $(ps)

#kill $monitor
