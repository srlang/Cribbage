#!/bin/bash

npt=10

echo "================================================="

for i in $(seq 1 $npt) ; do 
    echo "----------------------------------"
    echo "Score() Test $(i):"
    ../scorer_s <"score_in$(i).txt" >"score_aout$(i).txt"
    d=$(diff "score_aout$(i).txt" "score_eout$(i).txt")
    if [[ "x$d" == "x" ]] ; then
        echo "Passed"
    else
        echo "Failed:"
        echo "$d"
    fi
    echo "----------------------------------"
done

echo "================================================="

