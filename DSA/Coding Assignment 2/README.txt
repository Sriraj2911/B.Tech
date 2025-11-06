# Problem1.c

## Description
Constructs a binary tree from a given array representation of level order traversal, where missing nodes are indicated by "NULL"/"null". It outputs the inorder, preorder, and postorder traversals.

## Input
- First line: Number of test cases n
- Following k lines: Space-separated values for nodes data (use "null"/"NULL" for empty nodes)

## Output
- Prints inorder, preorder, and postorder traversals for each testcase

## Usage
1. Compile: `gcc -o Problem1 Problem1.c`
2. Run: `./Problem1` and provide the input as prompted

Example input:  
2  
1 2 3 4 5 6 7  
1 2 3 4 5 NULL 6  

Expected output:  
4 2 5 1 6 3 7  
1 2 4 5 3 6 7  
4 5 2 6 7 3 1  
4 2 5 1 3 6  
1 2 4 5 3 6  
4 5 2 6 3 1  

## Dependencies
- Standard C library
- stdlib.h
- string.h

# Problem2.c

## Description
Reconstructs a binary tree from given inorder and preorder traversals, then prints its level-order traversal.

## Input
- Line-1: Number of test cases n
- Line-(2i-1): Inorder sequence for the test case i
- Line-(2i): Preorder sequence for the test case i

## Output
- Prints the level-order traversal of the constructed tree

## Usage
1. Compile: `gcc -o Problem2 Problem2.c`
2. Run: `./Problem2` and enter the traversals as prompted

Example input:  
2  
1 2 3 4 5 6 7  
1 2 3 4 5 NULL 6  

Expected output:  
% Traversal for test case 1 %  
4 2 5 1 6 3 7  
1 2 4 5 3 6 7  
4 5 2 6 7 3 1  
% Traversal for test case 2 %  
4 2 5 1 3 6  
1 2 4 5 3 6  
4 5 2 6 3 1  

## Dependencies
- Standard C library
- stdlib.h
- string.h

# Problem3.c

## Description
Given inorder and preorder traversals, reconstructs a binary tree, then finds the most frequent distance between any two nodes in the tree. 

## Input
- First line: Number of nodes 
- Next line: Preorder traversal (space-separated)
- Next line: Inorder traversal (space-separated)

## Output
- Prints the most frequent distance. In case of a tie between the frequency of two distances, the lower of the two is printed.

## Usage
1. Compile: `gcc -o Problem3 Problem3.c`
2. Run: `./Problem3` and enter the traversals as prompted

Example input:  
5  
1 2 4 5 3  
4 2 5 1 3 

Expected output:  
1 

## Dependencies
- Standard C library
- stdlib.h
- string.h

# Problem4.c

## Description
This program constructs a binary tree based on user input and calculates the length of the longest path in which every node has the same value. The path length is reported as the number of nodes involved in the path.

## Input
- The first line contains an integer n — the number of nodes.
- The next line contains n integers — the values of the nodes (1-indexed).
- The next n−1 lines each contain two integers u, v representing an undirected edge between nodes u and v, where u and v are the 1-based indices of the nodes as given in the second line of input.

## Output
Print a single integer — the length of the longest equal-value path.

## Usage
1. Compile: `gcc -o Problem4 Problem4.c`
2. Run: `./Problem4` and enter the traversals as prompted

Example input:  
6  
5 5 5 5 1 5  
1 2  
1 3  
2 4  
3 5  
3 6 

Expected output:  
5

## Dependencies
- Standard C library
- stdlib.h
- string.h

# Problem5.c

## Description
Implements a Binary Search Tree (BST). Processes the value of the Kth node along the path of two given nodes u and v

## Input
- First line: Number of nodes 
- Second line: Array of node values
- Third line: Number of queries n
- Next n lines: u v K

## Output
- Prints the acquired node value, or -1 if it doesn't exist

## Usage
1. Compile: `gcc -o Problem5 Problem5.c`
2. Run: `./Problem5` and enter the input as prompted

Example input:  
7  
4 2 6 1 3 5 7  
2  
1 7 3  
3 5 2  

Expected output:  
4  
2

## Dependencies
- Standard C library
- stdlib.h

# Problem6.c

## Description
This program constructs a Binary Search Tree (BST) from a level order array where missing nodes are indicated by "NULL"/"null". It gives the sum of all node values within a given range.

## Input
- The first line contains the array representation of the BST (use "null"/"NULL" for empty nodes)
- The next line contains two integers — `low` and `high`.

## Output
- Print the sum of node values that lie in the range [low, high].

## Usage
1. Compile: `gcc -o Problem6 Problem6.c`
2. Run: `./Problem6` and enter the traversals as prompted

Example input:  
10 5 15 3 7 null 18  
7 15

Expected output:  
32

## Dependencies
- Standard C library
- stdlib.h
- string.h
