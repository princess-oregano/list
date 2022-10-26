#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void
list_dump(const list_t *list, FILE *stream)
{
        fprintf(stream, "------------------DUMP---------------------------\n");
        fprintf(stream, "Tail: %d\n", list->tail);
        fprintf(stream, "Free: %d\n", list->free);

        fprintf(stream, "Index: ");
        for (int i = 0; i < list->cap; i++) {
                fprintf(stream, "%2d ", i);
        }
        fprintf(stream, "\n");

        fprintf(stream, "Elem:  ");
        for (int i = 0; i < list->cap; i++) {
                fprintf(stream, "%2d ", list->elem[i].data);
        }
        fprintf(stream, "\n");

        fprintf(stream, "Next:  ");
        for (int i = 0; i < list->cap; i++) {
                fprintf(stream, "%2d ", list->elem[i].next);
        }
        fprintf(stream, "\n");

        fprintf(stream, "Prev:  ");
        for (int i = 0; i < list->cap; i++) {
                fprintf(stream, "%2d ", list->elem[i].prev);
        }
        fprintf(stream, "\n");
        fprintf(stream, "---------------END OF DUMP-----------------------\n");
}

void
list_resize(list_t *list, int new_cap)
{
        elem_t *elem_ptr = (elem_t *) realloc(list->elem,
                           ((size_t) new_cap + 1) * sizeof(elem_t));

        if (elem_ptr == nullptr) {
                fprintf(stderr, "Couldn't allocate memory for list.elem.\n");
                return;
        }

        for (int i = list->cap; i < new_cap + 1; i++) {
                elem_ptr[i].next = i + 1;
                elem_ptr[i].prev = -1;
                memset(&elem_ptr[i].data, ELEM_POISON, sizeof(data_t));
        }

        list->elem = elem_ptr;

        list->cap = new_cap + 1;
}

void
list_ctor(list_t *list, int cap)
{
        list_resize(list, cap);

        list->elem[0].prev = 0;
        list->elem[0].next = 0;

        list->cap = cap;
        list->tail = 0;
        list->free = 1;
}

void
list_insert(list_t *list, data_t data, int pos)
{
        list_dump(list, stderr);

        if (pos < 0 || pos > list->cap) {
                fprintf(stderr, "Invalid position.\n");
                return;
        }

        int index = list->free;
        list->free = list->elem[list->free].next;

        list->elem[index].data = data;

        list->elem[index].prev = pos;
        list->elem[index].next = list->elem[pos].next;

        list->elem[pos].next = index;
        list->elem[list->elem[index].next].prev = index;
}

void
list_remove(list_t *list, int pos)
{
        list->elem[list->elem[pos].prev].next = list->elem[pos].next;
        list->elem[list->elem[pos].next].prev = list->elem[pos].prev;

        memset(&list->elem[pos].data, ELEM_POISON, sizeof(elem_t));
        list->elem[pos].next = list->free;
        list->elem[pos].prev = -1;

        list->free = pos;

        list_dump(list, stderr);
}

void
list_dtor(list_t *list)
{
        list->cap = -1;
        list->tail = -1;
        list->free = -1;
        if (list->elem != nullptr)
                free(list->elem);
}

