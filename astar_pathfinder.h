#include "cpathfinder.h"
#include "list.h"
#include "field.h"

#ifndef ASTART_PATHFINDER_H_
#define ASTART_PATHFINDER_H_

list_t *get_path(field_t field, point_t from, point_t to);

#endif