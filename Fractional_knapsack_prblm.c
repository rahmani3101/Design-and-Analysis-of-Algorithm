//Write a program in C, to implement the fractional knapsack problem.

#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct {
    int value;
    int weight;
    float ratio;  // value/weight ratio
} Item;

// Function to compare two items based on their value-to-weight ratio
int compare(const void *a, const void *b) {
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    if (item1->ratio > item2->ratio) {
        return -1;  // If ratio of item1 is greater, return -1
    } else if (item1->ratio < item2->ratio) {
        return 1;   // If ratio of item2 is greater, return 1
    } else {
        return 0;   // If both ratios are equal, return 0
    }
}

// Function to implement fractional knapsack
float fractionalKnapsack(int W, Item items[], int n) {
    // Sort items by value/weight ratio in descending order
    qsort(items, n, sizeof(Item), compare);

    float totalValue = 0.0; // To store the total value in the knapsack

    // Iterate over the sorted items
    for (int i = 0; i < n; i++) {
        // If item can be completely added to knapsack
        if (items[i].weight <= W) {
            totalValue += items[i].value;  // Add whole item to knapsack
            W -= items[i].weight;  // Decrease the remaining capacity
        } else {
            // If item cannot be completely added, take the fraction
            totalValue += items[i].value * ((float)W / items[i].weight);
            break;  // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    int n, W;

    // Input the number of items and knapsack capacity
    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &W);

    Item items[n];

    // Input the items' value and weight
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight of item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
        items[i].ratio = (float)items[i].value / items[i].weight;  // Calculate value-to-weight ratio
    }

    // Call the fractionalKnapsack function
    float maxValue = fractionalKnapsack(W, items, n);

    // Output the maximum value that can be obtained
    printf("Maximum value in the knapsack = %.2f\n", maxValue);

    return 0;
}
