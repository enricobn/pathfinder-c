/*
 * path_example.c
 * This is a path finding example using ASearch
 */
#include <GL/glut.h>
#include "globals.h"
#include "list.h"
#include "field.h"
#include "astar_pathfinder.h"

#define WIDTH 100
#define HEIGHT 100

void draw_rectangle(shape_t rectangle) {
    glRectf((float)rectangle.point.x, (float)rectangle.point.y, (float)(rectangle.point.x + rectangle.dimension.width), 
        (float)(rectangle.point.y + rectangle.dimension.height));
}

void display(void)
{
/* clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    list_t *shapes = list_new(NULL, NULL);
    
    field_t field = {shapes, {WIDTH, HEIGHT}};
    

    shape_t r1 = {{10, 10}, {10, 10}};
    list_add(field.shapes, &r1);

    shape_t r2 = {{40, 20}, {20, 20}};
    list_add(field.shapes, &r2);
    
    shape_t r3 = {{40, 60}, {20, 20}};
    list_add(field.shapes, &r3);

    shape_t r4 = {{80, 80}, {10, 10}};
    list_add(field.shapes, &r4);

    point_t start_point = {0, 0};
    point_t end_point = {99, 99};
    
/*        
    shape_t r1 = {{4, 1}, {1, 3}};
    list_add(field.shapes, &r1);
    
    point_t start_point = {2, 2};
    point_t end_point = {6, 2};
*/    
    list_t *path = get_path(&field, start_point, end_point);

    if (path == NULL) {
        ERROR("No path found!\n");
        exit(1);
    }    

    shape_t *r;
    LIST_FOREACH_START(shapes, r)
       glColor3f (1.0, 1.0, 1.0);
       draw_rectangle(*r);
    LIST_FOREACH_END(shapes)
    
    point_t *point;
    LIST_FOREACH_START(path, point)
       glColor3f (0.0, 1.0, 0.0);
/*       printf("%d %d %d %d\n", point->x, point->y, point->x + 1, point->y +1);*/
       shape_t r = {{point->x, point->y}, {1, 1}};
       draw_rectangle(r);
       //glRectf((float)point->x, (float)point->y, (float)point->x + 1, (float)point->y +1);
    LIST_FOREACH_END(path)
    
    list_free(shapes, FALSE);
    
    list_free(path, FALSE);

/*
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (0.25, 0.25, 0.0);
      glVertex3f (0.75, 0.25, 0.0);
      glVertex3f (0.75, 0.75, 0.0);
      glVertex3f (0.25, 0.75, 0.0);
   glEnd();
*/

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

