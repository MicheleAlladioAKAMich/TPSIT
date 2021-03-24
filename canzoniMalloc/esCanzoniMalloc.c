/*
Author: Michele Alladio
Date: 14-10-20
es: legge una serie di canzoni da un file canzoni.csv e crea una playlist random usando le canzoni lette dal file
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define DIM 100
#define LUNG 20

typedef struct canzone{
    char nomeCanzone[DIM];
    char nomeAutore[DIM];
    int numero;
    int rand;
}Canzone;

int leggiFile(FILE *f, Canzone c[], int nc){
    int cnt = 0;
    
    0 -> Numero canzone
    1 -> Nome canzone
    2 -> Autore canzone
    */
   /*
    char car;
    char parola[LUNG];

    while(fscanf(f, "%c", &car) != EOF){
        if(car == ','){
            parola[strlen(parola)] = '\0';
            switch(cnt){
                case 0: 
                    c[nc].numero = (nc) + 1;
                break;
                case 1:    
                    strcpy(c[nc].nomeCanzone, parola);
                break;
                case 2:
                    strcpy(c[nc].nomeAutore, parola);
                break;
            }
            cnt = (cnt + 1) % 3;    //incremento cnt (quando cnt è > 3 torna a 0)
            memset(&parola[0], 0, sizeof(parola));  //azzera la parola
            if(cnt == 0)    //se ho finito di leggere la parola
                nc = nc + 1;   //incremento contatore canzoni
        }else{
            parola[strlen(parola)] = car;   //aggiunge alla fine della parola il carattere letto
        }
    }
    return nc;
}

bool controllo(int v[], int n, int k){
    bool ok = false;
    //controllo dell'eventuale presenza del numero random estratto
    for(int i = 0; i < k; i++){
        if(n == v[i]){
            ok = true;  //se il numero è gia presente ok diventa true
            i = k;  //viene forzata l'uscita dal ciclo
        }
    }
    return ok;
}

void listaRandom(Canzone c[], int n){
    int nRand[n];
    int cnt = 0;

    srand(time(NULL));

    for(cnt = 0; cnt < n; cnt++){

        //confronto ed eventuale scarto dei numeri random
        do{
            nRand[cnt] = rand() % n+1;
        }while(controllo(nRand, nRand[cnt], cnt));
        //printf("%d ", nRand[cnt]);  //se si vuole vedere la successione dei numeri random estratti
    }  

        
    //confronta il numero random con i numeri delle canzoni e stampa la playlist
    for(int k = 0; k < n; k++){    
        for(int i = 0; i < n; i++){                   
            if(c[k].numero == nRand[i])
                printf("%d, %s, %s.\n", c[i].numero, c[i].nomeCanzone, c[i].nomeAutore);
        }
    }
    
}

void main(){
    FILE *fin;
    Canzone canzoni[LUNG];
    int nCanzoni = 0;

    if((fin = fopen("canzoni.csv", "r")) == NULL){
        printf("Il file non esiste");
    }else{

        //lettura file
        nCanzoni = leggiFile(fin, canzoni, nCanzoni);   //restituisce il numero delle canzoni nel file

        //visualizzazione canzoni
        for(int k = 0; k < nCanzoni; k++){
            printf("%d, %s, %s.\n", canzoni[k].numero, canzoni[k].nomeCanzone, canzoni[k].nomeAutore);
        }

        //crea la playlist random
        printf("\nECCO LA TUA PLAYLIST:\n");
        listaRandom(canzoni, nCanzoni);
    }   
}
*/

/*
Author: Michele Alladio
Date: 14-10-20
es: legge una serie di canzoni da un file canzoni.csv e crea una playlist random usando le canzoni lette dal file
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define DIM 100
#define LUNG 20

typedef struct canzone{
    char nomeCanzone[DIM];
    char nomeAutore[DIM];
    int numero;
}Canzone;

int leggiNumRighe(FILE *f){
    char car;
    int cnt = 0;

    while(fscanf(f, "%c", &car) != EOF){
        if(car == '\n')
            cnt++;
    }
    return cnt;
}

void leggiFile(FILE *f, Canzone *p){
    int nc = 0; //contatore canzoni
    int cnt = 0;
    /*
    0 -> Numero canzone
    1 -> Nome canzone
    2 -> Autore canzone
    */
    char car;
    char* parola;
    parola = (char*)malloc(100 * sizeof(char));
    int cntCar = 0;   //contatore per i caratteri

    while(fscanf(f, "%c", &car) != EOF){
        if(car == ','){
            *(parola+cntCar)='\0';
            switch(cnt){
                case 0: 
                    (p + nc)->numero = nc + 1;
                break;
                case 1:    
                    strcpy((p + nc)->nomeCanzone, parola);
                break;
                case 2:
                    strcpy((p + nc)->nomeAutore, parola);
                break;
            }
            cnt = (cnt + 1) % 3;    //incremento cnt (quando cnt è > 3 torna a 0)
            cntCar = 0;
            if(cnt == 0)    //se ho finito di leggere la parola
                nc++;   //incremento contatore canzoni
        }else{
            *(parola + cntCar) = car;   //aggiunge alla fine della parola il carattere letto
            cntCar++;   //incremento contatore caratteri
        }
    }
    free(parola);
}

bool controllo(int *v, int n, int k){
    bool ok = false;
    //controllo dell'eventuale presenza del numero random estratto
    for(int *i = v; i-v < k; i++){
        if(n == *i){
            ok = true;  //se il numero è gia presente ok diventa true
            break;  //viene forzata l'uscita dal ciclo
        }
    }
    return ok;
}

void listaRandom(Canzone* p, int n){
    int *nRand;
    int cnt = 0;

    nRand = (int*) malloc(sizeof(int));

    srand(time(NULL));

    for(cnt = 0; cnt < n; cnt++){

        //confronto ed eventuale scarto dei numeri random
        do{
            *(nRand+cnt) = rand() % n;
            //printf("%d ", *(nRand+cnt));  //se si vuole vedere la successione dei numeri random estratti
        }while(controllo(nRand, *(nRand+cnt), cnt));
    }  

    //confronta il numero random con i numeri delle canzoni e stampa la playlist
    for(int *i = nRand; i-nRand < n; i++){                   
        printf("%d, %s, %s.\n", (p+*i)->numero, (p+*i)->nomeCanzone, (p+*i)->nomeAutore);
    }
}

void main(){
    FILE *fin;
    int nCanzoni = 0;   //numero delle canzoni
    Canzone *playlist;

    if((fin = fopen("canzoni.csv", "r")) == NULL){
        printf("Il file non esiste");
    }else{

        //lettura numero righe del file
        nCanzoni = leggiNumRighe(fin);

        //allocazione tramite malloc
        playlist = (Canzone*) malloc((nCanzoni) * sizeof(Canzone));

        //lettura file
        fclose(fin);
        fopen("canzoni.csv", "r");
        leggiFile(fin, playlist);  

        //visualizzazione canzoni
        for(Canzone *k = playlist; k - playlist < nCanzoni; k++){
            printf("%d, %s, %s.\n", k->numero, k->nomeCanzone, k->nomeAutore);
        }

        //crea la playlist random
        printf("\nECCO LA TUA PLAYLIST:\n");
        listaRandom(playlist, nCanzoni);
    }   
    free(playlist);
}