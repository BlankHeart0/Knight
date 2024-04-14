#!/bin/bash

for dir in */; do
    cd $dir

    for file in *.ks; do
        ~/Knight/bin/steed $file
    done

    cd ..
done
