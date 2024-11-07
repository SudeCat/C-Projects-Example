#include "stdio.h"
#include "stdlib.h"       // malloc
#include "stdbool.h"      // true, false
#include "semaphore.h"    // sem_t
#include "pthread.h"      // pthread_t
#include "unistd.h"       // sleep

#define size 3
#define winner 15

struct board
{
    int buffer[size][size];
    bool gameon;
    sem_t empty;
    sem_t full;
    sem_t ref;
};

typedef struct board BRD;

void initBoard(BRD *);
void printBoard(int, BRD *, int, int);
bool isFull(BRD *);
bool isWinner(BRD *);
void player1(BRD *);
void player2(BRD *);
void referee(BRD *);
bool isValid(int, BRD *);


int main(int argc, char const *argv[])
{
    BRD *p = malloc(sizeof(BRD));
    initBoard(p);
    printBoard(15, p, size, size);



    pthread_t p1, p2, r;

    
    pthread_create(&p1, NULL, (void *) player1, p);
    pthread_create(&p2, NULL, (void *) player2, p);
    pthread_create(&p2, NULL, (void *) referee, p);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(r, NULL);

    printf("I am here\n");

    return 0;
}

void initBoard(BRD *b)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            (*(b)).buffer[i][j] = 0;
    }
    sem_init(&(*(b)).ref, 1, 1);
    sem_init(&(*(b)).empty, 1, 0);
    sem_init(&(*(b)).full, 1, 0);
    (*(b)).gameon = true;
}

void printBoard(int c, BRD *b, int row, int col)
{
    printf("\t\t");
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {   
            printf("%d ", (*(b)).buffer[i][j]);
        }
        printf("\n\t\t");
    }
    printf("---------------%d -- (%d, %d)\n", c, row, col);
}

bool isFull(BRD *b)
{
    bool v = true;
    for (size_t i = 0; (i < size) && v; i++)
    {
        for (size_t j = 0; (j < size) && v; j++)
        {
            v = ((*(b)).buffer[i][j] != 0) && v;
        }
    }
    return v;
}

void player1(BRD *p)
{
    int num,row,col=0;
    while((*(p)).gameon){
        sem_wait(&(*(p)).empty);
        if(!(*(p)).gameon)
            pthread_exit(NULL);
        
        printf("Player1's turn:\n");
        printf("player 1 row: ");
        scanf("%d", &row);
        printf("player 1 col: ");
        scanf("%d", &col);
        printf("player 1 num: ");
        scanf("%d", &num);
        while(!isValid(num,p)){
            printf("Invalid input. player 1 row : ");
            scanf("%d", &row);
            printf("player 1 col: ");
            scanf("%d", &col);
            printf("player 1 num: ");
            scanf("%d", &num);
        }
        (*(p)).buffer[row][col] = num;
        (*(p)).gameon = !isWinner(p);
        if(!(*(p)).gameon)
        {
            printBoard(15, p, row, col);
            printf("\n\t ***** player 1 wins! congrats! ***** \n");
            sem_post(&(*(p)).full);
            pthread_exit(NULL);
        }

        (*(p)).gameon = !isFull(p);
        if(!(*(p)).gameon)
        {
            printBoard(15, p, row, col);
            printf("\n\t no winner; draw game!\n");
            sem_post(&(*(p)).full);
            pthread_exit(NULL);
        }
        sem_post(&(*(p)).ref);
    }
}

void player2(BRD *p)
{
     int num,row,col=0;
    while((*(p)).gameon){
        sem_wait(&(*(p)).full);
        if(!(*(p)).gameon)
            pthread_exit(NULL);
        
        printf("Player2's turn:\n");
        printf("player 2 row: ");
        scanf("%d", &row);
        printf("player 2 col: ");
        scanf("%d", &col);
        printf("player 2 num: ");
        scanf("%d", &num);
        while(!isValid(num,p)){
            printf("Invalid input. player 2 row : ");
            scanf("%d", &row);
            printf("player 2 col: ");
            scanf("%d", &col);
            printf("player 2 num: ");
            scanf("%d", &num);
        }
        (*(p)).buffer[row][col] = num;
        (*(p)).gameon = !isWinner(p);
        if(!(*(p)).gameon)
        {
            printBoard(15, p, row, col);
            printf("\n\t ***** player 2 wins! congrats! ***** \n");
            sem_post(&(*(p)).empty);
            pthread_exit(NULL);
        }

        (*(p)).gameon = !isFull(p);
        if(!(*(p)).gameon)
        {
            printBoard(15, p, row, col);
            printf("\n\t no winner; draw game!\n");
            sem_post(&(*(p)).empty);
            pthread_exit(NULL);
        }
        sem_post(&(*(p)).ref);
    }
    
}

void referee(BRD *p)
{
   int num,row,col=0;
   while((*(p)).gameon){
    num = rand()%99 +1;
    if(num%2 ==1){
        printf("ref is talking: token is %d therefore player 1 makes the next move\n", num);
        sem_post(&(*(p)).empty);
        sem_wait(&(*(p)).ref);
    }else{
        printf("ref is talking: token is %d therefore player 2 makes the next move\n", num);
        sem_post(&(*(p)).full);
        sem_wait(&(*(p)).ref);
    }
   }
   printf("The game is over.");
   
}

bool isWinner(BRD *p)
{
    for(int i =0; i<3; i++){
        int sum = 0;
        for(int j = 0; j<3; j++){
            sum+= (*(p)).buffer[i][j];
        }
        if (sum==15){
            return true;
        }
    }
    for(int j =0; j<3; j++){
        int sum = 0;
        for(int i = 0; i<3; i++){
            sum+= (*(p)).buffer[i][j];
        }
        if (sum==15){
            return true;
        }
    }
    if((*(p)).buffer[0][0]+(*(p)).buffer[1][1]+ (*(p)).buffer[2][2]==15){
         return true;
    }
    if((*(p)).buffer[0][2]+(*(p)).buffer[1][1]+ (*(p)).buffer[2][0]==15){
         return true;
    }
    return false;
}

bool isValid(int val, BRD *b)
{
    if(val<1 || val>9){
        return false;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((*(b)).buffer[i][j] != '0' && !isFull(b)) {
                return false;
            }
        }
    }
    return true;
}