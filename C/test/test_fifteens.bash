#!/bin/bash

npt=10

echo "================================================="

for i in $(seq 1 $npt) ; do 
    echo "----------------------------------"
    echo "Fifteens Test $i:"
    ../scorer_f <"fif_in$i.txt" >"fif_aout$i.txt"
    d=$(diff "fif_aout$i.txt" "fif_eout$i.txt")
    if [[ "x$d" == "x" ]] ; then
        echo "Passed"
    else
        echo "Failed:"
        echo "$d"
    fi
    echo "----------------------------------"
done

echo "================================================="

