#!/bin/sh

if [ -n "$1" ]
then
    TARGET="--target $1"
fi

cmake --build --preset release -j 8 $TARGET
