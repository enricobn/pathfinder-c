#include "field.h"

int field_is_occupied(field_t *field, point_t point) {
    rectangle_t *element;
    LIST_FOREACH_START(field->shapes, element)
        if (point.x >= element->point.x && point.y >= element->point.y
                && point.x <= (element->point.x + element->dimension.width) 
                && point.y <= (element->point.y + element->dimension.height)) {
             return TRUE;
         }
    LIST_FOREACH_END(field->shapes)
    return FALSE;
}

int field_contains(field_t *field, point_t point) {
    return (point.x >= 0 && point.y >= 0
                && point.x <= (field->dimension.width) 
                && point.y <= (field->dimension.height));
}