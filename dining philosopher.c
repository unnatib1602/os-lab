#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int n;
sem_t *chopstick;
pthread_t *philosopher;
int *phil_ids;

void* philosopher_fn(void* num) {
    int i = *(int*)num;
    int left = i;
    int right = (i + 1) % n;
    printf("Philosopher %d is hungry\n", i + 1);
    sem_wait(&chopstick[left]);
    sem_wait(&chopstick[right]);
    printf("Philosopher %d took chopstick %d and %d\n", i + 1, left + 1, right + 1);
    printf("Philosopher %d is eating\n", i + 1);
    sleep(1);
    printf("Philosopher %d finished eating and kept the chopstick back on table\n", i + 1);
    sem_post(&chopstick[left]);
    sem_post(&chopstick[right]);
    return NULL;
}

int main() {
    int hungry, i;
    printf("Enter the number of philosophers:");
    scanf("%d", &n);
    chopstick = malloc(n * sizeof(sem_t));
    philosopher = malloc(n * sizeof(pthread_t));
    phil_ids = malloc(n * sizeof(int));
    for (i = 0; i < n; i++) sem_init(&chopstick[i], 0, 1);
    printf("Enter number of hungry philosophers:");
    scanf("%d", &hungry);
    for (i = 0; i < hungry; i++) {
        phil_ids[i] = i;
        pthread_create(&philosopher[i], NULL, philosopher_fn, &phil_ids[i]);
        sleep(1);
    }
    for (i = 0; i < hungry; i++) {
        pthread_join(philosopher[i], NULL);
    }
    free(chopstick);
    free(philosopher);
    free(phil_ids);
    return 0;
}
