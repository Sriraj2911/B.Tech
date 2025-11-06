#include <stdio.h>
#include "dataop.h"

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    sort_array(arr, size);
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Max value: %d\n", find_max(arr, size));
    return 0;
}
