/*
 * move_example.c
 * This is a path finding example using ASearch
 *
 * 22-08-2013 13.070s
 */
#include <unistd.h>
#include <GL/glut.h>
#include "globals.h"
#include "list.h"
#include "field.h"
#include "astar_pathfinder.h"

#define WIDTH 100
#define HEIGHT 100

void rectangle_draw(shape_t rectangle) {
    glRectf((float)rectangle.point.x, (float)rectangle.point.y, (float)(rectangle.point.x + rectangle.dimension.width), 
        (float)(rectangle.point.y + rectangle.dimension.height));
}

typedef struct {
    shape_t *shape;
    point_t end;
} moving_shape_t;

field_t *field = NULL;

int moving_shapes_count = 50;

moving_shape_t *moving_shapes = NULL;

shape_t *rectangle_new(int x, int y, int width, int height, void (*draw)()) {
    shape_t *r = (shape_t *) malloc(sizeof(shape_t));
    r->point.x = x;
    r->point.y = y;
    r->dimension.width = width;
    r->dimension.height = height;
    r->draw = draw;
    return r;
}

void white_draw(shape_t rectangle) {
    glColor3f(1.0, 1.0, 1.0);
    rectangle_draw(rectangle);
}

void blue_draw(shape_t rectangle) {
    glColor3f(0.0, 0.0, 1.0);
    rectangle_draw(rectangle);
}

void red_draw(shape_t rectangle) {
    glColor3f(1.0, 0.0, 0.0);
    rectangle_draw(rectangle);
}

void green_draw(shape_t rectangle) {
    glColor3f(0.0, 1.0, 0.0);
    rectangle_draw(rectangle);
}

void field_init() {
    field = (field_t *) malloc(sizeof(field_t));

    field->shapes = list_new(NULL, NULL);
    field->dimension.width = WIDTH;
    field->dimension.height = HEIGHT;    

    list_add(field->shapes, rectangle_new(10, 10, 10, 10, white_draw));

    list_add(field->shapes, rectangle_new(40, 20, 20, 20, white_draw));
    
    list_add(field->shapes, rectangle_new(40, 60, 20, 20, white_draw));

    list_add(field->shapes, rectangle_new(75, 75, 10, 10, white_draw));
    
    moving_shapes = (moving_shape_t *) malloc(sizeof(moving_shape_t) * moving_shapes_count * 2);    
    
    int i;
    for (i = 0; i < moving_shapes_count; i++) {
        shape_t *p1 = rectangle_new(0, moving_shapes_count -i, 1, 1, red_draw);
        moving_shapes[2 * i].shape = p1;
        moving_shapes[2 * i].end.x = 90;
        moving_shapes[2 * i].end.y = 99 -i;
        list_add(field->shapes, p1);

        shape_t *p2 = rectangle_new(90, 99 -i, 1, 1, blue_draw);
        moving_shapes[2 * i +1].shape = p2;
        moving_shapes[2 * i + 1].end.x = 0;
        moving_shapes[2 * i + 1].end.y = moving_shapes_count -i;
        list_add(field->shapes, p2);
    }
}

void display(void)
{
/* clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    shape_t *r;
    LIST_FOREACH_START(field->shapes, r)
       glColor3f (1.0, 1.0, 1.0);
       r->draw(*r);
    LIST_FOREACH_END(field->shapes)

    {
        int i;
        for (i = 0; i < moving_shapes_count * 2; i++) {
            glColor3f(0.0, 1.0, 0.0);
            moving_shapes[i].shape->draw(*moving_shapes[i].shape);
        }
    }
    
/*    list_free(shapes, FALSE);*/
    
/* don't wait!  
 * start processing buffered OpenGL routines 
 */
   glFlush ();
/*   usleep(100);*/
   glutSwapBuffers();
}

void animate() {
    int i;
    for (i = 0; i < moving_shapes_count * 2; i++) {
        if (point_equals(moving_shapes[i].shape->point, moving_shapes[i].end)) {
            continue;
        }
        point_t *point = get_next_to_path(field, moving_shapes[i].shape->point, moving_shapes[i].end);
        if (point == NULL) {
/*            printf("empty path\n");*/
            continue;
/*            ERROR("No path found!\n");
            exit(1);
*/
        }
        
        moving_shapes[i].shape->point.x = point->x;
        moving_shapes[i].shape->point.y = point->y;
        free(point);
    }


/* 
    Normally openGL doesn't continuously draw frames. It puts one in place and waits for you to tell him what to do next.
     Calling glutPostRedisplay() forces a redraw with the new angle
 */
    glutPostRedisplay();
}

void init (void) 
{
/* select clearing color 	*/
    glClearColor (0.0, 0.0, 0.0, 0.0);

/* initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, HEIGHT, 0, 0, 1.0);
}

/* 
 * Declare initial window size, position, and display mode
 * (single buffer and RGBA).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int main(int argc, char** argv)
{
    field_init();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 800); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Path example");
    init ();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}

