#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "semaphore.h"
#include "stdbool.h"

#define NUMOFR 5
#define NUMOFW 5
#define size 10

struct board
{
    int buffer[size];
    int count;
    sem_t writers, readers;
    pthread_mutex_t x, y;
};

typedef struct board BOARD;

BOARD b;

void initBoard(void);
void writers(int *);
void readers(int *);
void printBoard(void);

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    pthread_t w[NUMOFW], r[NUMOFR];
    int idw[NUMOFW];
    int idr[NUMOFR];

    initBoard();

    for (size_t i = 0; i < NUMOFW; i++)
    {
        idw[i] = i;
        pthread_create(&w[i], NULL, (void *) writers, &idw[i]);
    }

    for (size_t i = 0; i < NUMOFR; i++)
    {
        idr[i] = i;
        pthread_create(&r[i], NULL, (void *) readers, &idr[i]);
    }

    for (size_t i = 0; i < NUMOFW; i++)
        pthread_join(w[i], NULL);
    
    for (size_t i = 0; i < NUMOFR; i++)
        pthread_join(r[i], NULL);
       
    return 0;
}

void initBoard(void)
{
    for (size_t i = 0; i < size; i++)
        b.buffer[i] = 0;
    b.count = 0;
    sem_init(&b.writers, 1, NUMOFW);
    sem_init(&b.readers, 1, NUMOFR);
    pthread_mutex_init(&b.x, NULL);
    pthread_mutex_init(&b.y, NULL);
}

void writers(int *identity)
{
    int id = *identity;
    int num;
    int index;
    while (true)
    {
        num   = (rand() % 20) + 1;
        index = rand() % size;

        sem_wait(&b.writers);
        
        /* 5 threads could arrive here at the same time */

        pthread_mutex_lock(&b.x);

        /* only one thread could be here at a time */

        b.buffer[index] = num;
        printf("writer %d is updating the array index %d with the number %d\n", id, index, num);
        printBoard();
        sleep(1);

        pthread_mutex_unlock(&b.x);
        
        sem_post(&b.writers);
        sleep(1);

    }
}

void readers(int *identity)
{
    int id = *identity;
    int num;
    int index;
    while (true)
    {
        sem_wait(&b.readers);

       /* 5 readers could be here at the same time*/
       
        b.count++;
        if(b.count == 1)
            sem_wait(&b.writers);

        pthread_mutex_lock(&b.y);
        index = rand() % size;
        num = b.buffer[index];
        printf("reader %d is fetching from the array index %d -- the value %d -- count %d-- \n", id, index, num, b.count);
        printBoard();
        sleep(1);
        pthread_mutex_unlock(&b.y);

        b.count--;
        if(b.count == 0)
            sem_post(&b.writers);

        sem_post(&b.readers);
        sleep(1);
    }
}


void printBoard(void)
{
    printf("[");
    for (size_t i = 0; i < size; i++)
    {
        if(i < size - 1)
            printf("%d,", b.buffer[i]);
        else
            printf("%d", b.buffer[i]);
    }
    printf("]\n");
}



