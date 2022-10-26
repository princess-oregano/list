#ifndef DUMP
#define DUMP

#include <stdio.h>
#include "list.h"

// Opens file to dump to.
void
open_dump(const char *filename);
// List dump.
void
list_dump(const list_t *list);

#endif // DUMP_H

