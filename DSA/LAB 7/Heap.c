#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b; 
    *b = temp;
}

void heapify(int* arr, int n){
    int i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if (left < n && arr[left] < arr[smallest])
            smallest = left;
        if (right < n && arr[right] < arr[smallest])
            smallest = right;

        if (smallest != i) {
            swap(&arr[i], &arr[smallest]);
            i = smallest;
        } else break;
    }
}

int deleteMin(int* arr, int n){
    int min = arr[0];
    swap(&arr[0], &arr[n-1]);
    heapify(arr, n-1); // Heapify only the valid part
    return min;
}

void buildHeap(int* arr, int n){
    for (int i = n/2 - 1; i >= 0; i--) {
        int idx = i;
        while (1) {
            int left = 2*idx + 1;
            int right = 2*idx + 2;
            int smallest = idx;

            if (left < n && arr[left] < arr[smallest])
                smallest = left;
            if (right < n && arr[right] < arr[smallest])
                smallest = right;

            if (smallest != idx) {
                swap(&arr[idx], &arr[smallest]);
                idx = smallest;
            } else break;
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", arr+i);
    }
    // Convert the given array into a proper heap
    buildHeap(arr, n);
    for(int i=0; i<n; i++){
        printf("%d ", deleteMin(arr, n-i));
    }

}
