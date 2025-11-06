#! /bin/bash

combine() {
    if [[ $# -lt 2 ]]; then
        echo "Usage: combine outputfilename [inputfilename ...]"
        return 1
    fi

    if [[ -f "$1" ]]; then
        echo "Error: Output file should not exist"
        return 1
    fi

    touch "$1"
    output_file="$1"
    shift

    cat "$@" >> "$output_file"

}