//Write a program in C, to implement Randomized version of Quick Sort.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array around the pivot
int partition(int arr[], int low, int high) {
    // Randomly choose a pivot index
    int pivotIndex = low + rand() % (high - low + 1);
    
    // Swap pivot with the last element
    swap(&arr[pivotIndex], &arr[high]);
    
    int pivot = arr[high];
    int i = low - 1;

    // Rearranging the elements around the pivot
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // Swap the pivot element to its correct position
    swap(&arr[i + 1], &arr[high]);
    
    return i + 1;
}

// Function to implement Quick Sort with Randomized pivot
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pi = partition(arr, low, high);
        
        // Recursively sort the left and right subarrays
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    int arr[] = {12, 3, 5, 7, 19, 2, 1, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Call the Quick Sort function
    quickSort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
