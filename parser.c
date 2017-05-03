#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(){
    unsigned long long i;
    FILE *fp, *result_file;
    tx_outputs *cursor;

    tx_outputs **table;
    table = malloc(0xffff * sizeof(tx_outputs*));
    for(i=0;i<0xffff;i++){
        table[i] = NULL;
    }


    fp = fopen("file.xml", "r");
    result_file = fopen("fileresult_", "a");
    LoadXMLToTable(fp, table);
    fp = fopen("file.xml", "r");
    ParseXML(fp, table, result_file);

    /*
    cursor = table[19338];

    do{
        printf("%llu: %s\n", i, cursor->hash);
        i++;
        cursor = cursor->next;
    }while(cursor != NULL);
    getchar();
    */



}
