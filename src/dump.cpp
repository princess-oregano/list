#include "dump.h"

// Stream of dump output. By default is stderr.
FILE *STREAM = stderr;

void
open_dump(const char *filename)
{
        FILE *stream = fopen(filename, "w");
        if (stream == nullptr) {
                fprintf(stderr, "Couldn't open %s\n", filename);
                return;
        }

        STREAM = stream;
}

void
list_dump(const list_t *list)
{
        fprintf(STREAM, "------------------DUMP---------------------------\n");
        fprintf(STREAM, "Free: %d\n", list->free);

        fprintf(STREAM, "Index: ");
        for (int i = 0; i <= list->cap; i++) {
                fprintf(STREAM, "%2d ", i);
        }
        fprintf(STREAM, "\n");

        fprintf(STREAM, "Data:  ");
        for (int i = 0; i <= list->cap; i++) {
                fprintf(STREAM, "%2d ", list->elem[i].data);
        }
        fprintf(STREAM, "\n");

        fprintf(STREAM, "Next:  ");
        for (int i = 0; i <= list->cap; i++) {
                fprintf(STREAM, "%2d ", list->elem[i].next);
        }
        fprintf(STREAM, "\n");

        fprintf(STREAM, "Prev:  ");
        for (int i = 0; i <= list->cap; i++) {
                fprintf(STREAM, "%2d ", list->elem[i].prev);
        }
        fprintf(STREAM, "\n");
        fprintf(STREAM, "---------------END OF DUMP-----------------------\n");
}

