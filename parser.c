#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(){
    unsigned long long i;
    FILE *fp, *result_file;
    tx_outputs *cursor;

    tx_outputs **table;
    printf("Alloco memoria per table...\n");
    table = malloc(0xffffffff * sizeof(tx_outputs*));
    printf("Inizializzo...\n");
    for(i=0;i<0xffffffff;i++){
        table[i] = NULL;
    }
    printf("Inizializzazione completata!\n");

    result_file = fopen("fileresult_", "a");

    fp = fopen("/local/s1953583/result_1", "r");
    LoadXMLToTable(fp, table);
    fp = fopen("/local/s1953583/result_2", "r");
    LoadXMLToTable(fp, table);
    fp = fopen("/local/s1953583/result_3", "r");
    LoadXMLToTable(fp, table);
    fp = fopen("/local/s1953583/result_4", "r");
    LoadXMLToTable(fp, table);

    //FINE CARICAMENTO IN TABELLA

    fp = fopen("/local/s1953583/result_1", "r");
    ParseXML(fp, table, result_file);
    fp = fopen("/local/s1953583/result_2", "r");
    ParseXML(fp, table, result_file);
    fp = fopen("/local/s1953583/result_3", "r");
    ParseXML(fp, table, result_file);
    fp = fopen("/local/s1953583/result_4", "r");
    ParseXML(fp, table, result_file);

    free(table);
}
