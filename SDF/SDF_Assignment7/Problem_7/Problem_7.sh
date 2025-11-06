#! /bin/bash

FillRows() {
	CSVfile="$1"
	column="$2"
	number_of_rows="$3"
	val1=$(awk -F',' -v col="$column" 'NR==1 {print $col}' "$CSVfile")
	val2=$(awk -F',' -v col="$column" 'NR==2 {print $col}' "$CSVfile")
	val3=$(awk -F',' -v col="$column" 'NR==3 {print $col}' "$CSVfile")
	if (( val3-val2 == val2-val1 )); then
		d=$(( val3-val2 ))
		declare -A val
		val[1]=$val1
		val[2]=$val2
		val[3]=$val3
		NF=$(awk -F',' '{print NF; ext}' "$CSVfile")

		for(( row=4; row<4+number_of_rows; row++)); do
			new_value=$(( val3 + (row-3) * d ))
			new_row=$(awk -F',' -v col="$column" -v val="$new_value" -v nf="$NF" 'BEGIN {
				for (i=1; i<col; i++) printf ",";
				printf "%s", val;
				for (i=col+1; i<nf; i++) printf ",";
				print "";
			}')

			echo "$new_row" >> "$CSVfile"
		done
	else
		echo -1
	fi
}
