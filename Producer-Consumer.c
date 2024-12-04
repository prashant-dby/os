#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Define the buffer size
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores for synchronization
sem_t empty; // Counts empty slots in the buffer
sem_t full;  // Counts full slots in the buffer
pthread_mutex_t mutex; // Mutex for critical section

// Producer function
void *producer(void *param) {
    int item;
    for (int i = 0; i < 10; i++) { // Produces 10 items
        item = rand() % 100; // Produce a random item

        sem_wait(&empty); // Decrement empty count
        pthread_mutex_lock(&mutex); // Enter critical section

        // Add item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Increment full count
    }
    return NULL;
}

// Consumer function
void *consumer(void *param) {
    int item;
    for (int i = 0; i < 10; i++) { // Consumes 10 items
        sem_wait(&full); // Decrement full count
        pthread_mutex_lock(&mutex); // Enter critical section

        // Remove item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Increment empty count
    }
    return NULL;
}

int main() {
    pthread_t producerThread, consumerThread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full, 0, 0);            // Initially, no slots are full
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
