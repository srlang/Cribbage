#!/bin/bash

npt=10

echo "================================================="

for i in $(seq 1 $npt) ; do 
    echo "----------------------------------"
    echo "Fifteens Test $(i):"
    ./scorer_f <"test/fif_in$(i).txt" >"test/fif_aout$(i).txt"
    d=$(diff "test/fif_aout$(i).txt" "test/fif_eout$(i).txt")
    if [[ "x$d" == "x" ]] ; then
        echo "Passed"
    else
        echo "Failed:"
        echo "$d"
    fi
    echo "----------------------------------"
done

echo "================================================="

