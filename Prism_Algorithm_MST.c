//Write a program in C, to implement Prim's algorithm to find the minimum spanning tree.

#include <stdio.h>
#include <limits.h>

// Number of vertices in the graph
#define V 5

// Function to find the vertex with the minimum key value
int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to implement Prim's Algorithm
void primMST(int graph[V][V]) {
    int parent[V];  // Array to store the MST
    int key[V];     // Key values to pick the minimum weight edge
    int mstSet[V];  // To check if a vertex is included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Start with the first vertex
    key[0] = 0;
    parent[0] = -1;  // First node is always the root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet);
        mstSet[u] = 1;  // Include the picked vertex in MST

        // Update key values and parent index of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update the key only if the current edge is smaller than the existing key
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the constructed MST
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

int main() {
    // A 5x5 adjacency matrix for a weighted graph
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    // Run Prim's algorithm to find the MST
    primMST(graph);

    return 0;
}
