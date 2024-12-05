//Write a program in C to find the maximum and minimum number, using divide and conquer technique.

#include <stdio.h>
#include <limits.h>

// Function to find the maximum and minimum of an array using divide and conquer
void findMinMax(int arr[], int low, int high, int *min, int *max) {
    // If there's only one element, both min and max are that element
    if (low == high) {
        *min = arr[low];
        *max = arr[low];
        return;
    }
    
    // If there are two elements, compare them directly
    if (high == low + 1) {
        if (arr[low] > arr[high]) {
            *max = arr[low];
            *min = arr[high];
        } else {
            *max = arr[high];
            *min = arr[low];
        }
        return;
    }
    
    // Find the middle index
    int mid = (low + high) / 2;
    
    // Recursively find the min and max in the left half and right half
    int leftMin, leftMax, rightMin, rightMax;
    findMinMax(arr, low, mid, &leftMin, &leftMax);
    findMinMax(arr, mid + 1, high, &rightMin, &rightMax);
    
    // Compare the results from the left and right halves to get the final min and max
    *min = (leftMin < rightMin) ? leftMin : rightMin;
    *max = (leftMax > rightMax) ? leftMax : rightMax;
}

int main() {
    int arr[] = {12, 3, 5, 7, 19, 2, 1, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int min = INT_MAX, max = INT_MIN;
    
    // Call the divide and conquer function
    findMinMax(arr, 0, n - 1, &min, &max);
    
    printf("Minimum element is %d\n", min);
    printf("Maximum element is %d\n", max);
    
    return 0;
}

