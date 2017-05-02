#include <stdlib.h>
#include <string.h>
#include "functions.h"

unsigned long hashToIndex(char *hash){
    char string[5];
    for(int i=0; i<4; i++){
        string[i] = hash[i];
    }
    string[4] = '\0';
    char *end;
    return strtoul(string, &end, 16);
}
