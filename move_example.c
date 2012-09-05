/*
 * move_example.c
 * This is a path finding example using ASearch
 */
#include <unistd.h>
#include <GL/glut.h>
#include "globals.h"
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

void field_init() {
    field = (field_t *) malloc(sizeof(field_t));

    field->shapes = list_new(NULL);
    field->dimension.width = WIDTH;
    field->dimension.height = HEIGHT;    

    list_add(field->shapes, rectangle_new(10, 10, 10, 10));

    list_add(field->shapes, rectangle_new(40, 20, 20, 20));
    
    list_add(field->shapes, rectangle_new(40, 60, 20, 20));

    list_add(field->shapes, rectangle_new(75, 75, 10, 10));
    
    moving_shapes = (moving_shape_t *) malloc(sizeof(moving_shape_t) * moving_shapes_count * 2);    
    
    int i;
    for (i = 0; i < moving_shapes_count; i++) {
        moving_shapes[2 * i].start.x = 0;
        moving_shapes[2 * i].start.y = moving_shapes_count -i;
         
        moving_shapes[2 * i].end.x = 90;
        moving_shapes[2 * i].end.y = 99 -i;

        moving_shapes[2 * i + 1].end.x = 0;
        moving_shapes[2 * i + 1].end.y = moving_shapes_count -i;
         
        moving_shapes[2 * i + 1].start.x = 90;
        moving_shapes[2 * i + 1].start.y = 99 -i;
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
        for (i = 0; i < moving_shapes_count * 2; i++) {
            glColor3f(0.0, 1.0, 0.0);
            rectangle_t r = {{moving_shapes[i].start.x, moving_shapes[i].start.y}, {1, 1}};
            draw_rectangle(r);
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
        if (point_equals(moving_shapes[i].start, moving_shapes[i].end)) {
            continue;
        }
        list_t *path = get_path(field, moving_shapes[i].start, moving_shapes[i].end);
        if (path == NULL) {
            printf("empty path\n");
            continue;
/*            ERROR("No path found!\n");
            exit(1);
*/
        }
        
        point_t point = *((point_t *)path->last->current);
        
        moving_shapes[i].start.x = point.x;
        moving_shapes[i].start.y = point.y;
                
        list_free(path, TRUE);
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
    glutInitWindowSize (800, 600); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Path example");
    init ();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}

