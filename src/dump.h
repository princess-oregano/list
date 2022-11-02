#ifndef DUMP
#define DUMP

#include <stdio.h>
#include "list.h"

// Write a graphviz interpretation of dump to a file.
void
list_graph_dump(const list_t *list);
// List dump.
void
list_text_dump(const list_t *list, FILE *stream);

#endif // DUMP_H

