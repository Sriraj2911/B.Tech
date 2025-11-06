import subprocess
import sys

if len(sys.argv) != 5:
    print("Usage: python codeRunner.py <int/float> <add/sub/mul/div> <operand1> <operand2>")
    sys.exit(1)

type = sys.argv[1]
operation = sys.argv[2]
operand1 = sys.argv[3]
operand2 = sys.argv[4]

compile_result = subprocess.run(["javac", "-cp", "arbitraryarithmetic/aarithmetic.jar", "MyInfArith.java"], capture_output=True, text=True)
run_result = subprocess.run(["java", "-cp", ".:arbitraryarithmetic/aarithmetic.jar", "MyInfArith", type, operation, operand1, operand2], capture_output=True, text=True)

if run_result.returncode == 0:
    print(run_result.stdout, end="")
else:
    print("Error:", end="")
    print(run_result.stderr, end="")