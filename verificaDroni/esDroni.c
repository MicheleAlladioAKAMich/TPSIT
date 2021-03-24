"""
Author: Michele Alladio
Leggere le anomalie di un drone da un file e confrontarle con un secondo file per scoprire la latitudine e la longitudine a cui si sono 
presentati questi errori
"""

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define LUNG 50

typedef struct anomalia{
    int tempo;
    char tipo[LUNG];
}Anomalia;

typedef struct volo{
    int tempo;
    float lat;
    float longitudine;
}Volo;

int numRighe(FILE *f){
    int cnt = 0;
    char car;

    while(fscanf(f, "%c", &car) != EOF){
            if(car == '\n') //quando nel file si va a capo incremento il numero di righe
                cnt++;
    }
    return cnt;
}

void leggiFileVolo(FILE *f, Volo *v){
    char *riga = (char*) malloc(200 * sizeof(char));    //puntatore per le righe del file
    int k = 0;

    printf("LISTA VOLO:\n");

    while(fgets(riga, 200, f)){ //legge una riga intera del file
        (v+k)->tempo = atoi(strtok(riga, ",\n")); //atoi permette di convertire una stringa in un intero
        (v+k)->lat = atof(strtok(NULL, ",\n"));   //atof permette di convertire una stringa in un float
        (v+k)->longitudine = atof(strtok(NULL, ",\n"));
        k++;
    }
    free(riga); //disalloca lo spazio per la riga
}

void leggiFileAnomalie(FILE *f, Anomalia *a){
    char *riga = (char*) malloc(200 * sizeof(char));    //puntatore per le righe del file
    int k = 0;

    printf("LISTA ANOMALIE:\n");
    while(fgets(riga, 200, f)){ //legge una riga intera del file
        (a+k)->tempo = atoi(strtok(riga, ",\n"));   
        strcpy((a+k)->tipo, strtok(NULL, ",\n")); //copia la seconda stringa nella prima
        k++;
    }
    free(riga); //disalloca lo spazio per la riga
}

void stampaLatLong(FILE *fA, FILE *fV, Anomalia *a, Volo *v, int nRigheA, int nRigheV){
    for(Anomalia *k = a+1; k - a < nRigheA+1; k++){ //scorre le anomalie  scartando la prima riga
        for(Volo *i = v+1; i - v < nRigheV+1; i++){ //scorre i tempi nel file volo scartando la prima riga
            if(k->tempo == i-> tempo){  //individua il tempo dell'anomalia nel file dei tempi di volo
                printf("TIPO DI ERRORE: %s\nLATITUDINE ERRORE: %.3f, LONGITUDINE ERRORE: %.3f\n\n", k->tipo, i->lat, i->longitudine);
            }
        }
    }
}

void main(){
    FILE *fAnomalie;    //file anomalie
    FILE *fVolo;    //file di volo
    int nRigheAnomalie; //numero righe del file delle anomalie
    int nRigheVolo; //numero righe del file di volo
    Anomalia *anomalie;
    Volo *voli;

    if(((fAnomalie = fopen("Anomalie_drone.csv", "r")) == NULL) || ((fVolo = fopen("Volo_drone.csv", "r")) == NULL)){
        printf("Errore nella ricerca dei file");    //se non trova tutti e due i file printa un errore
    }else{
        //CALCOLO IL NUMERO DI RIGHE DEI FILE
        nRigheAnomalie = numRighe(fAnomalie);
        nRigheVolo = numRighe(fVolo);

        //ALLOCO LO SPAZIO PER I PUNTATORI TRAMITE MALLOC
        anomalie = (Anomalia*) malloc(nRigheAnomalie * sizeof(Anomalia));
        voli = (Volo*) malloc(nRigheVolo * sizeof(Volo));

        fclose(fAnomalie);
        fclose(fVolo);
        fAnomalie = fopen("Anomalie_drone.csv", "r");
        fVolo = fopen("Volo_drone.csv", "r");

        //LEGGO E (STAMPO SALTANDO LA PRIMA RIGA) IL CONTENUTO DEI DUE FILE
        leggiFileVolo(fVolo, voli);
        for(Volo *k = voli+1; k - voli < nRigheVolo+1; k++){
            printf("%d, %f, %f\n", k->tempo, k->lat, k->longitudine);
        }

        printf("\n");

        leggiFileAnomalie(fAnomalie, anomalie);
        for(Anomalia *k = anomalie+1; k - anomalie < nRigheAnomalie+1; k++){
            printf("%d, %s\n", k->tempo, k->tipo);
        }

        printf("\n");
        printf("\n");

        //INDIVIDUO LATITUDINE E LONGITUDINE DELLE ANOMALIE
        stampaLatLong(fAnomalie, fVolo, anomalie, voli, nRigheAnomalie, nRigheVolo);

        //DISALLOCO LO SPAZIO DEI PUNTATORI
        free(anomalie);
        free(voli);
    }
    //CHIUDO I FILE
    fclose(fAnomalie);
    fclose(fVolo);
}
