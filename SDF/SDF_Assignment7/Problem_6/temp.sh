#! /usr/bin/bash

file="$1"
modified="modified.csv"
touch "$modified"
cp "$file" "$modified"
while true; do
	echo '1. add'
	echo '2. exit'
	read -p "enter: " choice
	if [[ "$choice" -eq "1" ]]; then
		read -p "cols: " cols
		col1=$(echo "$cols" | awk -F, '{print $1}')
		col2=$(echo "$cols" | awk -F, '{print $2}')
		echo "$col2"
		temp="temp_csv.csv"
		touch "$temp"
		lineno="0"
		while read -r line; do
			if [[ "$lineno" -eq 0 ]]; then
				lineno=1
				echo "$line,add_"$col1"_"$col2"" >> "$temp"
			else
				num1=$(echo "$line" | awk -F, -v col="$col1" '{print $col}')
				num2=$(echo "$line" | awk -F, -v col="$col2" '{print $col}')
				add=$(($num1+$num2))
				echo ""$line","$add"" >> "$temp"
			fi	
		done < "$modified"
		cat "$temp"
	else
		break
	fi
done
