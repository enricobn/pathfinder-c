#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "globals.h"

#ifndef CPATHFINDER_H_
#define CPATHFINDER_H_

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    int width;
    int height;
} dimension_t;


typedef struct {
    point_t point;
    dimension_t dimension;
} rectangle_t;

#endif
