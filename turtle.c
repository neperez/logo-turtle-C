/* Nicolas Perez
   CSC 451 Fall 2012
   Term Project */

/* turtle.c:
   this source file contains the main driving logic for
   the opengl turtle graphics implementation */

#include "turtle.h"/* holds function prototypes */
#include "globals.c" /* holds include,directives, global variables */
#include "command.c"/* holds functions related to commands, program text I/O */
#include "movement.c"/* holds functions that move turtle cursor on screen */

/* drawLine():
   this function uses the line vertices array to specify a line strip */
void drawLine()
{
	/* if there is at least sets of coordinates in the line vertex array, */
	if (lineEndIndex > 2)
	{
		/* make a line strip object with the vertex coordinates
       in the lineVertices array */
    int index = 0;
    glBegin(GL_LINE_STRIP);
    while (index < lineEndIndex)
    {
      glVertex2f(lineVertices [index], lineVertices [index + 1]);
      index += 2; /* coordinates take up two spaces in array */
    }
    glEnd();
	}
}

/* myinit():
   initializes various values needed by the program */
void myinit(void)
{
	glClearColor(0.0,0.0,0.0,1.0); /* color: black */
	angleIndex = 0;

	/* initialize line vertex array */
	lineVertices[0] = 0.0;
	lineVertices[1] = 0.0;
	lineEndIndex = 2;
}

/* drawTurtle():
   this function draws the turtle in the correct pose based on information
   in the turtle struct array */
void drawTurtle(void)
{
	GLuint width, height;
  GLfloat aspect;
	width = glutGet(GLUT_WINDOW_WIDTH);
  height = glutGet(GLUT_WINDOW_HEIGHT);
  aspect = (GLfloat)width / (GLfloat)height;
	
	glViewport(0, 0, width, height);
	glOrtho(-aspect * SCALE, aspect * SCALE, -SCALE, SCALE, -1.0, 1.0);
	glPushMatrix();
	glTranslatef(turtle.position.x, turtle.position.y, 0.0);
  glRotatef(turtle.rotate, 0, 0, 1.0);
  glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, turtle_vertices);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glPopMatrix();
}

/* display():
   this function gets called by the glut loop. 
   All screen objects are drawn using their
   respective functions. */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	drawTurtle();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawLine();
	drawInputBox();
  drawText();	
	glFlush();
}

/* myReshape():
   ensures that objects on the screen are drawn
   the same when the window is resized */
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-50.0, 50.0, -50.0 * (GLfloat)h / (GLfloat)w,
    	50.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
	else
		glOrtho(-50.0 * (GLfloat)w / (GLfloat)h, 
    	50.0 * (GLfloat)w / (GLfloat)h, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* main():
   main function for this program. Initializes and 
   links glut functions. Also starts glut display loop */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 515);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Turtle Graphics: An Implementation in C");
	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(checkKey);
	glutMainLoop();
	
	return 0;
}
