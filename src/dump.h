#ifndef DUMP
#define DUMP

#include <stdio.h>
#include "list.h"

// Write a graphviz interpretation of dump to a file.
void
make_graph_dump(const list_t *list);
// List dump.
void
make_text_dump(const list_t *list);

#endif // DUMP_H

