#! /bin/bash

new() {
	name="$1"
	number="$2"
	echo "$name $number" >> phonebook.txt
}

list() {
	if [[ ! -s phonebook.txt ]]; then
		echo "The phonebook is empty"
	fi
	cat phonebook.txt
}

remove() {
	name="$1"
	sed -i '/"$name"/d' phonebook.txt
}

clear() {
	truncate -s 0 phonebook.txt
}

lookup() {
	name="$1"
	grep "$name" phonebook.txt
}



