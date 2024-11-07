#include "stdio.h"

/* do not modify function signatures, rather adapt your code */
int length (char *);
int size (char **);
int comparator (char *, char *);
char ** stringSort (char **);
void printArray (char **);

int main (void)
{
    /* your code here */
    int l1=length("compeng");
    printf("l1 : %d \n",l1);

    char *s[] ={"msku" , "compeng" , "os" , "2023" , NULL};
    int s1 = size(s);
    printf("s1 : %d \n",s1);

    int c1 = comparator("msku" , "ceng") ;
    printf("c1 : %d \n",c1);

    char *t[] = {"aab" , "aaaa" , "a" , "b" , "ba" , "a" , NULL};
    char** t1 = stringSort(t);
    printf("t1 : %s \n",*t1);

    stringSort(t);
    printArray(t);

    return 0;
}

/* your functions here */
int length (char *s){
    int i;
    for (i = 0; *(s+i) != '\0'; i++);
    return i; 
}
int size (char **s){
    int i;
    for (i = 0; *(s+i) != NULL; i++);
    return i;    
}
int comparator (char *s1, char *s2){
    int i = 0;
    while (s1[i] != '\0' || s2[i] != '\0') {
        if (s1[i] == s2[i]) {
            i++;
            continue;
        }
        if (s1[i] < s2[i]) {
            return 2;
        } else {
            return 1;
        }
    }
}
char ** stringSort (char **s){
    int n = 0;
    while (s[n] != NULL) {
        n++;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (comparator(s[j], s[j+1]) == 1) {
                char *temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }
    return s;
}
void printArray (char **s){
    int l = size(s);
    printf("{");
    for (int i = 0; i < l; i++)
    {
        if(i < l - 1)
            printf("%s,", *(s+i));
        else
            printf("%s", *(s+i));
    }
    printf("}\n");

}
