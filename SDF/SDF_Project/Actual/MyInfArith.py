# for command-line arguments
import argparse
# for automating Java library with Python
import jpype
import jpype.imports
from jpype.types import *

# start JVM
jpype.startJVM(classpath=['/home/sanctorex/Programming/SDF_Project/Actual/build/aarithmetic.jar'])


# import the two classes
AInteger = jpype.JClass('arbitraryarithmetic.AInteger')
AFloat = jpype.JClass('arbitraryarithmetic.AFloat')

# a function to check if a string has any alphabets
def check_alpha(s):
    return any(char.isalpha() for char in s)

def main():
    parser = argparse.ArgumentParser(description="Aribitrary precision arithmetic.")
    
    # add arguments
    parser.add_argument("data_type", type = str, choices=["int", "float"], help="Specify the data type of the numbers")
    parser.add_argument("operator", type = str, choices=["add", "sub", "mul", "div"], help="Operator (+, -, *, /)")
    parser.add_argument("num1", type=str, help="First operand")
    parser.add_argument("num2", type=str, help="Second operand")

    # parse the arguments added above
    args = parser.parse_args()

    # check the validity of the operands entered
    if(check_alpha(args.num1) or check_alpha(args.num2)):
        print("Error: Invalid operands entered. Operands should be numeric.")
        sys.exit(1)
    dec_count1 = args.num1.count('.')
    dec_count2 = args.num2.count('.')
    if(dec_count1>1 or dec_count2>1):
        print("Error: Invalid operands entered. Only one decimal point is allowed.")
        sys.exit(1)
    minus_count1 = args.num1.count('-')
    minus_count2 = args.num2.count('-')
    if(minus_count1>1 or minus_count2>1):
        print("Error: Invalid operands entered. Only one negative sign is allowed.")
        sys.exit(1)

    # remove leading '+', if any
    if(args.num1[0]=='+'):
        args.num1 = args.num1[1:]
    if(args.num2[0]=='+'):
        args.num2 = args.num2[1:]

    try:
        if args.data_type == "int":
            n1 = AInteger(args.num1)
            n2 = AInteger(args.num2)
        else:
            n1 = AFloat(args.num1)
            n2 = AFloat(args.num2)
        
        if args.operator == "add":
            result = n1.add(n2)
        elif args.operator == "sub":
            result = n1.sub(n2)
        elif args.operator == "mul":
            result = n1.mul(n2)
        else:
            result = n1.div(n2)
        
        # Print the result
        print(result.return_string())

    except Exception as e:
        print(f"Error: {str(e)}")
        sys.exit(1)
    
    # shutdown JVM when down
    jpype.shutdownJVM()



if __name__ == "__main__":
    main()
