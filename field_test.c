#include <assert.h>
#include "field.h"

int main(int argc, char** argv) {
    list_t *shapes = list_new(NULL);
    field_t field = {shapes, {100, 100}};

    /* test contains */ 

    point_t p1 = {50, 50};
    assert(field_contains(&field, p1)); 

    point_t p2 = {150, 150};
    assert(!field_contains(&field, p2)); 

    point_t p3 = {-1, -1};
    assert(!field_contains(&field, p3));
    
    /* test is_occupied */ 
    
    shape_t r1 = {{0, 0}, {10, 10}};
    list_add(field.shapes, &r1);

    shape_t r2 = {{20, 20}, {10, 10}};
    list_add(field.shapes, &r2);
    
    point_t p4 = {5, 5};
    assert(field_is_occupied(&field, p4));
    
    point_t p5 = {15, 15};
    assert(!field_is_occupied(&field, p5));
    
    return 0;
}