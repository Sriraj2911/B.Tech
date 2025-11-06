#! /bin/bash

mkrandom() {
	number_files="$1"
	files_size="$2"
	if [[ -z "$number_files" || -z "$files_size" ]]; then
		echo "Usage : mkrandon <number_of_files> <size_of_each_file>"
		return 1
	fi

	for i in $(seq 1 $number_files); do
		head -c "$files_size" /dev/urandom | base64 > file_$i.txt
		echo "Created file_$i.txt with size $files_size bytes"
	done
}
