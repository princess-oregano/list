#include <stdio.h>
#include "list.h"
#include "dump.h"
#include "log.h"

const char *logfile = "log.htm";

int
main()
{
        open_log(logfile);

        list_t list {};

        list_ctor(&list, 10);

        list_insert(&list, 1, 0);
        list_insert(&list, 2, 1);
        list_insert(&list, 3, 2);
        list_insert(&list, 4, 3);
        list_insert(&list, 5, 4);
        list_insert(&list, 6, 5);
        list_remove(&list, 3);
        make_graph_dump(&list);
        list_insert(&list, 10, 6);
        list_insert(&list, 7, 6);
        list_insert(&list, 8, 7);
        list_insert(&list, 9, 8);

        make_graph_dump(&list);
        list_sort(&list);

        make_graph_dump(&list);

        list_dtor(&list);

        close_log();

        return 0;
}
