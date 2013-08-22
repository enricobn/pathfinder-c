#include <stdlib.h>
#include "globals.h"
#include "list.h"

list_t *list_new(list_equals equals, list_hash hash) {
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
    new->hash = hash;
    new->JArray = (Pvoid_t) NULL;
    return new;
}

void list_add(list_t *list, void *element) {
    if (list->hash != NULL) {
		int PValue;
		J1S(PValue, list->JArray, list->hash(element));
    }
    struct cursor *new = (struct cursor *) malloc(sizeof(struct cursor));
    if (new == NULL) {
        ERROR("Cannot allocate new cursor.");
        exit(TRUE);
    }
    new->current = element;
    new->next = NULL;
    if (new == NULL) {
        ERROR("Cannot allocate new element.");
        exit(TRUE);
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
	int PValue = 0;
    if (list->hash != NULL) {
    	if (list->JArray == NULL) {
    		return FALSE;
    	}
		J1T(PValue, list->JArray, list->hash(element));
		return PValue;
    }

    int found = FALSE;
    struct cursor *cur = list->first;
    for (cur = list->first; cur != NULL && !found; cur = cur->next) {
        if (list->equals == NULL) {
            if (element == cur->current) {
                found = TRUE;
            }
        } else if (list->equals(element, cur->current)) {
            found = TRUE;
        }
    }
    return found;
}

void list_clear(list_t *list, int deep) {
    if (list->hash != NULL) {
    	Word_t  Rc_word;
		J1FA(Rc_word, list->JArray);
		list->JArray = (Pvoid_t) NULL;
    }
    struct cursor *cur = list->first;
    list->first = NULL;
    list->last = NULL;
    while (cur != NULL) {
        if (deep && cur->current != NULL) {
            free(cur->current);
        }
        struct cursor *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

void list_free(list_t *list, int deep) {
    list_clear(list, deep);
    free(list->actual_cursor);
    free(list);
}

int list_remove(list_t *list, const void *element) {
    if (list->hash != NULL) {
		int PValue;
		J1U(PValue, list->JArray, list->hash(element));
    }
    struct cursor *cur = list->first;
    struct cursor *prev = list->first;
    for (cur = list->first; cur != NULL; cur = cur->next) {
        if ((list->equals == NULL && element == cur->current) 
                || list->equals(element, cur->current)) {
            int is_last = (cur == list->last);
            if (cur == list->first) {
                struct cursor *tmp = list->first;
                list->first = list->first->next;
                free(tmp);
                tmp = NULL;
                if (is_last) {
                	list->last = list->first;
                }
           } else {
                struct cursor *tmp = cur;
                prev->next = cur->next;
                free(tmp);
                tmp = NULL;
                if (is_last) {
                	list->last = prev;
                }
            }
            return TRUE;
        }
        prev = cur;
    }
    return FALSE;
}

int list_size(list_t *list) {
    int count = 0;
    void *element;
    LIST_FOREACH_START(list, element)
        count++;
    LIST_FOREACH_END(list)
    return count;
}
