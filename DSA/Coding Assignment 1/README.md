# 1. Linked List Odd-Even Node Reordering

## Description
This program reads a sequence of integers into a singly linked list and rearranges nodes such that all nodes at odd indices appear before those at even indices. The original relative order within odd and even indexed nodes is preserved.

## Output
The final sequence for integers are printing, separated by a comma

## Compilation
Use `gcc -o problem1 problem1.c` to compile.

## Usage
Run the compiled code and input up to 1000 integers separated by commas. Input ends if -1 is encountered.

Example input:
`1,2,3,4,5,-1`

Expected output:
`1, 3, 5, 2, 4,`

## Dependencies
Standard C library, stdlib.h for malloc

# 2. XOR Linked List with Search, Insert, Delete, and Reverse Operations

## Description
Implementation of an XOR linked list using uintptr_t (to ensure valid XORing of addresses) to store XOR of next and previous node addresses, supporting the following:
- Insertion at the start
- Searching for an element
- Deletion of an element
- Reversing the list

## Features
- Memory efficient doubly linked list
- Efficient reversal of the linked list, in O(1) time

## Compilation
Compile with `gcc -o problem2 problem2.c`.

## Usage
Input the number of operations followed by operation codes and values (where applicable).
Operations:
- 1: Insert
- 2: Search
- 3: Delete
- 4: Reverse list

## Dependencies
Standard C library, stdlib.h for malloc, and stdint.h for uintptr_t

# 3. Infix to Postfix Expression Converter Using Manually implemented Stacks

## Description
This program converts an input infix expression to its postfix form using a doubly linked list implemented as a stack.

## Features
- Supports operators: ^ ; / ; * ; + ; - (Precedence in the same order)
- Handles parentheses properly

## Compilation
Compile with `gcc -o problem3 problem3.c`

## Usage
Input the number of expressions, say n, followed by 'n' infix expressions

## Dependencies
Standard C library and string.h for strlen()

# 4. Two-Level Perfect Hash Table for Efficient Person Lookup

## Description
This program builds a two-level perfect hash table for efficient storage and retrieval of person records loaded from a CSV file. Uses universal hashing to minimize collisions.

## Features
- Reads person data from CSV file (Dictionary Data.csv)
- Builds first and second-level hash tables
- Supports fast lookup by person key, in O(1) time
- Ensures no collisions
- Avoids infinite loops by fixing a ceiling for number of iterations

## Compilation
Compile using `gcc -o problem4 problem4.c -lm` (math library may be needed depending on implementation).

## Usage
Ensure the CSV file "Dictionary Data.csv" is in the same directory.
Run the program and input keys to search; input -1 to quit.

## Dependencies
Standard C library, time.h for random seed, string.h for strcpy() for reading the CSV file, stdlib.h for malloc, calloc and free

# 5. Sorted Stack Using Singly Linked List

## Description
This program implements a stack using a singly linked list and supports sorting of the stack elements in ascending order (highest number at the top of the stack) using recursion.

## Features
- Recursive sorting algorithm that sorts the stack in-place

## Compilation
Compile with `gcc -o problem5 problem5.c`.

## Usage
Input the number of elements followed by the elements.

## Dependencies
Standard C library and stdlib.h for malloc

# 6.Doubly Linked List Stack with Middle Element Operations

## Description
Implementation of a stack with a doubly linked list supporting:
- Push, Pop
- Find Middle Element
- Delete Middle Element

Handles list properties such that head->prev points to tail and tail->next points to the middle element. This is done to avoid traversal of list to get tail or middle nodes.

## Features
- Efficient middle element operations, performed in O(1) time
- Doubly linked list with custom pointer links

## Compilation
Compile using `gcc -o problem6 problem6.c`.

## Usage
Input the number of operations.
Follow each operation with the relevant input if any.
Supported operations: Push, Pop, FindMiddle, DeleteMiddle.
- 1 a : Push a onto the stack
- 2: Pop the top element of the stack
- 3: Find the middle element of the stack
    - Returns the first element of the middle pair if the number of elements is even
- 4: Delete the middle element from the stack

## Dependencies
Standard C library and stdlib.h for malloc






