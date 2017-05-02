#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xml_functions.h"
#include "functions.h"

int main(){
    FILE *fp;
    unsigned long long i, j;
    unsigned long long number_of_outputs;

    mxml_node_t *xml;
    mxml_node_t *root;
    mxml_node_t *tree;
    mxml_node_t *tx_node;
    mxml_node_t *bl_node;

    const char *text;
    const char *elem;
    const char *tx_hash;
    unsigned long index_from_hash;

    fp = fopen("file.xml", "r");

    tx_outputs **table = malloc(0xffff * sizeof(tx_outputs*));
    for(i=0;i<0xffff;i++){
        table[i] = NULL;
    }

    tx_outputs *txo;


    //inizialization of a new xml root node (this is needed because the file is not well formed)
    xml = mxmlNewXML("1.0");
    root = mxmlNewElement(xml, "blocks");
    tree = mxmlLoadFile(root, fp, MXML_TEXT_CALLBACK);

    bl_node = mxmlFindPath(xml, "blocks/block");
    bl_node = mxmlWalkPrev(bl_node, root, MXML_DESCEND);
    tx_node = mxmlFindPath(bl_node, "tx");
    tx_node = mxmlWalkPrev(tx_node, root, MXML_DESCEND);

    //for(i=0; i<1750; i++){
    while(tx_node != NULL){
        //text = mxmlGetText(tx_node, NULL);
        //elem = mxmlGetElement(tx_node);
        //printf("TX number: %llu\n", i);
        tx_hash = mxmlElementGetAttr(tx_node, "hash");
        index_from_hash = HashToIndex(tx_hash);
        //printf("   text:%s\n", text);
        //printf("   elem:%s\n", elem);
        printf("Hash:%s\n", tx_hash);
        printf("    Index:%lu\n", index_from_hash);

        number_of_outputs = CountOuts(tx_node, root);
        printf("    outputs: %llu\n", number_of_outputs);

        txo = malloc(sizeof(tx_outputs));
        strncpy(txo->hash, tx_hash, 64);
        txo->outs_length = number_of_outputs;
        txo->outs = ArrayOfTxOuts(tx_node, root, number_of_outputs);

        /*
        for(i=0; i<txo->outs_length; i++){
            printf("    TXO_Out %llu -> %s\n", i, txo->outs[i].address);
        }
        */

        table[index_from_hash] = txo;

        NextTx(&tx_node, &bl_node, root);
        //getchar();
    }
    //41098
    printf("*****\n");
    getchar();
    for(i=0; i<table[0]->outs_length; i++){
        printf("    TXO_Out %llu -> %s\n", i, table[43489]->outs[i].address);
    }
    getchar();
}
