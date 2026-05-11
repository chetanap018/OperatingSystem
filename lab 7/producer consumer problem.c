#include <stdio.h>
#include <stdlib.h>

int mutex = 1;   // controls access to critical section
int full = 0;    // number of full slots
int empty = 5;   // buffer size
int x = 0;       // item counter

// wait (P operation)
void wait(int *s)
{
    (*s)--;
}

// signal (V operation)
void signal(int *s)
{
    (*s)++;
}

// Producer function
void producer()
{
    wait(&empty);
    wait(&mutex);

    x++;
    printf("Producer has produced: Item %d\n", x);

    signal(&mutex);
    signal(&full);
}

// Consumer function
void consumer()
{
    wait(&full);
    wait(&mutex);

    printf("Consumer has consumed: Item %d\n", x);
    x--;

    signal(&mutex);
    signal(&empty);
}

// Main function
int main()
{
    int choice;

    while (1)
    {
        printf("\n1. Producer\n2. Consumer\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if ((mutex == 1) && (empty != 0))
                producer();
            else
                printf("Buffer is full!\n");
            break;

        case 2:
            if ((mutex == 1) && (full != 0))
                consumer();
            else
                printf("Buffer is empty!\n");
            break;

        case 3:
            exit(0);
        }
    }
}
