#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "dump.h"
#include "log.h"

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

        elem_ptr[new_cap].next = 0;

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
        list->free = 1;
}

void
list_insert(list_t *list, data_t data, int pos)
{
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

int
list_find(const list_t *list, int pos)
{
        int index = 0;

        if (pos <= 0 || pos > list->cap) {
                fprintf(stderr, "Invalid position.\n");
                return -1;
        }
        for (int i = 0; i < pos; i++) {
                index = list->elem[index].next;
        }

        return index;
}

void
list_sort(list_t *list)
{
        data_t *sorted_data = (data_t *) calloc((size_t) list->cap,
                                                 sizeof(data_t));

        for (int i = 1; i < list->cap; i++) {
                sorted_data[i] = list->elem[list_find(list, i)].data;
        }

        for (int i = 1; i < list->cap; i++) {
                list->elem[i].data = sorted_data[i];
                list->elem[i].next = i + 1;
                if (list->elem[i].prev != -1)
                        list->elem[i].prev = i - 1;
        }

        list->elem[list->cap].next = 0;
        if (list->elem[list->cap].prev != -1)
                list->elem[list->cap].prev = list->cap - 1;

        list->free = list->cap;
        for (int i = 1; i <= list->cap; i++) {
                if (list->elem[i].prev == -1) {
                        list->free = i;
                        break;
                }
        }

        list->elem[0].next = 1;
        list->elem[0].prev = list->free - 1;
        list->elem[list->free - 1].next = 0;

        free(sorted_data);
}

void
list_remove(list_t *list, int pos)
{
        assert(list);

        list->elem[list->elem[pos].prev].next = list->elem[pos].next;
        list->elem[list->elem[pos].next].prev = list->elem[pos].prev;

        memset(&list->elem[pos].data, ELEM_POISON, sizeof(elem_t));
        list->elem[pos].next = list->free;
        list->elem[pos].prev = -1;

        list->free = pos;
}

void
list_dtor(list_t *list)
{
        list->cap = -1;
        list->free = -1;
        if (list->elem != nullptr)
                free(list->elem);
}

bool
list_verify(list_t *list)
{
        assert(list);

        bool ret_val = true;

        if (list->cap < 0) {
                fprintf(stderr, "Invalid capacity value.\n");
                ret_val = false;
        }

        if (list->free < 0) {
                fprintf(stderr, "Invalid free value.\n");
                ret_val = false;
        }
        if (list->elem == nullptr) {
                fprintf(stderr, "Pointer 'elem' is null.\n");
                ret_val = false;
        }

        return ret_val;
}
