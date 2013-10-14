/* Nicolas Perez
   CSC 451 Fall 2012
   Term Project */

/* globals.c:
	 this source file contains all pre-processor directives,
   symbol definitions, and global variables */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE 80
#define PROMPT "Enter Command->: "
#define PROMPT_LENGTH 17
#define SCALE 10.0
#define DISTANCE_FACTOR 0.02
#define DEGREES_TO_RADIANS 3.14159/180.0
#define TEXT_SCALE 0.00509

/* command response flags */
#define FORWARD 1
#define BACKWARD 2
#define TURN_RIGHT 3
#define TURN_LEFT 4
#define PEN_UP 5
#define PEN_DOWN 6

/* window attributes */
GLfloat windowHeight = 515.0;
GLfloat windowWidth = 500.0;

char penState = 1;/* 0=Pen up, 1=Pen down(default) */

/* user entry is stored in keyBuffer array */
char keyBuffer[MAX_LINE] = {'\0'};

/* command tokens are stored in args array */
char *args[MAX_LINE];

/* counter keeps track of keyboard buffer position */
int keyIndex = 0;

/* number of characters to compare*/
int compareLimit = 10;

/* keeps record of true angle for trig functions */
int angleIndex;

/* array that holds vertices that make up drawn turtle lines */
GLfloat lineVertices[200];

/* current position to insert into line vertex array */
int lineEndIndex;

/* pre-transformation turtle vertex coordinates */
GLfloat turtle_vertices[] = {
    -0.5, 0.0,
     0.5, 0.0,
     0.0, 1.0
};

/* nested structure to hold pose information for turtle cursor */
  struct {
      struct {
          GLfloat x, y;
      } position;
      GLfloat rotate;
  } turtle;
