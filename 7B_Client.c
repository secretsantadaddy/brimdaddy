#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ 25 // Size of shared memory

int main() {
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678; // Key for shared memory segment

    // Get the shared memory segment
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Locate the shared memory segment
    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Client reading data from Server:\n");

    // Read from the shared memory segment
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
    }
    printf("\n");

    // Detach from the shared memory
    shmdt(shm);

    // Remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0; 
}
