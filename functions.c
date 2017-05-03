#include "functions.h"

unsigned long HashToIndex(const char *hash){
    char string[5];
    int i;
    for(i=0; i<4; i++){
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

void LoadXMLToTable(FILE* fp, tx_outputs **table){
    mxml_node_t *xml;
    mxml_node_t *root;
    mxml_node_t *tree;
    mxml_node_t *tx_node;
    mxml_node_t *bl_node;

    const char *tx_hash;
    unsigned long index_from_hash;

    tx_outputs *txo;
    tx_outputs *cursor;

    unsigned long long i;
    unsigned long long number_of_outputs;

    xml = mxmlNewXML("1.0");
    root = mxmlNewElement(xml, "blocks");
    printf("LoadXMLToTable: Inizio caricamento file XML...\n");
    tree = mxmlLoadFile(root, fp, MXML_TEXT_CALLBACK);
    printf("Completato!\n");

    bl_node = mxmlFindPath(xml, "blocks/block");
    bl_node = mxmlWalkPrev(bl_node, root, MXML_DESCEND);
    tx_node = mxmlFindPath(bl_node, "tx");
    tx_node = mxmlWalkPrev(tx_node, root, MXML_DESCEND);

    i=0;

    while(tx_node != NULL){
        i++;
        printf("LoadXMLToTable: Aggiungo alla tabella la tx %llu\n", i);
        tx_hash = mxmlElementGetAttr(tx_node, "hash");
        index_from_hash = HashToIndex(tx_hash);
        number_of_outputs = CountOuts(tx_node, root);
        txo = malloc(sizeof(tx_outputs));
        strncpy(txo->hash, tx_hash, 64);
        txo->hash[64] = '\0';
        txo->outs_length = number_of_outputs;
        txo->outs = ArrayOfTxOuts(tx_node, root, number_of_outputs);
        txo->next = NULL;

        if(table[index_from_hash] == NULL){
            table[index_from_hash] = txo;
        }
        else{
            //COLLISIONE!
            cursor = table[index_from_hash];
            while(cursor->next != NULL){
                cursor = cursor->next;
            }
            cursor->next = txo;
        }
        NextTx(&tx_node, &bl_node, root);
    }

    printf("LoadXMLToTable: Popolamento tabella completato. Libero la memoria...\n");
    mxmlDelete(xml);
    printf("LoadXMLToTable: Memoria Liberata.\n");
}
