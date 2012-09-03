#include "cpathfinder.h"

struct Shape {
    int x;
    int y;
    int width;
    int height;
};

struct Shapes {
    struct Shapes *next;
    struct Shape *current;
};

