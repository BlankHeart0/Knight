#!/bin/bash

for dir in */; do
    cd $dir

    for file in *.k; do
        ~/Knight/bin/trial $file
    done

    cd ..
done
