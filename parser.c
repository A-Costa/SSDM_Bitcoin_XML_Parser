#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(){
    FILE *fp;
    unsigned long long i;

    fp = fopen("file.xml", "r");

    tx_outputs **table = malloc(0xffff * sizeof(tx_outputs*));
    for(i=0;i<0xffff;i++){
        table[i] = NULL;
    }

    tx_outputs *cursor;

    LoadXMLToTable(fp, table);

    getchar();

    cursor = table[19338];

    do{
        printf("%llu: %s\n", i, cursor->hash);
        i++;
        cursor = cursor->next;
    }while(cursor != NULL);
    getchar();

}
