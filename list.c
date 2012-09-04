#include <stdlib.h>
#include "list.h"

#define ERROR(...) fprintf(stderr, __VA_ARGS__)
typedef enum {FALSE, TRUE} boolean;

list_t *list_new(list_equals equals) {
    list_t *new = (list_t *) malloc(sizeof(list_t));
    if (new == NULL) 
    {
        ERROR("Error allocating list.");
    }
    new->actual_cursor = (struct cursor **)malloc(10 * sizeof(struct cursor *));
    if (new->actual_cursor == NULL) 
    {
        ERROR("Error allocating array for foreach.");
    }
    new->actual_cursor_number = -1;
    new->first = NULL;
    new->last = NULL;
    new->equals = equals;
    return new;
}

void list_add(list_t *list, const void *element) {
    struct cursor *new = (struct cursor *) malloc(sizeof(struct cursor));
    new->current = element;
    new->next = NULL;
    if (new == NULL) {
        ERROR("Error allocating new element.");
    }
    if (list->first == NULL) {
        list->first = new;
        list->last = new;
    } else {
       list->last->next = new;
       list->last = new; 
    }
}

int list_contains(list_t *list, const void *element) {
    struct cursor *cur = list->first;
    for (cur = list->first; cur != NULL; cur = cur->next) {
        if (list->equals == NULL) {
            if (element == cur->current) {
                return TRUE;
            }
        } else if (list->equals(element, cur->current)) {
            return TRUE;
        }
    }
    return FALSE;
}

void list_clear(list_t *list) {
    struct cursor *cur = list->first;
    list->first = NULL;
    list->last = NULL;
    while (cur != NULL) {
/*        if (cur->current != NULL) {
            free(cur->current);
        }
        */
        struct cursor *tmp = cur;
        cur = cur->next;
        free(tmp); 
    }
}
