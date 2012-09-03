#include "view.h"

DEF_LIST_NEW(Shapes, Shape)

DEF_LIST_ADD(Shapes, Shape)

int main(int argc, char** argv)
{
    struct Shapes *shapes = LIST_NEW(Shapes);
    struct Shapes *top = shapes;

    struct Shape *shape = STRUCT_NEW(Shape);
    shape->x = 0;
    shape->y = 0;
    shape->width = 100;
    shape->height = 100;

    shapes = LIST_ADD(Shapes, shapes, shape);

    struct Shape s1 = {.x = 100, .y = 100, .width = 200, .height = 200};

    shapes = LIST_ADD(Shapes, shapes, &s1);

    struct Shape s2 = {.x = 200, .y = 200, .width = 200, .height = 200};

    LIST_ADD(Shapes, shapes, &s2);

    /* back to the top of the list */
    shapes = top;

    LIST_FOREACH(me, shapes) 
        printf("x=%d, y=%d, width=%d, height=%d\n", me->x, me->y, me->width, me->height);
    }

    /* back to the top of the list */
    shapes = top;

    LIST_FOREACH(me1, shapes) 
        printf("x=%d, y=%d, width=%d, height=%d\n", me1->x, me1->y, me1->width, me1->height);
    }

    return 0;
}
