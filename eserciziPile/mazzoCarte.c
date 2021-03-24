/*
Author: Michele Alladio
es: Distribuire un mazzo di carte caricato opportunamente in una pila a due giocatori usando le pile
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAXCARTE 13

typedef struct mazzo{
    char seme;  //seme carta
    int numero; //numero carta
    struct mazzo *next;
}Mazzo;

int isEmpty(Mazzo *head){
    if(head == NULL)    //se la pila è vuota
        return 1;
    else
        return 0;   
}

void push(Mazzo **head, Mazzo *element){
    if(isEmpty(*head)){     //se la pila è vuota
        *head = element;    //a head si assegna l'elemento  
        element->next = NULL;   //il prossimo elemento viene inizializzato a NULL
    }else{
        element->next = *head;  //l'elemento successivo diventa la head della pila
        *head = element;  //a head si assegna l'elemento   
    }
}

Mazzo *pop(Mazzo **head){
    Mazzo *ret = *head;

    if(isEmpty(*head)){ //se la pila è vuota
        return NULL;
    }else{
        *head = ret->next;  //la head diventa l'elemento successivo
    }
    return ret; //return della struttura
}

void stampa(Mazzo **head){
    Mazzo *appoggio;    //variabile di appoggio
    
    while(!isEmpty(*head)){  //fino a quando la pila ha dei valori
        appoggio = pop(head);   //appoggio assume il valore dell'ultimo elemento inserito
        printf("%d %c - ", appoggio->numero, appoggio->seme);    //stampa
        free(appoggio); //disalloco appoggio
    }
}


int main(){
    //PILA PRINCIPALE 
    Mazzo *head = NULL;
    Mazzo *carta = NULL; 

    //PILA CARTE BOB
    Mazzo *cartaBob = NULL;
    Mazzo *headBob = NULL;

    //PILA CARTE ALICE
    Mazzo *cartaAlice = NULL;
    Mazzo *headAlice = NULL;

    int turno;

    srand(time(NULL));  //randomizzazione del seme
    
    //CICLI DI CARICAMENTO DELLE CARTE NELLA PILA PRINCIPALE (4 CICLI OGNUNO PER OGNI SEME)
    for(int k = 1; k <= MAXCARTE; k++){
        carta = (Mazzo*) malloc(sizeof(Mazzo));  //alloco un elemento della pila principale
        carta->seme = 'C';
        //carta->numero = rand() % MAXCARTE + 1;
        carta->numero = k;
        push(&head, carta);
    }

    for(int k = 1; k <= MAXCARTE; k++){
        carta = (Mazzo*) malloc(sizeof(Mazzo));  //alloco un elemento della pila principale
        carta->seme = 'P';
        //carta->numero = rand() % MAXCARTE + 1;
        carta->numero = k;
        push(&head, carta);
    }

    for(int k = 1; k <= MAXCARTE; k++){
        carta = (Mazzo*) malloc(sizeof(Mazzo));  //alloco un elemento della pila principale
        carta->seme = 'D';
        //carta->numero = rand() %  MAXCARTE + 1;
        carta->numero = k;
        push(&head, carta);
    }

    for(int k = 1; k <= MAXCARTE; k++){
        carta = (Mazzo*) malloc(sizeof(Mazzo));  //alloco un elemento della pila principale
        carta->seme = 'F';
        //carta->numero = rand() % MAXCARTE + 1;
        carta->numero = k;
        push(&head, carta);
    }

    //stampa(&head);    //per verificare il corretto caricamento della pila principale
    //printf("\n");

    while(!isEmpty(head)){
        turno = rand() % 2; //estrazione random di chi riceve la prima carta del turno
        
        if(turno == 1){ //bob riceve la prima carta
            cartaBob = (Mazzo*) malloc(sizeof(Mazzo));    //alloco un elemento della pila bob
            cartaBob = pop(&head);    //l'elemento della pila principale diventa l'elemento della pila di bob
            push(&headBob, cartaBob);      //riempio la pila di bob

            cartaAlice = (Mazzo*) malloc(sizeof(Mazzo));  //alloco un elemento della pila alice
            cartaAlice = pop(&head);      //l'elemento della pila principale diventa l'elemento della pila di alice
            push(&headAlice, cartaAlice);   //riempio la pila di alice
        }else{  //alice riceve la prima carta
            cartaAlice = (Mazzo*) malloc(sizeof(Mazzo));      //alloco un elemento della pila alice
            cartaAlice = pop(&head);      //l'elemento della pila principale diventa l'elemento della pila di alice
            push(&headAlice, cartaAlice);   //riempio la pila di alice

            cartaBob = (Mazzo*) malloc(sizeof(Mazzo));    //alloco un elemento della pila bob
            cartaBob = pop(&head);  //l'elemento della pila principale diventa l'elemento della pila di bob
            push(&headBob, cartaBob);   //riempio la pila di bob
        }
    }

    printf("MAZZO BOB:\n");
    stampa(&headBob);   //stampa del mazo di bob
    printf("\nMAZZO ALICE:\n");
    stampa(&headAlice); //stampa del mazzo di alice

    return 0;
}
