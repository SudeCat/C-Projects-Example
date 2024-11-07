#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "semaphore.h"
#include "time.h"
#include "stdbool.h"

#define NUMOP 5
#define TLIMIT 5
#define MAXWT 1000000

enum state
{
    THINKING, EATING, HUNGRY
};

typedef enum state STATE;

struct board
{
    STATE state[NUMOP];
    pthread_mutex_t mutex;
    pthread_cond_t cond[NUMOP];
    long WT[NUMOP];
    long TWT[NUMOP];
};

typedef struct board BOARD;
BOARD b;

long getSystemTime(void);
void initBoard(void);
bool canRun(int);
void philosophers(int *);
void pickCS(int);
void returnCS(int);
void checkCS(int);

int main(int argc, char const *argv[])
{
    pthread_t t[NUMOP];
    int id[NUMOP];

    initBoard();

    for (size_t i = 0; i < NUMOP; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, (void *) philosophers, &id[i]);
    }

    for (size_t i = 0; i < NUMOP; i++)
        pthread_join(t[i], NULL); 

    return 0;
}

void initBoard(void)
{
    pthread_mutex_init(&b.mutex, NULL);
    for (size_t i = 0; i < NUMOP; i++)
    {
        pthread_cond_init(&b.cond[i], NULL);
        b.state[i] = THINKING;
        b.WT[i] = 0;
        b.TWT[i] = 0;
    }
}

long getSystemTime(void)
{
    struct timespec ts;

    if(clock_gettime(1, &ts) == 0) 
        return (long) ts.tv_sec * 1000000000 + ts.tv_nsec;

    return 0;
}

bool canRun(int id)
{
    long current = b.WT[id];

    long left = b.WT[(id+NUMOP-1)%NUMOP];

    long right = b.WT[(id+1)%NUMOP];

    if(left > current && left > MAXWT)
    {
        printf("philosopher %d is giving way to the philosopher %d to avoid starvation\n", id, (id+NUMOP-1)%NUMOP);
        return false;
    }
    if(right > current && right > MAXWT)
    {
        printf("philosopher %d is giving way to the philosopher %d to avoid starvation\n", id, (id+1)%NUMOP);
        return false;
    }
    return true;
}

void philosophers(int *identity)
{
    int id = *identity;

    while (true)
    {
        srand(time(NULL) * id);
        int thinkTime = (rand() % TLIMIT) + 1;
        int eatTime = (rand() % TLIMIT) + 1;
        printf("philosopher %d is thinking for %d seconds\n", id, thinkTime);
        sleep(thinkTime);
        pickCS(id);
        printf("philosopher %d is ***EATING*** for %d seconds\n", id, eatTime);
        sleep(eatTime);   
        returnCS(id);     
    }
}

void pickCS(int id)
{
    pthread_mutex_lock(&b.mutex);

    long now = getSystemTime();
    b.state[id] = HUNGRY;
    printf("philosopher %d is hungry\n", id);
    b.WT[id] = now;
    checkCS(id);

    if(b.state[id] != EATING)
    {
        pthread_cond_wait(&b.cond[id], &b.mutex);
    }

    pthread_mutex_unlock(&b.mutex);
}

void checkCS(int id)
{
    long now = getSystemTime();
    printf("philosopher %d is looking for chopsticks\n", id);

    if(b.state[id] == HUNGRY &&
       b.state[(id+NUMOP-1)%NUMOP] != EATING &&
       b.state[(id+1)%NUMOP] != EATING &&
       canRun(id)
      )
      {
        b.state[id] = EATING;
        b.WT[id] = now - b.WT[id];
        b.TWT[id] = b.TWT[id] + b.WT[id];

        pthread_cond_signal(&b.cond[id]);
      }
}

void returnCS(int id)
{
    pthread_mutex_lock(&b.mutex);

    b.state[id] = THINKING;
    printf("philosopher %d has finished eating\n", id);
    checkCS((id+NUMOP-1)%NUMOP);
    checkCS((id+1)%NUMOP);

    pthread_mutex_unlock(&b.mutex);
}