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

point_t *get_adjacents(point_t point) {
    point_t adjacents[] = {
        {point.x +1, point.y}, 
        {point.x +1, point.y + 1},
        {point.x , point.y + 1},
        {point.x -1, point.y +1},
        {point.x -1, point.y},
        {point.x -1, point.y -1},
        {point.x , point.y -1},
        {point.x +1, point.y -1}};
    return adjacents;
}

int point_equals(point_t a, point_t b) {
    return a.x == b.x && a.y == b.y;
}

list_t *get_path(field_t *field, point_t from, point_t to) {
    list_t *open = list_new(NULL);
    list_t *closed = list_new(NULL);
    
    struct path_node_t *from_node = new_path_node(NULL, from, 0, 0, 0); 
    list_add(open, from_node);

    struct path_node_t *target_node = NULL;
    
    while (TRUE) {
        if (open->first == NULL) {
            return NULL;
        }
        int min = INT_MAX_VALUE;
        struct path_node_t *min_node = NULL;
        
        {
            struct path_node_t *node;
            LIST_FOREACH_START(open, node)
                if (min_node == NULL || node->F < min) {
                    min = node->F;
                    min_node = node;
                }
            LIST_FOREACH_END(open);
        }
        
        if (point_equals(min_node->point, to)) {
            target_node = min_node;
            break;
        }

        point_t *adjacents = get_adjacents(min_node->point);

        for (int i = 0; i < 8; i++) {
            point_t point = adjacents[i];
            // I do not consider the end point to be occupied, so I can move towards it
            if (field_contains(field, point) && (point_equals(point, to) || !field_is_occupied(field, point))) {
                struct path_node_t *node = new_path_node(min_node, point, 0, 0, 0);
                node->H = path_node_H(node);
                node->G = path_node_G(node);
                node->F = path_node_F(node);
                if (!list_contains(closed, node)) {
                    if (!list_contains(open, node)) {
                        list_add(open, node);
                    } else {
/*                        int gToMin = minNode.G(node);
                        if (gToMin < node.G()) {
                            node.setParent(minNode);
                        }
*/
                    }
                }
            }
        }
        list_remove(open, min_node);
        list_add(closed, min_node);
            
    }
    
    list_t *result = list_new(NULL);
    
    while (target_node->parent != NULL) {
        /* the path can contains occupied points. Normally it can be only the end point */ 
        if (!field_is_occupied(field, target_node->point)) {
            list_add(result, &target_node->point);
        }
        target_node = target_node->parent;
    }
    
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
