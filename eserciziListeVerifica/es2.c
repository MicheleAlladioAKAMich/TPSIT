#include <stdio.h>
#include <stdlib.h>
struct El{
    int valore;
    struct El* next;
};

void stampa(struct El *l){
    if (l!=NULL){
        printf("%d - %p \n",l->valore, l->next);
        stampa(l->next); /* ad l si assegna il prossimo campo di l */
    }
}

struct El *push(struct El *lista, int n){
    if (lista==NULL){   /* se la lista è vuota */
        /* alloca lo spazio per la lista  */
        lista = (struct El*) malloc(sizeof(struct El));
        
        lista->valore = n;
        lista->next = NULL;
    }else{ /* se la lista contiene qualcosa */
        struct El* l = lista;
        while(l->next != NULL){
            l = l->next;
        }
        
        /* viene allocato lo spazio per il campo successivo della lista */

        l->next = (struct El*) malloc(sizeof(struct El));
        l->next->valore = n;
        l->next->next = NULL;
    }
    return lista;
}

/*void push(struct El *lista, int n){
    struct El *l = lista;
    while(l->next != NULL){
        l = l->next;
    }
    l->next = (struct El*) malloc(sizeof(struct El));
    l->next->valore = n;
    l->next->next = NULL;
}*/

int main(){
    int valore;
    struct El* lista;
    lista=NULL; /* si inizializza la lista a NULL */

    do{
        printf("Inserisci un naturale o -1 per terminare\n");
        scanf("%d", &valore);
        if(valore >= 0)
            lista = push(lista, valore);
    }while(valore >= 0);
    
    printf("numeri inseriti: \n");
    stampa(lista);
    
    return 0;
}       