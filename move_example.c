/*
 * path_example.c
 * This is a path finding example using ASearch
 */
#include <GL/glut.h>
#include "list.h"
#include "field.h"
#include "astar_pathfinder.h"

#define WIDTH 100
#define HEIGHT 100

void draw_rectangle(rectangle_t rectangle) {
    glRectf((float)rectangle.point.x, (float)rectangle.point.y, (float)(rectangle.point.x + rectangle.dimension.width), 
        (float)(rectangle.point.y + rectangle.dimension.height));
}

typedef struct {
    point_t start;
    point_t end;
} moving_shape_t;

field_t *field = NULL;

int moving_shapes_count = 50;

moving_shape_t *moving_shapes = NULL;

rectangle_t *rectangle_new(int x, int y, int width, int height) {
    rectangle_t *r = (rectangle_t *) malloc(sizeof(rectangle_t));
    r->point.x = x;
    r->point.y = y;
    r->dimension.width = width;
    r->dimension.height = height;
    return r;
}

void init_field() {
    field = (field_t *) malloc(sizeof(field_t));

    field->shapes = list_new(NULL);
    field->dimension.width = WIDTH;
    field->dimension.height = HEIGHT;    

    list_add(field->shapes, rectangle_new(10, 10, 10, 10));

    list_add(field->shapes, rectangle_new(40, 20, 20, 20));
    
    list_add(field->shapes, rectangle_new(40, 60, 20, 20));

    list_add(field->shapes, rectangle_new(80, 80, 10, 10));
    
    moving_shapes = (moving_shape_t *) malloc(sizeof(moving_shape_t) * moving_shapes_count);    
    
    int i;
    for (i = 0; i < moving_shapes_count; i++) {
        moving_shapes[i].start.x = 0;
        moving_shapes[i].start.y = moving_shapes_count -i;
         
        moving_shapes[i].end.x = 90;
        moving_shapes[i].end.y = 99 -i;
    }    
}

void display(void)
{
/* clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    rectangle_t *r;
    LIST_FOREACH_START(field->shapes, r)
       glColor3f (1.0, 1.0, 1.0);
       draw_rectangle(*r);
    LIST_FOREACH_END(field->shapes)

    {
        int i;
        for (i = 0; i < moving_shapes_count; i++) {
            list_t *path = get_path(field, moving_shapes[i].start, moving_shapes[i].end);
            if (path == NULL) {
                ERROR("No path found!\n");
                exit(1);
            }
            point_t *point;
            LIST_FOREACH_START(path, point)
               glColor3f (0.0, 1.0, 0.0);
        //       printf("%d %d %d %d\n", point->x, point->y, point->x + 1, point->y +1);
               rectangle_t r = {{point->x, point->y}, {1, 1}};
               draw_rectangle(r);
               //glRectf((float)point->x, (float)point->y, (float)point->x + 1, (float)point->y +1);
            LIST_FOREACH_END(path)
            list_free(path, FALSE);
        }
    }
    
/*    list_free(shapes, FALSE);*/
    
/* don't wait!  
 * start processing buffered OpenGL routines 
 */
   glFlush ();
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
    init_field();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 600); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Path example");
    init ();
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}

