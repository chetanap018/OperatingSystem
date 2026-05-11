#include <stdio.h>
#include <stdlib.h>

#define N 5

int state[N]; // 0 = thinking, 1 = hungry, 2 = eating
int mutex = 1;

// Wait and Signal
void wait(int *s) { (*s)--; }
void signal(int *s) { (*s)++; }

// Check if philosopher can eat
void test(int i)
{
    if (state[i] == 1 &&
        state[(i + 4) % N] != 2 &&
        state[(i + 1) % N] != 2)
    {
        state[i] = 2;
        printf("Philosopher %d is eating\n", i + 1);
    }
}

// Take forks
void take_fork(int i)
{
    wait(&mutex);

    state[i] = 1;
    printf("Philosopher %d is hungry\n", i + 1);

    test(i);

    signal(&mutex);
}

// Put forks
void put_fork(int i)
{
    wait(&mutex);

    state[i] = 0;
    printf("Philosopher %d is thinking\n", i + 1);

    test((i + 4) % N);
    test((i + 1) % N);

    signal(&mutex);
}

// Main
int main()
{
    int i, choice;

    while (1)
    {
        printf("\n1. One can eat at a time\n2. Two can eat at a time\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3)
            break;

        for (i = 0; i < N; i++)
        {
            take_fork(i);
            put_fork(i);
        }
    }

    return 0;
}
