#include "list.h"
 
#ifndef FIELD_H_
#define FIELD_H_

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    int width;
    int height;
} dimension_t;

/*typedef void (*rectangle_draw_f) (rectangle_t rectangle);*/

typedef struct {
    point_t point;
    dimension_t dimension;
    void (*draw)();
} rectangle_t;

typedef struct {
    list_t *shapes;
    dimension_t dimension;
} field_t;

int field_is_occupied(field_t *field, point_t point);

int field_contains(field_t *field, point_t point);

int point_equals(point_t a, point_t b);

#endif