#!/bin/bash

npt=10

echo "================================================="

for i in $(seq 1 $npt) ; do 
    echo "----------------------------------"
    echo "Pair Test $(i):"
    ./scorer_p <"test/pair_in$(i).txt" >"test/pair_aout$(i).txt"
    d=$(diff "test/pair_aout$(i).txt" "test/pair_eout$(i).txt")
    if [[ "x$d" == "x" ]] ; then
        echo "Passed"
    else
        echo "Failed:"
        echo "$d"
    fi
    echo "----------------------------------"
done

echo "================================================="

