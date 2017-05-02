#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xml_functions.h"
#include "structs.h"
#include "functions.h"

int main(){
    FILE *fp;
    unsigned long long i, j;
    unsigned long long outputs;

    mxml_node_t *xml;
    mxml_node_t *root;
    mxml_node_t *tree;
    mxml_node_t *tx_node;
    mxml_node_t *bl_node;

    const char *text;
    const char *elem;
    const char *attr;

    fp = fopen("file.xml", "r");

    //inizialization of a new xml root node (this is needed because the file is not well formed)
    xml = mxmlNewXML("1.0");
    root = mxmlNewElement(xml, "blocks");
    tree = mxmlLoadFile(root, fp, MXML_TEXT_CALLBACK);

    bl_node = mxmlFindPath(xml, "blocks/block");
    bl_node = mxmlWalkPrev(bl_node, root, MXML_DESCEND);
    tx_node = mxmlFindPath(bl_node, "tx");
    tx_node = mxmlWalkPrev(tx_node, root, MXML_DESCEND);

    for(i=0; i<1750; i++){
        //text = mxmlGetText(tx_node, NULL);
        elem = mxmlGetElement(tx_node);
        attr = mxmlElementGetAttr(tx_node, "hash");
        //printf("   text:%s\n", text);
        printf("   elem:%s\n", elem);
        printf("   attr:%s\n", attr);

        printf("tx number: %llu\n", i);
        outputs = CountOuts(tx_node, root);
        printf("outputs: %llu\n", outputs);
        NextTx(&tx_node, &bl_node, root);
        getchar();
    }
}
