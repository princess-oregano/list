#ifndef DUMP
#define DUMP

#include <stdio.h>
#include "list.h"

// Writes a graphviz interpretation of dump to a file.
void
make_graph_dump(const list_t *list);
// List dump.
void
list_dump(const list_t *list);

#endif // DUMP_H

