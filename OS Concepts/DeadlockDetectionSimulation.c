#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "semaphore.h"
#include "pthread.h"
#include "stdbool.h"

#define NUMOT 5
#define NUMOR 3

struct board
{
    sem_t thread[NUMOT], banker[NUMOT];
    int available[NUMOR];
    int allocation[NUMOT][NUMOR];
    int request[NUMOT][NUMOR];
    int total[NUMOR]; 
    bool finish[NUMOT];
    int free[NUMOT];
};

typedef struct board BOARD;
BOARD b;

void initBoard(void);
void refreshBoard(void);
void printState(void);
bool requestLtAvailable(int); 
int arrayLength(void);
void printArray(void);

void threads(int *);//25pts
void banker(void *);//25pts
bool isDeadlockFree(void); //50pts

int main(int argc, char const *argv[])
{
    pthread_t t[NUMOT], bnkr;
    int id[NUMOT];

    initBoard();

    for (size_t i = 0; i < NUMOT; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, (void *) threads, &id[i]);
    }

    pthread_create(&bnkr, NULL, (void *) banker, NULL);
    
    for (size_t i = 0; i < NUMOT; i++)
        pthread_join(t[i], NULL);
    
    pthread_join(bnkr, NULL);

    return 0;
}

void initBoard(void)
{
    for (size_t i = 0; i < NUMOT; i++)
    {
        sem_init(&b.thread[i],1,1);
        sem_init(&b.banker[i],1,0);
        b.finish[i] = false;
        b.total[i] = 0;
        b.free[i] = -1;
    }

    b.available[0] = 7;
    b.available[1] = 8;
    b.available[2] = 6;
}

void refreshBoard(void)
{
    for (size_t i = 0; i < NUMOT; i++)
    {
        b.total[i] = 0;
        b.free[i] = -1;
    }

    b.available[0] = 7;
    b.available[1] = 8;
    b.available[2] = 6;
}

void printState(void)
{
    bool v = true;
    printf(" Allocation      Request       Available\n");

    for (size_t i = 0; i < NUMOT; i++)
    {
        for (size_t j = 0; j < NUMOR; j++)
        {
            if(j < NUMOR - 1)
                printf("%-2d   ", b.allocation[i][j]);
            else
                printf("%-2d|  ", b.allocation[i][j]);
        }

        for (size_t j = 0; j < NUMOR; j++)
        {
            if(j < NUMOR - 1)
                printf("%-2d   ", b.request[i][j]);
            else
                printf("%-2d|  ", b.request[i][j]);
        }

        for (size_t k = 0; k < NUMOR && v; k++)
            printf("%-2d   ", b.available[k]);        
        
        v = false;
        printf("\n");
    }
}

bool requestLtAvailable(int id)
{
    bool v = true;

    for (size_t i = 0; i < NUMOR && v; i++)
    {
        if(b.request[id][i] <= b.available[i])
            v = v && true;
        else
            v = false;
    }
    return v;
}

void printArray(void)
{
    int l = arrayLength();
    printf("<");
    for (size_t i = 0; i < l; i++)
    {
        if(i < l - 1 && b.free[i+1] != -1)
            printf("%d,", b.free[i]);
        else if (b.free[i] != -1)
            printf("%d", b.free[i]);
    }
    printf(">\n");
}

int arrayLength(void)
{
    bool v = true;
    int i;
    for (i = 0; i < NUMOT && v; i++)
    {
        if(b.free[i] == -1)
            v = false;
    }
    return i;
}

void threads(int *identity)
{
    int id = *identity;

    while(true){
        sem_wait(&b.thread[id]);

        printf("Thread %d is allocating and requesting...\n", id);
 
        for (int j = 0; j < NUMOR; j++) {
            b.allocation[id][j] = rand() % 3;
            b.request[id][j] = rand() % 3;
        }

        sleep(1);
        sem_post(&b.banker[id]);
        
    }        

}

void banker(void *unused)
{
    while(true){

        for (size_t i = 0; i < NUMOT; i++)
            sem_wait(&b.banker[i]);

        printf("Banker is checking...\n");

        for (size_t i = 0; i < NUMOR; i++)
        {
            for (size_t j = 0; j < NUMOT; j++)
                b.total[i] = b.total[i] + b.allocation[j][i];            
        }

        for (size_t i = 0; i < NUMOR; i++)
            b.available[i] = b.available[i] - b.total[i];        
        
        printState();

        if (isDeadlockFree()) {
            printf("The system is deadlock-free.\n");
            printf("Order of service for working threads: ");
            printArray();
        } else {
            printf("The system is deadlocked.\n");
            printf("except\n");
            printArray();
        }

        refreshBoard();
        sleep(1);

        for (size_t i = 0; i < NUMOT; i++)
            sem_post(&b.thread[i]);
    }
}

bool isDeadlockFree(void)
{
    bool dl = true;
    int m = 0;

    for (size_t j = 0; j < NUMOT; j++)
    {
        dl = true;
        for (size_t i = 0; i < NUMOT; i++)
        {
            if(b.finish[i] == false && requestLtAvailable(i))
            {
                for (size_t k = 0; k < NUMOR; k++)
                {
                    b.available[k] = b.available[k] + b.allocation[i][k];
                    b.finish[i] = true;
                }
                b.free[m] = i;
                m++;
            }
        }

        for (size_t i = 0; i < NUMOT; i++)
        {
            if(b.finish[i] == true)
                dl = dl && true;
            else
                dl = false;
        }
    }

    return dl;

}