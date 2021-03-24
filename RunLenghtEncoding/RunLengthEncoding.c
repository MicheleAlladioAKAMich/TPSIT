/*
Author: Michele Alladio
Date: 08/10/20
es: algoritmo di Run Lenght Encoding
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define LUNG 100

void caricaStringa(char string[]){
    printf("inserisci la stringa: ");
    fflush(stdin);                      //pulisce il buffer di tastiera
    scanf("%s", string); 
}

int menu(){
    int n; 
    printf("premi 1 per fare l'encoding, premi 2 per fare il decoding: ");
    scanf("%d", &n);                                                           //scelta dell'utente
    return n;
}

void encoding(char string[]){
    int cnt = 1, i;

    i = strlen(string);                         //restituisce la lunghezza della stringa
    for(int k = 0; k < i; k++){
        if(string[k] == string[k + 1]){         //se il carattere è uguale al carattere precedente cnt viene incrementato
                cnt++;
        }else{
            if(cnt == 1){                       //se cnt vale 1 viene stampato solo il carattere
                printf("%c", string[k]);
                cnt = 1;
            }else{
                printf("%d%c", cnt, string[k]); //se cnt vale più di 1 prima del carattere viene stampato il valore assunto da cnt
                cnt = 1;
            }
        }
    }
}

void decoding(char string[]){
    int temp = 0, i;

    i = strlen(string);                         //restituisce la lunghezza della stringa
    for(int k = 0; k < i; k++){
        if(string[k] > 49 && string[k] < 58){  
            temp = string[k] - 48;              //trova il numero di volte per cui il carattere dev'essere stampato
            for(int i = 0; i < temp; i++){
                printf("%c", string[k + 1]);
            }
        }else{
            printf("%c", string[k]);            //se non vi è un numero il carattere viene stampato una sola volta
        }
    }
}

int main(){
    char s[LUNG];
    int opz;

    //inserimento della stringa
    caricaStringa(s);

    //scelta tra coding ed encoding  
    opz = menu();

    switch(opz){
        case 1:
        encoding(s);
        case 2:
        decoding(s);
    }
    return 0;
}
