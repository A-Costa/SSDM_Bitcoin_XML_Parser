#include <mxml.h>

void NextTx(mxml_node_t **current_tx, mxml_node_t **current_block, mxml_node_t *tree);
unsigned long long CountOuts(mxml_node_t *current_tx, mxml_node_t *tree);
