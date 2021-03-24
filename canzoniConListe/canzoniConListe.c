"""
Author: Michele Aladio
es: leggere da un file csv delle canzoni e creare una playlist random utilizzando le liste

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
    struct canzone *next;
}Canzone;

void push(Canzone *p, int n, char *titolo, char *autore){
    Canzone *pAppoggio; //lista con almeno un elemento
    pAppoggio = p;

    if(p == NULL){
        //p = (Canzone*) malloc(sizeof(Canzone));
        p->numero = n;
        strcpy(p->nomeCanzone, titolo);
        strcpy(p->nomeAutore, autore);
        p->next = NULL;
    }else{
        while(pAppoggio->next != NULL){
            pAppoggio = pAppoggio->next;
        }
        //in questo punto pAppoggio punta all'ultimo elemento della lista p
        pAppoggio->next = (Canzone*) malloc(sizeof(Canzone));
        pAppoggio->next->numero = n;
        strcpy(pAppoggio->next->nomeCanzone, titolo);
        strcpy(pAppoggio->next->nomeAutore, autore);
        pAppoggio->next->next = NULL;
    }
}

int leggiFile(FILE *f, Canzone *p){
    int cnt = 0;
    char *riga = (char*) malloc(200 * sizeof(char));
    int n;  //numero canzone
    char nC[100];   //nome canzone
    char nA[100];   //autore canzone

    while(fgets(riga, 200, f)){
        //assegnazione campi di p dal file
        n = atoi(strtok(riga, ","));
        strcpy(nA, strtok(NULL, ","));
        strcpy(nC, strtok(NULL, ","));
        push(p, n, nC, nA);
        cnt++;
    }
    free(riga);
    return cnt;
}

bool controllo(int *v, int n, int k){
    bool ok = false;
    //controllo dell'eventuale presenza del numero random estratto
    for(int *i = v; i-v < k; i++){
        if(n == *i){
            ok = true;  //se il numero è gia presente ok diventa true
            break;  //viene forzata l'uscita dal ciclo
        }
    }
    return ok;
}

void listaRandom(Canzone* p, int n){
    int *nRand;
    int cnt = 0;

    nRand = (int*) malloc(sizeof(int));

    srand(time(NULL));

    for(cnt = 0; cnt < n; cnt++){

        //confronto ed eventuale scarto dei numeri random
        do{
            *(nRand+cnt) = rand() % n;
            //printf("%d ", *(nRand+cnt));  //se si vuole vedere la successione dei numeri random estratti
        }while(controllo(nRand, *(nRand+cnt), cnt));
    }  

    //confronta il numero random con i numeri delle canzoni e stampa la playlist
    for(int *i = nRand; i-nRand < n; i++){                   
        printf("%d, %s, %s.\n", (p+*i)->numero, (p+*i)->nomeCanzone, (p+*i)->nomeAutore);
    }
}

int main(){
    FILE *fin;
    int nCanzoni;
    Canzone *primaCanzone = (Canzone*) malloc(sizeof(Canzone));

    if((fin = fopen("canzoni.csv", "r")) == NULL){
        printf("Il file non esiste");
    }else{

        //LETTURA FILE
        fclose(fin);
        fin = fopen("canzoni.csv", "r");
        nCanzoni = leggiFile(fin, primaCanzone);
        
        //printf("%d %s %s", primaCanzone->next->next->numero, primaCanzone->next->next->nomeCanzone, primaCanzone->next->next->nomeAutore);
        for(Canzone *k = primaCanzone->next->next; k != NULL; k = k->next){
            printf("%d: %s, %s.\n", k->numero, k->nomeCanzone, k->nomeAutore);
        }

        //LISTA RANDOM
        printf("\nECCO LA TUA PLYLIST:\n");
        listaRandom(primaCanzone, nCanzoni);
    }


    return 0;
}
