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
        list_insert_back(&list, 2);
        list_insert_back(&list, 3);
        list_insert_back(&list, 4);
        list_insert_back(&list, 5);
        list_insert_back(&list, 6);
        list_remove(&list, 3);
        make_graph_dump(&list);
        list_insert_back(&list, 10);
        list_insert_back(&list, 7);
        list_insert_back(&list, 8);
        list_insert_back(&list, 9);

        make_graph_dump(&list);
        list_sort(&list);

        make_graph_dump(&list);

        list_dtor(&list);

        close_log();

        return 0;
}
