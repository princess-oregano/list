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

        list_dump(list);

        list_dtor(&list);

        return 0;
}
