/*
Author: Michele Alladio
Date: 08/10/20
es:
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define LUNG 100

void caricaStringa(char string[]){
    printf("inserisci la stringa: ");
    fflush(stdin);
    scanf("%s", string); 
}

int menu(){
    int n; 
    printf("premi 1 per fare l'encoding, premi 2 per fare il decoding: ");
    scanf("%d", &n);
    return n;
}

void encoding(char string[]){
    int cnt = 1, i;

    i = strlen(string);
    for(int k = 0; k < i; k++){
        if(string[k] == string[k + 1]){
                cnt++;
        }else{
            if(cnt == 1){
                printf("%c", string[k]);
                cnt = 1;
            }else{
                printf("%d%c", cnt, string[k]);
                cnt = 1;
            }
        }
    }
}

void decoding(char string[]){
    int temp, i;

    i = strlen(string);
    for(int k = 0; k < i; k++){
        if(string[k] >= '0' && string[k] <= '9'){
            temp = string[k];
            do{
                printf("%c", string[k + 1]);
                temp --;
            }while(temp > 0);
        }
    }
}

int main(){
    char s[LUNG];
    int opz;

    caricaStringa(s);
    opz = menu();

    switch(opz){
        case 1:
        encoding(s);
        case 2:
        decoding(s);
    }
    return 0;
}