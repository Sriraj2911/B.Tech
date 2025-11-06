#! /bin/bash

rename_file() {
	old_name="$1"
	new_name="$2"
	if [[ ! -e "$old_name" ]]; then
		echo "No file of name $old_name found"
		return 1
	else
		if [[ -z "$new_name" ]]; then
			extension="${old_name##*.}"
			if [[ "$old_name" == "$extension" ]]; then
				new_name="$(date +"%Y-%m-%d")"
			else
				new_name="$(date +"%Y-%m-%d").$extension" 
			fi
			mv "$old_name" "$(date +"%Y-%m-%d").$extension"
			echo -e  "Old name: $old_name.$extension\nNew name: $(date +"%Y-%m-%d").$extension"
		fi
	fi
	mv "$old_name" "$new_name"
	echo -e "Renamed successfully:\nOld name: $old_name\nNew name: $new_name"
}
