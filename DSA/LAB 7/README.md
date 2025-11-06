# Heap Sort 
  
This program repeatedly extracts the smallest element from the heap to produce a sorted (ascending) list.



## How It Works

1. **`buildHeap()`**  
   Converts an unsorted array into a valid heap where every parent node ≤ its children.  

2. **`deleteMin()`**  
   Removes the smallest element (the root), swaps it with the last element, and re-heapifies the remaining elements.

3. The main loop calls `deleteMin()` repeatedly to produce the sorted output.


## Time Complexity

| Operation | Complexity |
|-----------|-------------|
| Build Heap | O(n) |
| deleteMin | O(logn) |
| Heap sort (total) | O(nlogn) |

