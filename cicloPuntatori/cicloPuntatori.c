/*
Author: Michele Alladio
Date: 08/10/20
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int main(){
    int *pi;
    int vet[5] = {0,1,2,3,4};

    for(pi = vet; pi - vet < 5; pi++){
        printf("INDIRIZZO: %p\n", pi);
        printf("VALORE DELLA CELLA: %d\n", *pi);
        printf("POSIZIONE NEL VETTORE: %d\n", pi - vet);
        printf("============================\n");
    }
}
