#include <stdlib.h>
#include <string.h>
#include <mxml.h>
#include "structs.h"


unsigned long HashToIndex(const char *hash);
output *ArrayOfTxOuts(mxml_node_t *current_tx, mxml_node_t *tree, unsigned long long number);
