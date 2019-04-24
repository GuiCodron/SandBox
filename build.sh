#!/bin/bash
_BUILD_SH_DIR=$(greadlink -f $(dirname ${BASH_SOURCE[0]}))

BUILD_DIR="$_BUILD_SH_DIR"/build

parse_args() {
    export opt_build opt_clean
    opt_build=1
    [ $# != 0 ] && opt_build=
    while [ $# != 0 ]; do
        case "$1" in
        -c | --clean) opt_clean=1 ;;
        -b | --build) opt_build=1 ;;
        esac
        shift
    done
}

build() {
    echo "Running build!"
    export CC=gcc
    export CXX=g++
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake ..
    make
}

clean() {
    echo "Cleaning all"
    make -C "$BUILD_DIR" clean
}

main() {
    parse_args "$@"
    [ "$opt_build" ] && build
    [ "$opt_clean" ] && clean
}

main "$@"
