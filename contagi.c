#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define LUNG 50

typedef struct regione{
    char nome[LUNG];
    int terapia;
    int tot;
}Regione;

int numRighe(FILE *f){
    int cnt = 0;
    char car;

    while(fscanf(f, "%c", &car) != EOF){
            if(car == '\n') //quando nel file si va a capo incremento il numero di righe
                cnt++;
    }
    return cnt;
}

void leggiFile(FILE *f, Regione *r){
    char *riga = (char*) malloc(200 * sizeof(char));    //puntatore per le righe del file
    int k = 0;

    printf("LISTA:\n");

    while(fgets(riga, 200, f)){ //legge una riga intera del file
        strcpy((r+k)->nome, strtok(riga, ",")); //copia nella stringa del nome ciò che legge fino alla prima virgola di ogni riga
        (r+k)->terapia = atoi(strtok(NULL, ","));   //atoi permette di convertire una stringa in un intero
        (r+k)->tot = atoi(strtok(NULL, ","));
        k++;
    }
    free(riga); //disalloca lo spazio per la riga
}

void topIntensiva(Regione *r, int n){
    Regione *max = (Regione*) malloc(n * sizeof(Regione));  //puntatore per il massimo delle terapie

    for(Regione *k = r; k - r < 3; k++){    //esegue il ciclo 3 volte per la top 3
        max->terapia = -1;   //numero sicuramente minore di ogni numero delle terapie intensive
        for(Regione *i = k; i - r < n; i++){
            if(max->terapia < i->terapia)   //se trova un numero di terapie maggiore quest'ultimo diventa il maggiore
                max = i;
        }
    printf("%s, ", max->nome);  //stampa il maggiore (lo fa 3 volte, 1 per ciclo)
    }
    free(max);  //disalloca lo spazio per il massimo 
}

int totTerapiaIntensiva(Regione *r, int n){
    int tot = 0;

    for(Regione *k = r; k - r < n; k++){    //cicla ogni regione e somma il numero di terapie intensive
        tot = tot + k->terapia;
    }
    return tot; //returna il totale ottenuto
}

void lessTotali(Regione *r, int n){
    Regione *min = (Regione*) malloc(n * sizeof(Regione));  //alloca lo spazio per il minimo

    for(Regione *k = r; k - r < 3; k++){    //esegue il ciclo 3 volte per la top 3
        min->tot = 999999999;  //numero sicuramente maggiore di tutti gli altri totali
        for(Regione *i = k; i - r < n; i++){
            if(min->tot > i->tot)   //se trova un numero di casi totali minore quest'ultimo diventa il minore
                min = i;
        }
        printf("%s, ", min->nome);  //printa il minore (lo fa 3 volte, 1 per ogni ciclo)
    }
    free(min);
}

void main(){
    FILE *fin;
    Regione *regioni;
    int nRighe; //numero delle righe del file
    int totIntensiva;   //totale delle terapie intensive

    if((fin = fopen("dati.csv", "r")) == NULL){
        printf("Il file non esiste");
    }else{

        //CONTO NUMERO RIGHE DEL FILE
        nRighe = numRighe(fin);

        //ALLOCO LO SPAZIO PER LE REGIONI
        regioni = (Regione*) malloc(nRighe * sizeof(Regione));

        //LETTURA DEL FILE
        fclose(fin);
        fin = fopen("dati.csv", "r");
        leggiFile(fin, regioni);

        //STAMPA DEL FILE
        for(Regione *k = regioni; k - regioni < nRighe; k++){
            printf("%s: TERAPIA INTENSIVA: %d, CONTAGI TOTALI: %d.\n", k->nome, k->terapia, k->tot);
        }

        //TOP 3 PIU' CASI IN TERAPIA INTENSIVA
        printf("\nTOP 3 REGIONI CON PIU' CASI IN TERAPIA INTENSIVA:\n");
        topIntensiva(regioni, nRighe);

        //TOTALE TERAPIE INTENSIVE
        totIntensiva = totTerapiaIntensiva(regioni, nRighe);
        printf("\n\nTOTALE TERAPIA INTENSIVA: %d\n", totIntensiva);

        //TOP 3 MENO CONTAGI TOTALI
        printf("\nTOP 3 REGIONI CON MENO CASI TOTALI:\n");
        lessTotali(regioni, nRighe);

    }
    free(regioni);  //disalloco lo spazio per le regioni
    fclose(fin);    //chiususra del file
}