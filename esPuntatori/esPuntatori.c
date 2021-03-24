/*
Author: Michele Alladio
Date: 01/10/20
es: semplice esercizio dimostrativo sull'uso dei puntatori
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main(){
    int *pi;
    *pi = 15;
    printf("%p\n", pi);
    pi = pi + 1;
    printf("%p", pi);
    return 0;
}
