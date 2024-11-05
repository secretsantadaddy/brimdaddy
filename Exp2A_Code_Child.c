#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int n = argc - 1;  // Number of elements passed (excluding program name)
    int arr[n];

    // Convert the string arguments back to integers
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    // Sort the array in the child process
    bubbleSort(arr, n);

    // Display the sorted array
    printf("Child process (PID: %d) sorted integers: ", getpid());
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

