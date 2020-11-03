/*
Author: Michele Alladio
Date: 14-10-20
es: legge una serie di canzoni da un file canzoni.csv e crea una playlist random usando le canzoni lette dal file
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define DIM 100
#define LUNG 20

typedef struct canzone{
    char nomeCanzone[DIM];
    char nomeAutore[DIM];
    int numero;
    int rand;
}Canzone;

int leggiFile(FILE *f, Canzone c[], int nc){
    int cnt = 0;
    /*
    0 -> Numero canzone
    1 -> Nome canzone
    2 -> Autore canzone
    */
    char car;
    char parola[LUNG];

    while(fscanf(f, "%c", &car) != EOF){
        if(car == ','){
            parola[strlen(parola)] = '\0';
            switch(cnt){
                case 0: 
                    c[nc].numero = (nc) + 1;
                break;
                case 1:    
                    strcpy(c[nc].nomeCanzone, parola);
                break;
                case 2:
                    strcpy(c[nc].nomeAutore, parola);
                break;
            }
            cnt = (cnt + 1) % 3;    //incremento cnt (quando cnt è > 3 torna a 0)
            memset(&parola[0], 0, sizeof(parola));  //azzera la parola
            if(cnt == 0)    //se ho finito di leggere la parola
                nc = nc + 1;   //incremento contatore canzoni
        }else{
            parola[strlen(parola)] = car;   //aggiunge alla fine della parola il carattere letto
        }
    }
    return nc;
}

void listaRandom(Canzone c[], int n){
    int nRand, cnt = 0;
    int numeriUsciti[n];    //vettore per il confronto dei numeri random che vengono estratti

    srand(time(NULL));

    //inizializzazione delle celle di numeriUsciti[] a 0 per il confronto
    for(int k = 0; k < n; k++){
        numeriUsciti[k] = 0;
    }

    for(cnt = 0; cnt < n+1; cnt++){

        //confronto ed eventuale scarto dei numeri random
        do{
            nRand = rand() % (n + 1) + 1;
            //printf("%d ",nRand[cnt]); //se si vuole vedere come funziona il ciclo per lo scarto dei numeri random già usciti 
        }while(nRand == numeriUsciti[0] || nRand == numeriUsciti[1] || nRand == numeriUsciti[2] ||
                nRand == numeriUsciti[3] || nRand == numeriUsciti[4] || nRand == numeriUsciti[5] || 
                nRand == numeriUsciti[6] || nRand == numeriUsciti[7] || nRand == numeriUsciti[8] || 
                nRand == numeriUsciti[9] || nRand == numeriUsciti[10]);
        
        numeriUsciti[cnt] = nRand; //carica nella cella corrispondente dei numeri usciti il numero random estratto
        
        //confronta il numero random con i numeri delle canzoni
        for(int k = 0; k < n; k++){                       
            if(c[k].numero == nRand)
                printf("%d, %s, %s.\n", c[k].numero, c[k].nomeCanzone, c[k].nomeAutore);
        }
    }
}

void main(){
    FILE *fin;
    Canzone canzoni[LUNG];
    int nCanzoni = 0;

    if((fin = fopen("canzoni.csv", "r")) == NULL){
        printf("Il file non esiste");
    }else{
        nCanzoni = leggiFile(fin, canzoni, nCanzoni);   //restituisce il numero delle canzoni nel file

        //visualizzazione canzoni
        for(int k = 0; k < nCanzoni; k++){
            printf("%d, %s, %s.\n", canzoni[k].numero, canzoni[k].nomeCanzone, canzoni[k].nomeAutore);
        }

        //crea la playlist random
        printf("\nECCO LA TUA PLAYLIST:\n");
        listaRandom(canzoni, nCanzoni);
    }   
}