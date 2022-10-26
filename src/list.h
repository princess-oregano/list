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
        int tail = 0;
        int free = 0;
};

// Construct list. 
void
list_ctor(list_t *list, int cap);
// Pushes element to list.
void
list_push(list_t *list, data_t data, int pos);
// Removes element out of list.
void
list_remove(list_t *list, int num);
// Removes next element out of list.
void
list_remove_next();
// Resizes list.
void
list_resize(list_t *list, int new_cap);
// Destroy list.
void
list_dtor(list_t *list);
// Checks condition of list.
void 
list_verify(list_t list);
// List dump.
void
list_dump(const list_t *list, FILE *stream);

#endif // LIST_H

