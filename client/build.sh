#!/bin/bash

if [ ! -d "./build" ]; then
    mkdir ./build
fi

if [ "$1" == "fclean" ]; then
    rm -rf ./build/* r-type_client
    exit 1
fi

if [ "$1" == "clean" ]; then
    rm -rf ./build/*
    exit 1
fi

if [ "$1" == "all" ]; then
    cd build || exit 1
    cmake ..

    if [ $? -eq 0 ]; then
        make
        mv r-type_client ./../
    else
        echo "CMake failed"
        exit -1
    fi
    rm -rf ./build/*
fi

if [ "$1" == "re" ]; then
    rm -rf ./build/* || exit 1
    cd build || exit 1
    cmake ..

    if [ $? -eq 0 ]; then
        make
    else
        echo "CMake failed"
        exit -1
    fi

    if [ -f "r-type_client" ]; then
        mv r-type_client ./../
    else
        echo "binary not found"
        exit -1
    fi
    rm -rf ./build/*
    exit 1
fi
