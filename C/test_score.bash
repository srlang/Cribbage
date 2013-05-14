#!/bin/bash

npt=10

echo "================================================="

for i in $(seq 1 $npt) ; do 
    echo "----------------------------------"
    echo "Score() Test $(i):"
    ./scorer_p <"test/score_in$(i).txt" >"test/score_aout$(i).txt"
    d=$(diff "test/score_aout$(i).txt" "test/score_eout$(i).txt")
    if [[ "x$d" == "x" ]] ; then
        echo "Passed"
    else
        echo "Failed:"
        echo "$d"
    fi
    echo "----------------------------------"
done

echo "================================================="

