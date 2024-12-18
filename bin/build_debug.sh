#!/bin/sh

if [ -n "$1" ]
then
    TARGET="--target $1"
fi

cmake . --preset Debug
cmake --build --preset Debug $TARGET
