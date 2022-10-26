#include <stdio.h>
#include "list.h"

int
main()
{
        list_t list {};

        list_ctor(&list, 10);

        list_push(&list, 2, 1);
        list_push(&list, 3, 2);
        list_push(&list, 4, 3);
        list_push(&list, 4, 4);
        list_push(&list, 4, 5);
        list_push(&list, 4, 6);
        list_remove(&list, 3);
        list_push(&list, 4, 7);
        list_push(&list, 4, 8);
        list_push(&list, 4, 9);
        list_push(&list, 4, 10);

        list_dump(&list, stderr);

        list_dtor(&list);

        return 0;
}
