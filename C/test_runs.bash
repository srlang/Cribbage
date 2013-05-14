#!/bin/bash

npt=10

echo "================================================="

for i in $(seq 1 $npt) ; do 
    echo "----------------------------------"
    echo "Runs Test $(i):"
    ./scorer_r <"test/runs_in$(i).txt" >"test/runs_aout$(i).txt"
    d=$(diff "test/runs_aout$(i).txt" "test/runs_eout$(i).txt")
    if [[ "x$d" == "x" ]] ; then
        echo "Passed"
    else
        echo "Failed:"
        echo "$d"
    fi
    echo "----------------------------------"
done

echo "================================================="

