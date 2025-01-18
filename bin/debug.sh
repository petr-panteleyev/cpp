#!/bin/sh

if [ -n "$1" ]
then
    TARGET="--target $1"
fi

cmake --build --preset debug -j 8 $TARGET
