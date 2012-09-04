#include "cpathfinder.h"
#include "list.h"
 
#ifndef FIELD_H_
#define FIELD_H_
 
typedef struct {
    list_t *shapes;
    dimension_t dimension;
} field_t;

int field_is_occupied(field_t *field, point_t point);

int field_contains(field_t *field, point_t point);

#endif