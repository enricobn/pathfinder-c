#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <Judy.h>

#ifndef LIST_H_
#define LIST_H_

struct cursor {
    void *current;
    struct cursor *next;
};

typedef int (*list_equals) (const void *e1, const void *e2);

typedef int (*list_hash) (const void *e);

typedef struct {
    struct cursor *first;
    struct cursor *last;
    struct cursor **actual_cursor;
    int actual_cursor_number;
    list_equals equals;
    list_hash hash;
    Pvoid_t JArray;
} list_t;


list_t *list_new(const list_equals equals, const list_hash hash);

void list_add(list_t *list, void *element);

int list_contains(list_t *list, const void *element);

void list_clear(list_t *list, int deep);

int list_remove(list_t *list, const void *element);

int list_size(list_t *list);

void list_free(list_t *list, int deep);

#define LIST_FOREACH_START(LIST, ELEMENT) \
    LIST->actual_cursor_number++;\
/*    printf("List %s -> actual cursor number %d, file=%s, line=%d, \n", #LIST, LIST->actual_cursor_number, __FILE__, __LINE__);*/\
    for (LIST->actual_cursor[LIST->actual_cursor_number] = LIST->first; \
                LIST->actual_cursor[ LIST->actual_cursor_number] != NULL; \
                LIST->actual_cursor[ LIST->actual_cursor_number] = LIST->actual_cursor[ LIST->actual_cursor_number]->next) {\
        ELEMENT = (__typeof__(ELEMENT)) LIST->actual_cursor[ LIST->actual_cursor_number]->current;

#define LIST_FOREACH_END(LIST) \
    }\
    LIST->actual_cursor[ LIST->actual_cursor_number--] = NULL; 

#endif
