#include <stdio.h>
#include "stringop.h"
#include "dataop.h"
#include "mathop.h"

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    int a = 10, b = 5;

    char str[] = "Hello World";
    printf("Using math operations\n");
    printf("Addition: %d\n", add(a, b));
    printf("Subtraction: %d\n", subtract(a, b));

    printf("\nUsing string operations\n");
    to_uppercase(str);
    printf("Uppercase: %s\n", str);
    to_lowercase(str);
    printf("Lowercase: %s\n", str);

    printf("\nUsing data operations\n");
    sort_array(arr, size);
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Max value: %d\n", find_max(arr, size));
    return 0;
}
