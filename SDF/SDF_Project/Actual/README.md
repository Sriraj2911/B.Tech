## Arbitrary Precision Arithmetic Library

A Python tool for **exact calculations** with arbitrarily large integers and precise floating-point numbers. Performs high-precision addition, subtraction, multiplication, and division without rounding errors.

**Key Features**  
- Handles numbers beyond standard data type limits  
- Exact integer arithmetic (no size restrictions)  
- Precise floating-point division (configurable decimal places)  
- Command-line interface with error handling  

---

## Command-Line Usage

python MyInfArith.py {int|float} {add|sub|mul|div} <num1> <num2>


### Parameters

| Argument       | Description                                  | Valid Options                |
|----------------|----------------------------------------------|------------------------------|
| `{int\|float}` | Number type                                  | `int` or `float`             |
| `{operation}`  | Arithmetic operation                         | `add`, `sub`, `mul`, `div`   |
| `<num1>`       | First operand (positive/negative)            | Any valid number             |
| `<num2>`       | Second operand (positive/negative)           | Any valid number             |

**Help Command**  
python MyInfArith.py -h # or --help


---

## Error Handling

The script automatically detects and reports:
- Invalid number formats
- Division by zero attempts
- Operation/number-type mismatches
- Missing/extra arguments

**Note:** For floating-point division, results show full precision by default (no automatic rounding).

For a detailed description, see [Report.pdf](./Report.pdf).