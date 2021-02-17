/*
Author: Michele Alladio
es: Scrivere una funzione che inverta una coda, ovvero produca una coda invertendo l’ordine
    degli elementi della coda di partenza. Suggerimento: utilizzare una pila.
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

void push(El **head, El *element){
    if(isEmpty(*head)){     //= if(isEmpty(*head) == 0)
        *head = element;
        element->next = NULL;
    }else{
        element->next = *head;
        *head = element;
    }
}

El *pop(El **head){
    El *ret = *head;

    if(isEmpty(*head)){
        return NULL;
    }else{
        *head = ret->next;
    }
    return ret;
}

int main(){
    El *headCoda = NULL;    //testa della coda
    El *tailCoda = NULL;    //fine della coda
    El *headPila = NULL;    //testa della pila
    El *elementCoda = NULL; //elemento della coda
    El *elementPila = NULL; //elemento della pila

    char risposta;

    do{
        elementCoda = (El*) malloc(sizeof(El)); //alloco un elemento della coda

        printf("Inserisci un numero: ");
        scanf("%d", &elementCoda->n);   //inserisco un elemento della coda

        enqueue(&headCoda, &tailCoda, elementCoda); //inserisco l'elemento della coda nella coda

        printf("Vuoi ancora inserire un numero? (s per inserire ancora): ");
        fflush(stdin);
        scanf("%c", &risposta);

        elementPila = (El*) malloc(sizeof(El));
        elementPila->n = elementCoda->n;    //assegno al valore dell'elemento della pila il valore dell'elemento della coda
        push(&headPila, elementPila);   //inserisco l'elemento della pila nella pila

    }while(risposta == 's' || risposta == 'S'); //fino a quando la risposta è s o S carico numeri


    while(!isEmpty(headCoda)){  //fino a quando la coda ha elementi
        El *stampa; //struttura di appoggio per stampare
        stampa = dequeue(&headPila, &tailCoda); /*ricevo come stampa la struttura returnata dalla dequeue che ha 
                                                come testa la testa della pila e come fine la ine della coda 
                                                (dequeue della coda iniziale invertita)*/                                            
        printf("%d ", stampa->n);   //stampa
        free(stampa);   //disalloco la stampa
    } 

    return 0;
}