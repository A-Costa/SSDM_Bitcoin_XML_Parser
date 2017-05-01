#include "xml_functions.h"

void NextTx(mxml_node_t **current_tx, mxml_node_t **current_block, mxml_node_t *tree){
    *current_tx = mxmlGetNextSibling(*current_tx);
    *current_tx = mxmlGetNextSibling(*current_tx);
    if(*current_tx == NULL){
        *current_block = mxmlGetNextSibling(*current_block);
        *current_block = mxmlGetNextSibling(*current_block);
        *current_tx = mxmlFindPath(*current_block, "tx");
        *current_tx = mxmlWalkPrev(*current_tx, tree, MXML_DESCEND);
    }
}

unsigned long long CountOuts(mxml_node_t *current_tx, mxml_node_t *tree){
    unsigned long long counter = 0;
    mxml_node_t *outputs;

    outputs = mxmlFindPath(current_tx, "outputs/output");
    outputs = mxmlWalkPrev(outputs, tree, MXML_DESCEND);
    while(outputs != NULL){
        counter++;
        outputs = mxmlGetNextSibling(outputs);
        outputs = mxmlGetNextSibling(outputs);
    }
    return counter;
}
