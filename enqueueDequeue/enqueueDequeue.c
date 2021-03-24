/*
Author: Michele Alladio
es: CODE -> enqueue e dequqeue
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

