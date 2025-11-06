#! /bin/bash

spellcheck() {
    if [[ $# -eq 0 ]]; then
        echo "Usage: spellcheck filename"
        return 1
    fi

    filename="spellcheck.spelling"

    if [[ ! -f "$filename" ]]; then
        echo "Creating file $filename"
        touch "$filename"
    else
        echo "Deleting the existing file and replacing it"
        > "$filename"
    fi

    for arg in "$@"; do
        count=0
        if [[ ! -f "$arg" ]]; then
            echo "Invalid argument $arg. Skipping it"
            continue
        fi
        IFS=' '
        while read -r -a terms; do
            for term in "${terms[@]}"; do
                if ! grep -q -w "$term" word; then
                    echo "$term" >> "$filename"
                    ((count++))
                fi
            done
        done < "$arg"
        
        echo "@arg completed"
        echo "Found $count unique words"
    done
}
