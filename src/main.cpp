#include <stdio.h>
#include "list.h"

int
main()
{
        list_t list {};

        list_ctor(&list, 10);

        list_insert(&list, 2, 0);
        list_insert(&list, 3, 1);
        list_insert(&list, 4, 2);
        list_insert(&list, 4, 3);
        list_insert(&list, 4, 4);
        list_insert(&list, 4, 5);
        list_remove(&list, 3);
        list_insert(&list, 4, 5);
        list_insert(&list, 4, 6);
        list_insert(&list, 4, 7);
        list_insert(&list, 4, 8);

        list_dump(&list, stderr);

        list_dtor(&list);

        return 0;
}
