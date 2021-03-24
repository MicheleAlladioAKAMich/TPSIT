#include <stdio.h>
#include <stdlib.h>
struct El{
    int valore;
    struct El* next;
};

int main(){
    int n;
    struct El* lista;
    struct El* l;
    lista=NULL; /* si inizializza la lista a NULL */

    do{
        printf("Inserisci un naturale o -1 per terminare\n");
        scanf("%d",&n);
        if (n>=0){
            if (lista==NULL) /* se la lista è vuota */{
                /* alloca lo spazio per la lista  */

                lista = (struct El*) malloc(sizeof(struct El));

                l = lista;
            }else{ /* se la lista contiene qualcosa */
    
                /* viene allocato lo spazio per il campo successivo della lista */

                l->next = (struct El*) malloc(sizeof(struct El));

                l = l->next;
            }
            l->valore = n; /* si assegna al valore della posizione corrente della lista n */
            l->next = NULL; /* si assegna al campo successivo della lista NULL */
        }
    } while (n>=0);

    l=lista; /* si assegna ad l la lista */
    printf("numeri inseriti: \n");
    while (l!=NULL){
        printf("%d - %p \n",l->valore, l->next);
        l=l->next; /* ad l si assegna il prossimo campo di l */
    }
    printf("\n");
    return 0;
}       