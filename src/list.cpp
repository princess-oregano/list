#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void
list_dump(list_t list)
{
        printf("------------------DUMP---------------------------\n");
        printf("Tail: %d\n", list.tail);
        printf("Free: %d\n", list.free);

        printf("Index: ");
        for (int i = 0; i < list.tail; i++) {
                printf("%2d ", i);
        }
        printf("\n");

        printf("Elem:  ");
        for (int i = 0; i < list.tail; i++) {
                printf("%2d ", list.data[i].elem);
        }
        printf("\n");

        printf("Next:  ");
        for (int i = 0; i < list.tail; i++) {
                printf("%2d ", list.data[i].next);
        }
        printf("\n");

        printf("Prev:  ");
        for (int i = 0; i < list.tail; i++) {
                printf("%2d ", list.data[i].prev);
        }
        printf("\n");
        printf("---------------END OF DUMP-----------------------\n");
}

void
list_ctor(list_t *list, int cap)
{
        data_t *data_ptr = nullptr;
        if ((data_ptr = (data_t *) calloc((size_t) cap, 
                                   sizeof(data_t))) == nullptr)
                fprintf(stderr, "Couln't allocate memory.\n");

        for (int i = 0; i < cap; i++) {
                data_ptr[i].next = i + 1;
                data_ptr[i].prev = -1;
                memset(&data_ptr[i].elem, ELEM_POISON, sizeof(elem_t));
        }

        data_ptr[0].next = 0;
        data_ptr[0].prev = 0;

        list->data = data_ptr;

        list->tail = cap;
        list->free = 1;
}

void
list_push(list_t *list, elem_t elem, int pos)
{
        if (pos <= 0) {
                fprintf(stderr, "Invalid position.\n");
                return;
        }

        int index = list->free;
        list->free = list->data[list->free].next;

        list->data[index].elem = elem;

        list->data[index].prev = list->data[pos].prev;
        list->data[index].next = pos;

        list->data[pos].prev = index;

        if (pos == 1)
                return;
                
        list->data[list->data[index].prev].next = pos;
}

void
list_remove(list_t *list, int num)
{
        list->data[list->data[num].prev].next = list->data[num].next;
        list->data[list->data[num].next].prev = list->data[num].prev;

        list->data[num].next = -1;
        list->data[num].prev = -1;

        list->free = num;
}

void
list_resize(list_t *list, int new_cap)
{
        data_t *data_ptr = (data_t *) realloc(list->data, (size_t) new_cap);

        list->data = data_ptr;

        for (int i = list->tail; i < new_cap; i++) {
                data_ptr[i].next = i + 1;
        }

        list->tail = new_cap;
}

void
list_dtor(list_t *list)
{
        list->tail = -1;
        list->free = -1;
        if (list->data != nullptr)
                free(list->data);
}

