#!/bin/bash

build_project() {
    project_dir=$1
    binary_name=$2

    if [ ! -d "./$project_dir/build" ]; then
        mkdir ./$project_dir/build
    fi

    cd ./$project_dir/build || exit 1
    cmake ..

    if [ $? -eq 0 ]; then
        make
        if [ -f "$binary_name" ]; then
            mv $binary_name ../../
        else
            echo "$binary_name binary not found"
            exit -1
        fi
    else
        echo "CMake failed"
        exit -1
    fi

    cd ../..
    rm -rf ./$project_dir/build/*
}

if [ "$#" -eq 0 ]; then
    echo "No arguments provided"
    echo "Usage: $0 [all|client|server|clean|fclean|re]"
    exit 1
fi

case "$1" in
    all)
        build_project "client" "r-type_client"
        build_project "server" "r-type_server"
        ;;
    client)
        build_project "client" "r-type_client"
        ;;
    server)
        build_project "server" "r-type_server"
        ;;
    clean)
        rm -rf ./client/build/* ./server/build/*
        rm -rf ./build/*
        ;;
    fclean)
        rm -rf ./client/build/* ./server/build/* r-type_client r-type_server
        rm -rf ./build/*
        ;;
    re)
        rm -rf ./client/build/* ./server/build/* r-type_client r-type_server
        build_project "client" "r-type_client"
        build_project "server" "r-type_server"
        ;;
    *)
        echo "Invalid argument: $1"
        echo "Usage: $0 [all|client|server|clean|fclean|re]"
        exit 1
        ;;
esac
