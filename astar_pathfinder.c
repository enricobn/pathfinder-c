#include <stdlib.h>
#include <stdio.h>
#include "globals.h"
#include "cpathfinder.h"
#include "astar_pathfinder.h"
#include "list.h"
#include "field.h"

struct path_node_t {
    struct path_node_t *parent;
    point_t point;
    int F;
    int G;
    int H;
};

struct path_node_t *new_path_node(struct path_node_t *parent, point_t point, int F, int G, int H) {
    struct path_node_t *result = NEW_STRUCT_POINTER(path_node_t);
    result->parent = parent;
    result->point = point;
    result->F = F;
    result->G = G;
    result->H = H;
    return result;
}

list_t *get_path(field_t field, point_t from, point_t to) {
    list_t *open = list_new(NULL);
    list_t *closed = list_new(NULL);
    
    struct path_node_t *from_node = new_path_node(NULL, from, 0, 0, 0); 
    
    list_t *result = list_new(NULL);
    
    list_clear(open);
    list_clear(closed);    
    
    return result;
}

int path_node_H(struct path_node_t *node, point_t to) {
    return (abs(to.x - node->point.x) + abs(to.y - node->point.y)) * 10;
}

int path_node_F(struct path_node_t *node) {
    return node->H + node->G;
}

int path_node_G_vs(struct path_node_t *node, struct path_node_t *vs) {
    if (vs == NULL) {
        return 0;
    }
    int g = node->G;
    if (node->point.x == vs->point.x || node->point.y == vs->point.y) {
        g += 10;
    } else {
        g += 14;
    }
    return g;
}

int path_node_G(struct path_node_t *node) {
    return path_node_G_vs(node, node->parent); 
}
