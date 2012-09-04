#include <assert.h>
#include "list.h"

int equals(const void *e1, const void *e2) {
    return *((int *)e1) == *((int *)e2);
}

int main(int argc, char** argv) {
    list_t *l = list_new(equals);
    int a = 10;
    list_add(l, &a);

    int b = 20;
    list_add(l, &b);

    int c = 30;
    list_add(l, &c);
    
    struct cursor *cur = l->first;
    
	assert(*((int *)cur->current) == 10);

    cur = cur->next;
	assert(*((int *)cur->current) == 20);
	
    cur = cur->next;    
    assert(*((int *)cur->current) == 30);

    int *element;
    LIST_FOREACH_START(l, element)
        printf("%d\n", *element);
    LIST_FOREACH_END(l)

    int d = 40;

    assert(list_contains(l, &a));
    assert(list_contains(l, &b));
    assert(list_contains(l, &c));
    assert(!list_contains(l, &d));

    assert(list_remove(l, &b));
    
    assert(!list_contains(l, &b));

    assert(list_remove(l, &a));
    
    assert(!list_contains(l, &a));


    list_clear(l);
    
    assert(!list_contains(l, &a));

    return 0;
}

