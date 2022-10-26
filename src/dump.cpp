#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include "dump.h"

// Stream of dump output. By default is stderr.
FILE *STREAM = stderr;
FILE *GRAPH = nullptr;

// Opens file to dump to.
static void
open_dump()
{
        DIR* dir = opendir("dmp");
        if (dir) {
                closedir(dir);
        } else if (ENOENT == errno) {
                system("mkdir dmp");
        } else {
                fprintf(stderr, "Couldn't make a directory for dumps.\n");
        }

        char filename[] = "dmp/DUMP_XXXXXX";

        STREAM = fdopen(mkstemp(filename), "w");
}

void
make_graph_dump(const list_t *list)
{
        int i = 0;

        open_dump();

        fprintf(STREAM, 
        "digraph G {\n"
        "ranksep = 1.5\n"
        "graph [dpi = 100]\n"
        "splines = ortho\n"
        "{rank = min;\n"
        "above_node[label = \"Top inv\", width = 3, style = invis];\n}\n"
        "{rank = same;\n");
        
        for (i = 0; i < list->cap; i++) {
                fprintf(STREAM,
                "       "
                "node%d [shape = record, "
                "label = \"idx\\n %d | {next \\n %d | prev\\n %d} | val\\n %d\"];\n", 
                i, i, list->elem[i].next, list->elem[i].prev, list->elem[i].data);
        }

        fprintf(STREAM, "}\n");

        fprintf(STREAM,
        "{rank = max;\n"
        "	below_node[label = \"Bot inv\", width = 3, style = invis];\n"
        "}\n");
        
        fprintf(STREAM,
        "above_node -> node0 [style=invis];\n"
        "below_node -> node0 [style=invis];\n");

        for (i = 0; i < list->cap - 1; i++) {
                fprintf(STREAM,
                "node%d -> ", i);        
        }

        fprintf(STREAM, 
        "node%d [weight = 5, style = invis];\n", i);

        for(i = 0; i < list->cap; i++) {
                fprintf(STREAM,
                "node%d -> node%d [weight = 0, color=red];\n", i, list->elem[i].next);
        }

        for(i = 0; i < list->cap; i++) {
                fprintf(STREAM,
                "node%d -> node%d [weight = 0, color=blue];\n", i, list->elem[i].prev);
        }

        fprintf(STREAM, "}\n");
}

void
list_dump(const list_t *list)
{
        open_dump();

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

