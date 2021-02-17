/*
Author: Michele Alladio
es: Implementare le funzioni pop e push usando la enqueue e la dequeue.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct el{
    int n;
    struct el *next;
}El;

int isEmpty(El *head){
    if(head == NULL)
        return 1;
    else
        return 0;   
}

void enqueue(El **head, El **tail, El *element){
    if(isEmpty(*head))
        *head = element;
    else
        (*tail)->next = element;

    *tail = element;
    element->next = NULL;
}

El *dequeue(El **head, El **tail){
    El *ret = *head;

    if(isEmpty(*head))
        return NULL;
    else
        *head = ret->next;

    if(*head == NULL)
        *tail = NULL;
    
    return ret;
}

void push(El **head, El **tail, El *element){
    enqueue(head, tail, element); 
}

El *pop(El **head, El **tail){
    El *ret = (El*) malloc(sizeof(El));
    El *testa = NULL;   //testa di appoggio
    El *fondo = NULL;   //coda di appoggio

    if(!isEmpty(*head)){
        do{ 
            ret = dequeue(head, tail);  /*ret assume un valore diverso fino a quando la coda non è vuota
                                        (assume il valore della head della coda)*/

            if(!isEmpty(*head)) //se la coda non è vuota ricrea la coda
                push(&testa, &fondo, ret);

        }while(!isEmpty(*head));    //fino a quando la coda ha degli elementi

        //si assegna alla coda originale la coda di appoggio distruggendo la coda di appoggio
        *head = testa;
        *tail = fondo;  

        return ret; //return dell'elemento
    }
    *tail=NULL; //se la coda è vuota non esiste una coda
    return NULL;
    
}

int main(){
    char risposta;
    El *head = NULL;
    El *element = NULL;
    El *tail = NULL;

    do{
        element = (El*) malloc(sizeof(El));

        printf("Inserisci il numero: ");
        scanf("%d", &element->n);
        
        push(&head, &tail, element);    //carico gli elementi nella coda

        printf("Vuoi ancora inserire un numero? (s per inserire ancora): ");
        fflush(stdin);
        scanf("%c", &risposta);

    }while(risposta == 's' || risposta == 'S'); //fino a quando la risposta è s o S carico numeri

    while(!isEmpty(head)){  //fino a quando la coda ha elementi
        printf("%d ", pop(&head, &tail)->n);   //stampa
    }

    return 0;
}