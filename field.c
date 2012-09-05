#include "globals.h"
#include "field.h"

int field_is_occupied(field_t *field, point_t point) {
    rectangle_t *element;
    int result = FALSE;
    LIST_FOREACH_START(field->shapes, element)
        if (point.x >= element->point.x && point.y >= element->point.y
                && point.x <= (element->point.x + element->dimension.width - 1) 
                && point.y <= (element->point.y + element->dimension.height - 1)) {
             /* I cannot exit from a FOREACH without LIST_FOREACH_END, so I cannot return TRUE here! */
             result = TRUE;
             break;
         }
    LIST_FOREACH_END(field->shapes)
    return result;
}

int field_contains(field_t *field, point_t point) {
    return (point.x >= 0 && point.y >= 0
                && point.x <= field->dimension.width 
                && point.y <= field->dimension.height);
}

int point_equals(point_t a, point_t b) {
    return a.x == b.x && a.y == b.y;
}
