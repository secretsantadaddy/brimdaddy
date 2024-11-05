#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n = argc - 1;  // Number of elements passed (excluding program name)
    int arr[n];

    // Convert the string arguments back to integers
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    // Display the array in reverse order
    printf("Child process (PID: %d) displaying integers in reverse order: ", getpid());
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
