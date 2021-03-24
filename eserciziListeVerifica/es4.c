#include <stdio.h>
#include <stdlib.h>
struct El{
    int valore;
    struct El* next;
};

void ordinamento(struct El *l, int n){
    struct El *kmin = (struct El*) malloc(sizeof(struct El));;
    for(struct El *k = l; k - l < n-1; k++){
        kmin = k;  
        l = l->next;   
        for(struct El *j = k + 1; j - k < n; j++){
            if(kmin->valore > j->valore)
                kmin = j;
        }
        if(kmin->valore != k->valore){
            struct El *temp = (struct El*) malloc(sizeof(struct El));
            temp = k;
            k = kmin;
            kmin = temp; 
        }           
    }
    return;
}

int main(){
    int n;
    struct El* lista;
    struct El* l;
    lista=NULL; /* si inizializza la lista a NULL */
    int cnt = 0;

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
            cnt++;
        }
    } while (n>=0);

    printf("numeri inseriti: \n");
    l = lista;
    while (l!=NULL){
        printf("%d - %p \n",l->valore, l->next);
        l=l->next; /* ad l si assegna il prossimo campo di l */
    }

    printf("\n");

    ordinamento(lista, cnt);

    l=lista;
    while (l!=NULL){
        printf("%d - %p \n",l->valore, l->next);
        l=l->next; /* ad l si assegna il prossimo campo di l */
    }
    printf("\n");
    return 0;
}   