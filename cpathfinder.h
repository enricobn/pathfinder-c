#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef CPATHFINDER_H_
#define CPATHFINDER_H_

#define ERROR(...) fprintf(stderr, __VA_ARGS__)

#define STRUCT_NEW(STRUCT) (struct STRUCT *) malloc(sizeof(struct STRUCT))

//#define NEW(VAR) (__typeof__( VAR )) malloc(sizeof(__typeof__( VAR )));
#define NEW(TYPE) (TYPE) malloc(sizeof(TYPE));

#define DEF_LIST_NEW(LIST_STRUCT, ELEMENT_STRUCT) \
struct LIST_STRUCT *list_new_##LIST_STRUCT() {\
    struct LIST_STRUCT *list = STRUCT_NEW( LIST_STRUCT );\
    if (list == NULL){\
 	   ERROR("Error allocating " #LIST_STRUCT ".");\
    }\
    list->current = NULL;\
    list->next = NULL;\
    return list;\
}

#define LIST_NEW_PROTO(LIST_STRUCT) struct LIST_STRUCT *list_new_##LIST_STRUCT();

#define LIST_NEW(LIST_STRUCT) list_new_##LIST_STRUCT()

#define DEF_LIST_ADD(LIST_STRUCT, ELEMENT_STRUCT) \
struct LIST_STRUCT *list_add_##LIST_STRUCT(struct LIST_STRUCT *list, struct ELEMENT_STRUCT *element) {\
    if (list == NULL) {\
    	ERROR("Empty list.");\
    } else if ( list->current == NULL) {\
       list->current = element;\
       list->next = LIST_NEW( LIST_STRUCT );\
    } else {\
    	struct LIST_STRUCT *dummy = list->next;\
    	struct LIST_STRUCT *new = LIST_NEW( LIST_STRUCT );\
    	list->next = new;\
    	new->next = dummy;\
    	new->current = element;\
	}\
    return list->next;\
}

#define PROTO_LIST_ADD(LIST_STRUCT, ELEMENT_STRUCT) struct LIST_STRUCT *list_add_##LIST_STRUCT(struct LIST_STRUCT *list, struct ELEMENT_STRUCT *element);

#define LIST_ADD(LIST_STRUCT, LIST, ELEMENT) list_add_##LIST_STRUCT(LIST, ELEMENT)

#define LIST_FOREACH(ELEMENT, LIST) __typeof__(LIST->current) ELEMENT; for( ELEMENT = LIST->current; LIST->current != NULL; LIST = LIST->next) { ELEMENT = LIST->current;

#endif
