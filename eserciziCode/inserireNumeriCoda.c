/*
Author: Michele Alladio
es: inserire una serie di numeri in una coda, stamparla e poi svuotarla.
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

int main(){
    El *head = NULL;    //testa della coda
    El *tail = NULL;    //fine della coda
    El *element = NULL; //elemento della coda
    char risposta;

    do{
        element = (El*) malloc(sizeof(El)); //alloco un elemento della coda

        printf("Inserisci un numero: ");
        scanf("%d", &element->n);

        enqueue(&head, &tail, element); //inserisco gli elementi nella coda

        printf("Vuoi ancora inserire un numero? (s per inserire ancora): ");
        fflush(stdin);
        scanf("%c", &risposta);

    }while(risposta == 's' || risposta == 'S'); //fino a quando la risposta è s o S carico numeri

    while(!isEmpty(head)){  //fino a quando la coda ha elementi
        El *stampa; //struttura di appoggio per stampare
        stampa = dequeue(&head, &tail);     /*dequeue della coda (parte dalla fine e va fino alla testa 
                                            togliendo gli elementi nello stesso modo in cui sono stati inseriti)*/
        printf("%d ", stampa->n);   //stampa
        free(stampa);   //disalloco la stampa
    }

    if(isEmpty(head))   //se la lista è vuota (controllo)
        printf("\nLista svuotata correttamente");  

    return 0;
}