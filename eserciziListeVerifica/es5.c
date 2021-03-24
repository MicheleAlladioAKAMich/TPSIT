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

struct El *merge(struct El *l1, struct El *l2){
    struct El *l3 = (struct El*) malloc(sizeof(struct El));
    while(l1->next != NULL){
        l3->valore = l1->valore;
        l1 = l1->next;
        l3 = l3->next;
    }
    while(l2->next != NULL){
        l3->valore = l2->valore;
        l2 = l2->next;
        l3 = l3->next;
    }
    l3->next = NULL;
    return l3;
}

int main(){
    int n;
    struct El* lista1;
    struct El* lista2;
    struct El* lista3;
    struct El* l1;
    struct El* l2;
    lista1=NULL; /* si inizializza la lista a NULL */
    lista2=NULL; /* si inizializza la lista a NULL */
    int cnt = 0;

    do{
        printf("Inserisci un naturale o -1 per terminare\n");
        scanf("%d",&n);
        if (n>=0){
            if (lista1==NULL) /* se la lista è vuota */{
                /* alloca lo spazio per la lista  */

                lista1 = (struct El*) malloc(sizeof(struct El));

                l1 = lista1;
            }else{ /* se la lista contiene qualcosa */
    
                /* viene allocato lo spazio per il campo successivo della lista */

                l1->next = (struct El*) malloc(sizeof(struct El));

                l1 = l1->next;
            }
            l1->valore = n; /* si assegna al valore della posizione corrente della lista n */
            l1->next = NULL; /* si assegna al campo successivo della lista NULL */
            cnt++;
        }
    } while (n>=0);

    printf("numeri inseriti: \n");
    l1 = lista1;
    while (l1!=NULL){
        printf("%d - %p \n",l1->valore, l1->next);
        l1=l1->next; /* ad l si assegna il prossimo campo di l */
    }

    printf("\n");

    ordinamento(lista1, cnt);

    l1=lista1;
    while (l1!=NULL){
        printf("%d - %p \n",l1->valore, l1->next);
        l1=l1->next; /* ad l si assegna il prossimo campo di l */
    }

    cnt = 0;

    do{
        printf("Inserisci un naturale o -1 per terminare\n");
        scanf("%d",&n);
        if (n>=0){
            if (lista2==NULL) /* se la lista è vuota */{
                /* alloca lo spazio per la lista  */

                lista2 = (struct El*) malloc(sizeof(struct El));

                l2 = lista2;
            }else{ /* se la lista contiene qualcosa */
    
                /* viene allocato lo spazio per il campo successivo della lista */

                l2->next = (struct El*) malloc(sizeof(struct El));

                l2 = l2->next;
            }
            l2->valore = n; /* si assegna al valore della posizione corrente della lista n */
            l2->next = NULL; /* si assegna al campo successivo della lista NULL */
            cnt++;
        }
    } while (n>=0);

    printf("numeri inseriti: \n");
    l2 = lista2;
    while (l2!=NULL){
        printf("%d - %p \n",l2->valore, l2->next);
        l2=l2->next; /* ad l si assegna il prossimo campo di l */
    }

    printf("\n");

    ordinamento(lista2, cnt);

    l2=lista2;
    while (l2!=NULL){
        printf("%d - %p \n",l2->valore, l2->next);
        l2=l2->next; /* ad l si assegna il prossimo campo di l */
    }

    lista3 = merge(lista1, lista2);    

    while (lista3!=NULL){
        printf("%d - %p \n",lista3->valore, lista3->next);
        lista3 = lista3->next; /* ad l si assegna il prossimo campo di l */
    }

    printf("\n");
    return 0;
}   