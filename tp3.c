#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 100
#define INITIAL_BALANCE 1000

int balance = INITIAL_BALANCE;
int total_d = 0;
int total_w = 0;

void *depositor(void *arg) {
    int amount = rand() % 100;
    total_d += amount;
    int current_balance = balance;
    usleep(100);
    balance = current_balance + amount;
    return NULL;
}

void *withdrawer(void *arg) {
    int amount = rand() % 100;
    total_w += amount;
    int current_balance = balance;
    if (current_balance >= amount) {
        usleep(100);
        balance = current_balance - amount;
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    srand(time(NULL));

    for (int i = 0; i < NUM_THREADS; i++) {
        if (i % 2 == 0) {
            pthread_create(&threads[i], NULL, depositor, NULL);
        } else {
            pthread_create(&threads[i], NULL, withdrawer, NULL);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final balance: %d\nTotal D: %d\nTotal W: %d\n", balance, total_d, total_w);
    return 0;
}
