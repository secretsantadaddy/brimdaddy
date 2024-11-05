#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define READERS 3
#define WRITERS 2

pthread_mutex_t mutex; // To protect readers_count
sem_t rw_mutex;        // To control access to the shared resource
int readers_count = 0;
int shared_resource = 0; // The shared resource being read/written

void *reader(void *arg) {
    int id = *((int *) arg);
    while (1) {
        sleep(rand() % 3);  // Simulate reading delay

        // Lock the readers_count
        pthread_mutex_lock(&mutex);
        readers_count++;
        if (readers_count == 1) {
            // First reader locks the rw_mutex
            sem_wait(&rw_mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Read the shared resource
        printf("Reader %d is reading: %d\n", id, shared_resource);

        // Lock the readers_count and check if we are the last reader
        pthread_mutex_lock(&mutex);
        readers_count--;
        if (readers_count == 0) {
            // Last reader unlocks the rw_mutex
            sem_post(&rw_mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *) arg);
    while (1) {
        sleep(rand() % 3);  // Simulate writing delay

        // Lock the rw_mutex to gain exclusive access
        sem_wait(&rw_mutex);

        // Write to the shared resource
        shared_resource++;
        printf("Writer %d is writing: %d\n", id, shared_resource);

        // Release the rw_mutex
        sem_post(&rw_mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t reader_threads[READERS], writer_threads[WRITERS];
    int reader_ids[READERS], writer_ids[WRITERS];

    // Initialize mutex and semaphore
    pthread_mutex_init(&mutex, NULL);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all reader threads to complete (this never happens since they run indefinitely)
    for (int i = 0; i < READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    // Wait for all writer threads to complete (this never happens since they run indefinitely)
    for (int i = 0; i < WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    // Destroy mutex and semaphore (this won't be reached due to the infinite loop)
    pthread_mutex_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
