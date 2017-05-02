#include "functions.h"

unsigned long HashToIndex(const char *hash){
    char string[5];
    for(int i=0; i<4; i++){
        string[i] = hash[i];
    }
    string[4] = '\0';
    char *end;
    return strtoul(string, &end, 16);
}

output *ArrayOfTxOuts(mxml_node_t *current_tx, mxml_node_t *tree, unsigned long long number){
    output *array;
    array = malloc(sizeof(output) * number);

    unsigned long long i;
    mxml_node_t *outputs;
    mxml_node_t *address;
    const char *text;
    size_t text_length;

    outputs = mxmlFindPath(current_tx, "outputs/output");
    outputs = mxmlWalkPrev(outputs, tree, MXML_DESCEND);
    for(i=0;i<number;i++){
        address = mxmlFindPath(outputs, "address");
        text = mxmlGetText(address, NULL);
        text_length = strlen(text);
        strncpy(array[i].address, text, text_length);
        array[i].address[text_length] = '\0';
        //printf("%s\n", array[i].address);
        //printf("%i\n",array[i].address[text_length]);
        outputs = mxmlGetNextSibling(outputs);
        outputs = mxmlGetNextSibling(outputs);
        if(outputs == NULL){
            break;
        }
    }
    return array;
}
