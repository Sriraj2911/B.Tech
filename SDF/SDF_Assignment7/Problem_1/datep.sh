#! /bin/bash

datep() {
	current_date=$(date)
	month=${current_date:4:3}
	date=${current_date:8:2}
	year=${current_date:27:4}
	str1="$month $date"
	echo "$str1 $year"
}
