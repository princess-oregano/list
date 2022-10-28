#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef int data_t;

const char ELEM_POISON = 0x00;

struct elem_t {
        data_t data = 0;
        int next = 0;
        int prev = 0;
};

struct list_t {
        elem_t *elem = nullptr;
        int cap = 0;
        int free = 0;
};

// Resizes list.
void
list_resize(list_t *list, int new_cap);
// Construct list.
void
list_ctor(list_t *list, int cap);
// Inserts element to the list after position pos.
void
list_insert(list_t *list, data_t data, int pos);
// Removes element out of list.
void
list_remove(list_t *list, int num);
// Finds element in the list by logical position
// excluding the zero element.
int
list_find(list_t *list, int pos);
// Destroy list.
void
list_dtor(list_t *list);
// Checks condition of list.
bool
list_verify(list_t *list);

#endif // LIST_H

