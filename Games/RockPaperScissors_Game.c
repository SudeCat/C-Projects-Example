#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "time.h"
#include "stdbool.h"
#include "semaphore.h"
#include "pthread.h"

struct board
{
    char *buffer[2];
    sem_t empty;
    sem_t full;
};

typedef struct board BRD;

void clearBoard(BRD *);
void updateBoard(BRD *, char *, int);
void player1(BRD *);
void player2(BRD *);
void printBoard(BRD *, int);
int  decideHandWinner(BRD *);

int main(int argc, char const *argv[])
{   
    srand(time(NULL));
    BRD *b = malloc(sizeof(BRD));
    clearBoard(b);

    int p1_score = 0, p2_score = 0;
    int n = atoi(argv[1]);
    int rounds_to_win = (n/2) + 1;
   

    while (p1_score < rounds_to_win && p2_score < rounds_to_win ) {
        pthread_t p1, p2;
        pthread_create(&p1, NULL, (void *) player1, b);
        pthread_create(&p2, NULL, (void *) player2, b);
        pthread_join(p1, NULL);
        pthread_join(p2, NULL);
        
        
        int w = decideHandWinner(b);
        printBoard(b,w);

        if (w == 0) { 
            // do nothing     
        } else if (w == 1) {
            p1_score++;
        } else {
            p2_score++;
        }
        
    }

    if (p1_score > p2_score) {
        printf("*** player 1 achieves the best of %d with the score: (%d-%d); congrats player 1 ***\n",n, p1_score, p2_score);
    } else if (p2_score > p1_score) {
        printf("*** player 2 achieves the best of %d with the score: (%d-%d); congrats player 2 ***\n",n, p2_score, p1_score);
    } else {
        printf("*** The game is a tie with the score: (%d-%d) ***\n", p1_score, p2_score);
    }
    
    return 0;
}

int decideHandWinner(BRD *b)
{
    int v = 0;
    char *hand1 = (*(b)).buffer[0];
    char *hand2 = (*(b)).buffer[1];

    if (hand1[0] == hand2[0])
        v = 0;

    else if (hand1[0] == 'r' && hand2[0] == 's')
        v = 1;
    
    else if (hand1[0] == 'p' && hand2[0] == 'r')
        v = 1;
    
    else if (hand1[0] == 's' && hand2[0] == 'p')
        v = 1;
    
    else
        v = 2;
    
    return v;   
}

void clearBoard(BRD *b)
{
    for (size_t i = 0; i < 2; i++)
        (*(b)).buffer[i] = NULL;
    sem_init(&(*(b)).empty, 1, 1);
    sem_init(&(*(b)).full, 1, 0);
}

void player1(BRD *b)
{   
    sem_wait(&(*(b)).empty);
    int random_num = (rand() % 3);
    char *hands[] = {"rock", "paper", "scissors"};
    updateBoard(b, (char *)hands[random_num], 0); 
    sem_post(&(*(b)).full); 
    pthread_exit(NULL);
        
}

void player2(BRD *b)
{  
    sem_wait(&((*b).full));
    int random_num = (rand() % 3);
    char *hands[] = {"rock", "paper", "scissors"};
    updateBoard(b, (char *)hands[random_num], 1);   
    sem_post(&((*b).empty));  
    pthread_exit(NULL);  
}

void updateBoard(BRD *b, char *s, int i)
{
    (*(b)).buffer[i] = s;
}

void printBoard(BRD *b, int w)
{   
    printf("[ p1: %-8s | p2: %-8s]", (*(b)).buffer[0], (*(b)).buffer[1]);
    if (w == 0) {
        printf(" --- draw hand; no winner!\n");
    } else if (w == 1) {
        printf(" --- player 1 wins the hand!\n");
    } else {
        printf(" --- player 2 wins the hand!\n");
    }
    
}
