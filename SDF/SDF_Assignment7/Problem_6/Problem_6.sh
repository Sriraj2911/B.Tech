#! /bin/bash

#editCSV(){
	sourceCSV="$1"
	modifiedCSV="$2"
	cp "$sourceCSV" "$modifiedCSV"
	while true; do
		echo "Choose an operation:"
		echo "1. Concatenate"
		echo "2. Sum"
		echo "3. Initials"
		echo "4. Bonus percentage"
		echo "5. Exit"
		read -p "Enter your choice: " choice
		tempCSV="temp_csv.csv"
		touch "$tempCSV"
		if [[ "$choice" == "1" ]]; then
			read -p "Enter column numbers to concat (comma-separated): " cols
			col1=$(echo "$cols" | awk -F, '{print $1}')
			col2=$(echo "$cols" | awk -F, '{print $2}')
			firstLine="0"
			while read -r curLine; do
				if [[ "$firstLine" -eq "0" ]]; then
					firstLine=$(("$firstLine"+1))
					echo ""$curLine","concat_"$col1"_"$col2""" >> "$tempCSV"
				else
					echo "$curLine" | awk -F, -v c1="$col1" -v c2="$col2" '{print $0, $c1 "_" $c2}' >> "$tempCSV"
				fi
			done < "$modifiedCSV"
	  		# awk -F',' -v c1="$c1" -v c2="$c2" 'NR==1 {print $0, "Full name"; next} NR>1 {print $0, $c1 " " $c2}' "$modifiedCSV" > "$tempCSV"

		elif [[ "$choice" == "2" ]]; then
			read -p "Enter the column numbers to sum (comma-separated): " cols
			col1=$(echo "$cols" | awk -F, '{print $1}')
			col2=$(echo "$cols" | awk -F, '{print $2}')
			firstLine="0"
			echo "$col1"
			while read -r curLine; do
				if [[ "$firstLine" -eq "0" ]]; then
					firstLine=$(($firstLine+1))
					echo "$curLine"
					echo "$curLine,add_${col1}_${col2}"
					echo "$curLine,add_${col1}_${col2}" >> "$tempCSV"
				else
					num1=$(echo "$curLine" | awk -F, -v c1="$col1" '{print $c1}')
					num2=$(echo "$curLine" | awk -F, -v c2="$col2" '{print $c2}')
					added=$(($num1+$num2))
					echo "$curLine" | awk -F, -v v1="$added" '{print $0 "," v1}' >> "$tempCSV"
				fi
			done < "$modifiedCSV"
			#awk -F',' -v c3="$c3" -v c4="$c4" 'NR==1 {print $0, "Total salary"; next} NR>1 {print $0, $c3+$c4}' "$modifiedCSV" > "$tempCSV"
		elif [[ "$choice" == "3" ]]; then
			read -p "Enter column numbers to get the initials for (comma-separated): " c5 c6
			awk -F',' -v c5="$c5" -v c6="$c6" 'NR==1 {print $0, "Initials"; next} NR>1 {print $0, substr($c5, 1, 1) "." substr($c6, 1, 1)}' "$modifiedCSV" > "$tempCSV"
		elif [[ "$choice" == "4" ]]; then
			read -p "Enter the column numbers to get the percentage for (comma-separated):" c7 c8
			awk -F',' -v c7="$c7" -v c8="$c8" 'NR==1 {print $0, "Bonus percentage"; next} NR>1 {print $0, ($c8*100)/$c7}' "$modifiedCSV" > "$tempCSV"
		elif [[ "$choice" == "5" ]]; then
			echo "Final output saved to $modifiedCSV"
			break
		else
			echo "Unrecognised choice"
		fi
		#rm "$modifiedCSV"
		#mv "$tempCSV" "$modifiedCSV"
	done
#}	
