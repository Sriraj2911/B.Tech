#! /bin/bash

isOdd=false
javaOut=""
testCaseNum=1
line=""

while read -r line; do
    if [ "$isOdd" = false ]; then
        javaOut=$(java -cp build MyInfArith $line)
        echo "Testcase $testCaseNum starting..."
        isOdd=true
        testCaseNum=$(($testCaseNum + 1))
    else
        if [ "$line" = "$javaOut" ]; then
            echo "Test case passed"
        else
            echo "Test case failed"
            echo "expected: $line"
            echo "got: $javaOut"
        fi
        isOdd=false
    fi
done < "./test.txt"

if [ "$line" = "$javaOut" ]; then
    echo "Test case passed"
else
    echo "Test case failed"
fi