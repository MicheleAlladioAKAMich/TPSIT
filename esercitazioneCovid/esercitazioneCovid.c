/*
Author: Michele Alladio
Date: 24/09/20
es: esercizio covid
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define DIM 1000

void main(){
    float R, x[DIM], persContagiate = 1;
    int N, giorni = 0;

    printf("inserisci l'indice di contagio: ");
    scanf("%f", &R);
    printf("inserisci il numero di persone: ");
    scanf("%d", &N);

    do{
        x[giorni] = persContagiate;
        printf("%.2f ", x[giorni]);
        persContagiate = persContagiate * R;
        giorni++;
    }while(persContagiate < N);
    printf("\nIl numero di giorni impiegato per contagiare %d persone con un indice %.2f di contagio e': %d", N, R, giorni);
}
