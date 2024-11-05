#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_REQUESTS 100

// Function prototypes for disk scheduling algorithms
int SSTF();
int SCAN();
int CLOOK();

int main() {
    int ch, YN = 1;

    do {
        // Display menu
        printf("\n\n\t*********** MENU ***********");
        printf("\n\n\t1: SSTF\n");
        printf("\t2: SCAN\n");
        printf("\t3: CLOOK\n");
        printf("\t4: EXIT");
        printf("\n\n\tEnter your choice: ");
        
        // Read user's choice
        if (scanf("%d", &ch) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (ch) {
            case 1: SSTF(); break;
            case 2: SCAN(); break;
            case 3: CLOOK(); break;
            case 4: exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }

        printf("\n\n\tDo you want to continue? Press 1 for YES, 0 for NO: ");
        if (scanf("%d", &YN) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
    } while (YN == 1);

    return 0;
}

// SSTF Algorithm
int SSTF() {
    int RQ[MAX_REQUESTS], i, n, TotalHeadMovement = 0, initial, count = 0;

    // Get the number of requests
    printf("Enter the number of Requests (max %d): ", MAX_REQUESTS);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 0;
    }

    // Get the request sequence
    printf("Enter the Requests sequence:\n");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &RQ[i]) != 1) {
            printf("Invalid input for request sequence.\n");
            return 0;
        }
    }

    // Get the initial head position
    printf("Enter initial head position:\n");
    if (scanf("%d", &initial) != 1) {
        printf("Invalid initial head position.\n");
        return 0;
    }

    while (count != n) {
        int min = 1000, d, index;
        for (i = 0; i < n; i++) {
            d = abs(RQ[i] - initial);
            if (min > d) {
                min = d;
                index = i;
            }
        }
        TotalHeadMovement += min;
        initial = RQ[index];
        RQ[index] = 1000; // Mark request as serviced
        count++;
    }
    
    printf("Total head movement is %d\n", TotalHeadMovement);
    return 0;
}

// SCAN Algorithm
int SCAN() {
    int RQ[MAX_REQUESTS], i, j, n, TotalHeadMovement = 0, initial, size, move;
    
    // Get the number of requests
    printf("Enter the number of Requests (max %d): ", MAX_REQUESTS);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 0;
    }

    // Get the request sequence
    printf("Enter the Requests sequence:\n");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &RQ[i]) != 1) {
            printf("Invalid input for request sequence.\n");
            return 0;
        }
    }

    // Get the initial head position and disk size
    printf("Enter initial head position:\n");
    if (scanf("%d", &initial) != 1) {
        printf("Invalid initial head position.\n");
        return 0;
    }
    
    printf("Enter total disk size:\n");
    if (scanf("%d", &size) != 1) {
        printf("Invalid total disk size.\n");
        return 0;
    }

    // Get the head movement direction
    printf("Enter the head movement direction for high (1) and for low (0):\n");
    if (scanf("%d", &move) != 1 || (move != 0 && move != 1)) {
        printf("Invalid direction input.\n");
        return 0;
    }

    // Sort the request sequence
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) {
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs(size - RQ[n - 1] - 1);
        initial = size - 1;
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else {
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs(RQ[0] - 0);
        initial = 0;
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("Total head movement is %d\n", TotalHeadMovement);
    return 0;
}

// C-LOOK Algorithm
int CLOOK() {
    int RQ[MAX_REQUESTS], i, j, n, TotalHeadMovement = 0, initial, size, move;

    // Get the number of requests
    printf("Enter the number of Requests (max %d): ", MAX_REQUESTS);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 0;
    }

    // Get the request sequence
    printf("Enter the Requests sequence:\n");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &RQ[i]) != 1) {
            printf("Invalid input for request sequence.\n");
            return 0;
        }
    }

    // Get the initial head position and disk size
    printf("Enter initial head position:\n");
    if (scanf("%d", &initial) != 1) {
        printf("Invalid initial head position.\n");
        return 0;
    }

    printf("Enter total disk size:\n");
    if (scanf("%d", &size) != 1) {
        printf("Invalid total disk size.\n");
        return 0;
    }

    // Get the head movement direction
    printf("Enter the head movement direction for high (1) and for low (0):\n");
    if (scanf("%d", &move) != 1 || (move != 0 && move != 1)) {
        printf("Invalid direction input.\n");
        return 0;
    }

    // Sort the request sequence
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) {
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (i = 0; i < index; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else {
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (i = n - 1; i >= index; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("Total head movement is %d\n", TotalHeadMovement);
    return 0;
}
