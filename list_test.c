#include <assert.h>
#include "globals.h"
#include "list.h"

int equals(const void *e1, const void *e2) {
    return *((int *)e1) == *((int *)e2);
}

int hash(const void *e) {
    return *((int *)e) * 1000;
}

int main(int argc, char** argv) {
    list_t *l = list_new(equals, hash);
    assert(l->first == NULL);
    assert(l->last == NULL);    
    
    int a = 10;
    list_add(l, &a);
    assert(list_size(l) == 1);
    assert(l->first->current == &a);
    assert(l->last->current == &a);

    int b = 20;
    list_add(l, &b);
    assert(list_size(l) == 2);
    assert(l->first->current == &a);
    assert(l->last->current == &b);

    int c = 30;
    list_add(l, &c);
    assert(list_size(l) == 3);
    assert(l->first->current == &a);
    assert(l->last->current == &c);
    
    struct cursor *cur = l->first;
    
	assert(*((int *)cur->current) == 10);

    cur = cur->next;
	assert(*((int *)cur->current) == 20);
	
    cur = cur->next;    
    assert(*((int *)cur->current) == 30);

    int count = 0;
    int *element;
    LIST_FOREACH_START(l, element)
        count++;
    LIST_FOREACH_END(l)

    assert(count == 3);

    int d = 40;

    assert(list_contains(l, &a));
    assert(list_contains(l, &b));
    assert(list_contains(l, &c));
    assert(!list_contains(l, &d));

    assert(list_contains(l, &a));

    assert(list_remove(l, &a));
    assert(!list_contains(l, &a));
    assert(list_size(l) == 2);
    assert(l->first->current == &b);
    assert(l->last->current == &c);

    assert(list_remove(l, &c));
    assert(!list_contains(l, &c));
    assert(list_size(l) == 1);
    assert(l->first->current == &b);
    assert(l->last->current == &b);

    assert(list_remove(l, &b));
    assert(!list_contains(l, &b));
    assert(list_size(l) == 0);
    assert(l->first == NULL);
    assert(l->last == NULL);

    list_clear(l, FALSE);
    
    assert(!list_contains(l, &a));

    return 0;
}

