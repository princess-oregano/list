#include <stdio.h>
#include "list.h"
#include "dump.h"
#include "log.h"

const char *logfile = "log.html";

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
        list_verify(&list);
        list_graph_dump(&list);
        list_insert_back(&list, 10);
        list_insert_back(&list, 7);
        list_insert_back(&list, 8);
        list_insert_back(&list, 9);
        list_insert_back(&list, 11);
        list_insert_back(&list, 16);
        list_insert_back(&list, 18);
        list_insert_back(&list, 40);

        list_graph_dump(&list);
        list_sort(&list);
        list_text_dump(&list, stderr);

        list_graph_dump(&list);

        list_dtor(&list);

        close_log();

        return 0;
}
