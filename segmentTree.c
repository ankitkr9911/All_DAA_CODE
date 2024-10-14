#include<stdio.h>

#define MAX 10000

int segment_tree[4*MAX];

// Function to build the segment tree
void build_tree(int arr[], int node, int start, int end) {

    if (start == end) {
        segment_tree[node] = arr[start]; // Assign the value of the array to the segment tree
    } 
    else {
        // Calculate the mid-point of the current segment
        int mid = (start + end) / 2;

        // Recursively build the left and right subtrees
        build_tree(arr, 2 * node, start, mid);          
        build_tree(arr, 2 * node + 1, mid + 1, end);   
        
        // Combine the results from the left and right children
        segment_tree[node] = segment_tree[2 * node] + segment_tree[2 * node + 1];
    }
}

// Function to query the sum in a given range [L, R]
int sumQuery(int node, int start, int end, int L, int R) {

    if (R < start || L > end) {
        return 0; // Return 0 since it doesn't contribute to the sum
    }
    
    // If the current segment is completely within the range [L, R]
    if (start >= L && end <= R) {
        return segment_tree[node]; // Return the sum stored in the segment tree
    }
    
    // Otherwise, the segment is partially in the range [L, R]
    int mid = (start + end) / 2; // Calculate the mid-point
    int left_sum = sumQuery(2 * node, start, mid, L, R);          // Query the left child
    int right_sum = sumQuery(2 * node + 1, mid + 1, end, L, R);    // Query the right child

    // Return the sum from both left and right children
    return left_sum + right_sum;
}


int main() {
    int N, Q; 
    printf("Enter the number of elements in the array: ");
    scanf("%d", &N); // Input the number of elements

    int arr[N]; // Array to hold the elements

    // Input the elements of the array
    for (int i = 0; i < N; i++) {
        printf("Enter arr[%d]: ", i);
        scanf("%d", &arr[i]);
    }

    // Build the segment tree from the input array
    build_tree(arr, 1, 0, N - 1);

    printf("Enter the number of queries: ");
    scanf("%d", &Q); // Input the number of queries

    // Process each query
    for (int i = 0; i < Q; i++) {
        int L, R; // Variables for the query range
        printf("Enter the range [L,R]: ");
        scanf("%d %d", &L, &R); // Input the range for the sum query

        // Calculate the sum in the specified range and print it
        int sum = sumQuery(1, 0, N - 1, L, R);
        printf("Sum of the elements in the range [%d,%d]: %d\n", L, R, sum);
    }

    return 0; 
}
