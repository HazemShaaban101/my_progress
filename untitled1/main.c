//main.c
/* this is a simple program that tells you your favorite number is shit
 * and there are only two superior numbers */

#include <stdio.h>
#include "hazem.h"

int x;

int main(){
    printf("your favorite number is     ");
   scanf("%d", &x);


    if ((x==69)||(x==420)) {
        printf("nice");
    }
    else {
        printf("shame on you dumbass");
    }
    hazem();

    return 0;
}
