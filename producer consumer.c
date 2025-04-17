#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mutex = 1, full = 0, empty = 3, x = 0, buffer = 0;

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}

void producer() {
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    x = rand() % 50;
    buffer = x;
    printf("Producer 1 produced %d\n", x);
    printf("Buffer:%d\n", buffer);
    mutex = signal(mutex);
}

void consumer() {
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    printf("Consumer 2 consumed %d\n", buffer);
    printf("Current buffer len: 0\n");
    x--;
    mutex = signal(mutex);
}

void main() {
    int choice, p, c;

    srand(time(0));
    printf("Enter the number of Producers:");
    scanf("%d", &p);
    printf("Enter the number of Consumers:");
    scanf("%d", &c);
    printf("Enter buffer capacity:");
    scanf("%d", &empty);

    for (int i = 1; i <= p; i++)
        printf("Successfully created producer %d\n", i);
    for (int i = 1; i <= c; i++)
        printf("Successfully created consumer %d\n", i);

    while (1) {
        printf("\n1.Producer\n2.Consumer\n3.Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if ((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("Buffer is full\n");
                break;
            case 2:
                if ((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("Buffer is empty\n");
                break;
            case 3:
                exit(0);
        }
    }
}
