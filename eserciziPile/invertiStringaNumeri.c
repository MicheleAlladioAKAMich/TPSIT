/*
Author: Michele Alladio
es: invertire una stringa di numeri utilizzando le pile
*/

typedef struct nodo{
    char valore;
    struct nodo *next;
}Nodo;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int isEmpty(Nodo *head){
    if(head == NULL)
        return 1;
    else
        return 0;   
}

Nodo *pop(Nodo **head){
    Nodo *ret = *head;

    if(isEmpty(*head)){
        return NULL;
    }else{
        *head = ret->next;
    }
    return ret;
}

void push(Nodo **head, Nodo *element){
    if(isEmpty(*head)){     //= if(isEmpty(*head) == 0)
        *head = element;
        element->next = NULL;
    }else{
        element->next = *head;
        *head = element;
    }
}

void stampa(Nodo **head){
    Nodo *appoggio;
    
    while(!isEmpty(head)){  //fino a quando la pila ha dei valori
        appoggio = pop(head);   //appoggio assume il valore dell'ultimo elemento inserito
        printf("%c ", appoggio->valore);    //stampa
        free(appoggio); //disalloco appoggio
    }
}

int main(){
    char numero[100];
    Nodo *head = NULL;
    Nodo *element = NULL;

    printf("Inserisci i numeri: ");
    fflush(stdin);
    scanf("%s", numero);

    for(int k = 0; numero[k] != '\0'; k++){
        element = (Nodo*) malloc(sizeof(Nodo));
        element->valore = numero[k];    //leggo la tringa e assegno il valore letto
        push(&head, element);   //creo la pila
    }

    stampa(&head);

    return 0;
}