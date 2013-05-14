#!/bin/bash

npt=10

echo "================================================="

for i in $(seq 1 $npt) ; do 
    echo "----------------------------------"
    echo "Right Jack Test $(i):"
    ./scorer_p <"test/rj_in$(i).txt" >"test/rj_aout$(i).txt"
    d=$(diff "test/rj_aout$(i).txt" "test/rj_eout$(i).txt")
    if [[ "x$d" == "x" ]] ; then
        echo "Passed"
    else
        echo "Failed:"
        echo "$d"
    fi
    echo "----------------------------------"
done

echo "================================================="

