#! /bin/bash

findwords() {
	search_word="$1"
	filename="${2:-words}"

	if [ ! -f "$filename" ]; then
		echo "Error: File '$filename' not found" > /dev/null
		return 1
	fi

	count=0
	output=""

	while read -r line; do
		for word in $line; do
			if echo "$word" | grep -qi "$search_word"; then
				output+="$word "
				(( count++ ))
				if (( count%4 == 0 )); then
					awk -F " " '{printf "%-15s\t%-15s\t%-15s\t%-15s\n", $1, $2, $3, $4}' <<< "$output"
					output=""
				fi
			fi
		done
	done < "$filename"
}
