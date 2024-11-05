#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

int main() {
    int n, i;
    
    // Input the number of integers
    printf("Enter the number of integers to be sorted: ");
    scanf("%d", &n);
    int arr[n];
    
    // Input the array elements
    printf("Enter the integers to be sorted: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Create a child process using fork
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } else if (pid == 0) {
        // This is the child process
        char *args[n + 2];  // Array to hold command-line arguments for execve
        args[0] = "./child"; // First argument is the child program's name

        // Convert integers to strings and add them as arguments
        for (i = 0; i < n; i++) {
            char *arg = (char *)malloc(20);
            sprintf(arg, "%d", arr[i]);
            args[i + 1] = arg;
        }
        args[n + 1] = NULL;  // Terminate the argument list

        // Use execve to replace the child process with the child program
        execve(args[0], args, NULL);

        // If execve fails, print an error
        perror("execve failed");
        return 1;
    } else {
        // This is the parent process
        printf("Parent process (PID: %d) sorting the integers...\n", getpid());

        // Sort the array using bubble sort
        bubbleSort(arr, n);

        printf("Parent process (PID: %d) sorted integers: ", getpid());
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Demonstrate a zombie process (child finishes, parent waits after a delay)
        sleep(5);  // Simulates zombie state for child process

        // Wait for the child process to complete
        wait(NULL);
        printf("Parent process waited for the child to finish.\n");
    }

    return 0;
}

