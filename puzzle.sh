#!/bin/bash
LENGTH=$1
HEIGHT=$2

if [ ! -f "./puzzle.out" ]
then
    echo "File $FILE does not exists, compiling it now!"
    gcc puzzle.c -std=c99 -o puzzle.out
fi

./puzzle.out $LENGTH $HEIGHT | R -e "data <- read.csv(file=\"stdin\",head=TRUE,sep=\",\"); x11(); attach(data); par(mfrow=c(2,1)); plot(pieces_remaining,total_attempts); hist(attempts); locator(1);"
