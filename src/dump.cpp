#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "dump.h"
#include "log.h"

const int PNGFILENAME_SIZE = 100;

// Stream of dump output.
FILE *DMP_STREAM = nullptr;
char PNGFILENAME[PNGFILENAME_SIZE] = {};

// Opens file to which graph dump will be written.
static void
open_graph_dump()
{
        DIR* dir = opendir("dmp");
        if (dir) {
                closedir(dir);
        } else if (ENOENT == errno) {
                mkdir("dmp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        } else {
                fprintf(stderr, "Couldn't make a directory for dumps.\n");
        }

        char filename[] = "dmp/DUMP_XXXXXX";

        DMP_STREAM = fdopen(mkstemp(filename), "w");
        if (strlen(filename) >= PNGFILENAME_SIZE) {
                fprintf(stderr, "Filename is too long.\n");
                return;
        }

        memcpy(PNGFILENAME, filename, strlen(filename));
}

// Genetares .png image from given dot code
static void
generate_graph()
{
        char *cmd = (char *) calloc (200, sizeof(char));
        char *new_filename = (char *) calloc (100, sizeof(char));
        // calloc error?

        memcpy(cmd, "dot -Tpng ", strlen("dot -Tpng ")); // shouldn't evaluate in runtime

        memcpy(new_filename, PNGFILENAME, strlen(PNGFILENAME));
        new_filename = strcat(new_filename, ".png");

        cmd = strcat(cmd, PNGFILENAME);
        cmd = strcat(cmd, " > ");       // runtime ?
        cmd = strcat(cmd, new_filename);

        system(cmd);

        include_graph(new_filename);

        free(cmd);
        free(new_filename);
}

void
list_graph_dump(const list_t *list) // naming ???
{
        int i = 0;

        open_graph_dump();

        fprintf(DMP_STREAM,
        "digraph G {\n"
        "ranksep = 1.5\n"
        "graph [dpi = 100]\n"
        "splines = ortho\n"
        "{rank = min;\n"
        "above_node[label = \"Top inv\", width = 3, style = invis];\n"
        "free[label = \"FREE\", shape = rect, width = 3]}\n"
        "{rank = same;\n");

        for (i = 0; i <= list->cap; i++) {
                fprintf(DMP_STREAM,
                "       "
                "node%d [shape = record, "
                "label = \"idx\\n %d | {next \\n %d | prev\\n %d} | val\\n %d\"];\n",
                i, i, list->elem[i].next, list->elem[i].prev, list->elem[i].data);
        }

        fprintf(DMP_STREAM, "}\n");

        fprintf(DMP_STREAM,
        "{rank = max;\n"
        "	below_node[label = \"Bot inv\", width = 3, style = invis];\n"
        "}\n");

        fprintf(DMP_STREAM,
        "above_node -> node0 [style=invis];\n"
        "below_node -> node0 [style=invis];\n");

        for (i = 0; i < list->cap; i++) {
                fprintf(DMP_STREAM,
                "node%d -> ", i);
        }

        fprintf(DMP_STREAM,
        "node%d [weight = 5, style = invis];\n", i);

        for(i = 0; i <= list->cap; i++) {
                if (list->elem[i].prev >= 0) {
                        fprintf(DMP_STREAM,
                        "node%d -> node%d [weight = 0, color=red];\n",
                        i, list->elem[i].next);

                        fprintf(DMP_STREAM,
                        "node%d -> node%d [weight = 0, color=blue];\n",
                        i, list->elem[i].prev);
                }
        }

        if (list->elem[list->free].prev == -1)
                fprintf(DMP_STREAM, "free->node%d [weight = 0, color = purple]\n", list->free);

        fprintf(DMP_STREAM, "}\n");

        fclose(DMP_STREAM);

        generate_graph();
}

void
list_text_dump(const list_t *list, FILE *stream)
{
        fprintf(stream, "------------------DUMP---------------------------\n");
        fprintf(stream, "Free: %d\n", list->free);

        fprintf(stream, "Index: ");
        for (int i = 0; i <= list->cap; i++) {
                fprintf(stream, "%2d ", i);
        }
        fprintf(stream, "\n");

        fprintf(stream, "Data:  ");
        for (int i = 0; i <= list->cap; i++) {
                fprintf(stream, "%2d ", list->elem[i].data);
        }
        fprintf(stream, "\n");

        fprintf(stream, "Next:  ");
        for (int i = 0; i <= list->cap; i++) {
                fprintf(stream, "%2d ", list->elem[i].next);
        }
        fprintf(stream, "\n");

        fprintf(stream, "Prev:  ");
        for (int i = 0; i <= list->cap; i++) {
                fprintf(stream, "%2d ", list->elem[i].prev);
        }
        fprintf(stream, "\n");
        fprintf(stream, "---------------END OF DUMP-----------------------\n");
}

