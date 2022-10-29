#include <stdio.h>
#include "list.h"
#include "dump.h"

int
main()
{
        list_t list {};

        list_ctor(&list, 10);

        list_insert(&list, 1, 0);
        list_insert(&list, 2, 1);
        list_insert(&list, 3, 2);
        list_insert(&list, 4, 3);
        list_insert(&list, 5, 4);
        list_insert(&list, 6, 5);
        list_remove(&list, 3);
        list_insert(&list, 10, 6);
        list_insert(&list, 7, 6);
        list_insert(&list, 8, 7);
        list_insert(&list, 9, 8);

        for (int i = 1; i < list.cap; i++)
                printf("logical %d - physical %d\n", i, list_find(&list, i));

        make_graph_dump(&list);
        list_sort(&list);
        printf("\n\n\n");
        for (int i = 1; i < list.cap; i++)
                printf("logical %d - physical %d\n", i, list_find(&list, i));

        make_graph_dump(&list);

        list_dtor(&list);

        return 0;
}
