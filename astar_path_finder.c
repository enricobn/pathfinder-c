#include <stdio.h>
#include "cpathfinder.h"

struct Node {
    struct Node *parent;
    int x;
    int y;
    int F;
    int G;
    int H;
};

struct Nodes {
    struct Nodes *next;
    struct Node *node;
};

struct Nodes *new_nodes() {
    struct Nodes *nodes = (struct Nodes *) malloc(sizeof(struct Nodes));
    if (nodes == NULL){
 	   ERROR("Error allocating shapes.");
    }
    nodes->node = NULL;
    nodes->next = NULL;
/*    moves->previous = NULL;*/
    return nodes;
}

void add_node(struct Nodes *nodes, struct Node *node) {
    if (nodes == NULL) {
    	ERROR("Empty nodes.");
    } else if (nodes->node == NULL) {
       nodes->node = node;
       nodes->next = new_nodes();
    } else {
    	struct Nodes *dummy = nodes->next;
    	struct Nodes *new = new_nodes();
    	nodes->next = new;
    	new->next = dummy;
    	new->node = node;
	}
}


