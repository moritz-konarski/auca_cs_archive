#!/bin/bash

cd "./$1/"
if [[ -d "./build/" ]]
then
    cd "./build/"
    rm -rf *
    cmake ..
    make
    cd ..
else
    echo "ERROR: directory build does not exist"
fi
cd ..
