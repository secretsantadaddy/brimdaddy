#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ 25 // Size of shared memory

int main() {
    int shmid;
    key_t key;
    char *shm, *s;
    char *str;

    str = (char *)malloc(sizeof(char) * 15); // Allocate memory for input
    key = 5678; // Key for shared memory segment

    // Create the shared memory segment
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment
    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    
    s = shm; // Pointer to shared memory
    
    // Writing to memory
    printf("\nEnter message from Server to Client: ");
    scanf("%[^\n]s", str); // Read string from user

    // Write the string to shared memory
    for (int cnt = 0; str[cnt] != '\0'; cnt++) {
        *s++ = str[cnt];
    }
    *s = '\0'; // Null-terminate the string

    // Detach from shared memory
    shmdt(shm); 
    free(str); // Free the allocated memory
    return 0; 
}