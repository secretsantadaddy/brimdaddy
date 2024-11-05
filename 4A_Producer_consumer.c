#include <stdio.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

char avbuff[10];  // Shared buffer
sem_t mutex, empty, full;  // Semaphores

void *produce(void *arg) {
    int i;
    printf("\nInside Producer");
    for (i = 0; i < 10; i++) {
        sem_wait(&empty);  // Wait for an empty slot
        sem_wait(&mutex);  // Lock the buffer
        
        avbuff[i] = i;  // Produce an item
        printf("\nItem produced is %d", avbuff[i]);
        
        sem_post(&mutex);  // Release the buffer
        sem_post(&full);   // Signal that a slot is full
        
        sleep(1);  // Simulate time taken to produce
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int j;
    printf("\nInside Consumer");
    for (j = 0; j < 10; j++) {
        sem_wait(&full);   // Wait for a full slot
        sem_wait(&mutex);  // Lock the buffer

        int item = avbuff[j];  // Consume the item
        printf("\nItem consumed is %d", item);
        
        sem_post(&mutex);  // Release the buffer
        sem_post(&empty);  // Signal that a slot is empty
        
        sleep(5);  // Simulate time taken to consume
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;  // Thread identifiers
    void *status;

    // Initialize semaphores
    sem_init(&empty, 0, 10);  // 10 empty slots initially
    sem_init(&full, 0, 0);    // 0 full slots initially
    sem_init(&mutex, 0, 1);   // Binary semaphore for mutual exclusion

    // Create producer and consumer threads
    pthread_create(&tid1, NULL, produce, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(tid1, &status);
    printf("\nProducer exited with status %s\n", (char *)status);

    pthread_join(tid2, &status);
    printf("\nConsumer exited with status %s\n", (char *)status);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
