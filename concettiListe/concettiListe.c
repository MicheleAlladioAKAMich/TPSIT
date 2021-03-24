#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct nodo{
    int valore;
    struct nodo *successivo;
}Nodo;

Nodo *push(Nodo *lista, int n){
    if (lista==NULL){   /* se la lista è vuota */
        /* alloca lo spazio per la lista  */
        lista = (Nodo*) malloc(sizeof(Nodo));
        
        lista->valore = n;
        lista->successivo = NULL;
    }else{ /* se la lista contiene qualcosa */
        Nodo* l = lista;
        while(l->successivo != NULL){
            l = l->successivo;
        }
        
        /* viene allocato lo spazio per il campo successivo della lista */

        l->successivo = (Nodo*) malloc(sizeof(Nodo));
        l->successivo->valore = n;
        l->successivo->successivo = NULL;
    }
    return lista;
}

void stampaListaRicorsiva(Nodo *lista){
    //funzione ricorsiva
    if(lista == NULL){
        printf("----\n");
    }else{
        printf("%d ", lista->valore);
        stampaListaRicorsiva(lista->successivo);
    }
}

int lunghezzaListaIterativa(Nodo *lista){
    int cnt = 0;
    while(lista != NULL){
        lista = lista->successivo;
        cnt++;
    }
    return cnt;
}

int lunghezzaListaRicorsiva(Nodo *lista){
    if(lista == NULL){
        return 0;
    }else{
        //1 + lunghezzaListaRicorsiva(lista->successivo) + lunghezzaListaRicorsiva(lista->successivo->successivo) 
        //+ lunghezzaListaRicorsiva(lista->successivo->successivo) 
        //+ lunghezzaListaRicorsiva(lista->successivo->successivo->successivo) + ..... + 0

        return 1 + lunghezzaListaRicorsiva(lista->successivo);  //1 + 1 + 1 + 1 + 0 aggiunge 0 quando lista == NULL
    }
}

void deallocaListaRicorsiva(Nodo *lista){
    /*
    1->2->3->NULL
    deallocaListaRicorsiva(1->2->3->NULL)
    deallocaListaRicorsiva(2->3->NULL)
    deallocaListaRicorsiva(3->NULL)
    deallocaListaRicorsiva(NULL)
    e poi torna indietro ed esegue tutte le free:
    free(3)
    free(2)
    free(1)
    */
    if(lista != NULL){
        deallocaListaRicorsiva(lista->successivo);
        printf("deallocaLista: %d\n", lista->valore);   //per capire il funzionamento
        free(lista);
        printf("free: %d\n", lista->valore);    //per capire il funzionamento
    }
}

int main(){
    Nodo *lista;
    int lungIterativa, lungRicorsiva, valore;

    lista=NULL; /* si inizializza la lista a NULL */

    do{
        printf("Inserisci un naturale o -1 per terminare\n");
        scanf("%d", &valore);
        if(valore >= 0)
            lista = push(lista, valore);
    }while(valore >= 0);
    
    printf("numeri inseriti: \n");

    stampaListaRicorsiva(lista);
    lungIterativa = lunghezzaListaIterativa(lista);
    lungRicorsiva = lunghezzaListaRicorsiva(lista);
    printf("%d ", lungIterativa);
    printf("%d\n", lungRicorsiva);
    deallocaListaRicorsiva(lista);
    return 0;
}