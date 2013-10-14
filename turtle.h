/* Nicolas Perez
   CSC 451 Fall 2012
   Term Project */

/* turtle.h:
	 this header file holds the function prototypes */

#include <GL/glut.h> /* to specify GL datatypes in command functions */

/* movement functions */
int forward(int distance);
int backward(int distance);
int turnRight(int degree);
int turnLeft(int degree);
int penUp(void);
int penDown(void);
void redisplay(void);
void saveCoordinates(void);

/* main opengl functions */
void drawTurtle(void);
void myinit(void);
void display(void);
void myReshape(int w, int h);
void drawLine(void);

/* command functions */
void outputText(GLfloat x, GLfloat y, char *text);
void drawText(void);
int validateCommand(void);
int checkForAndBack(int distance);
int checkTurns(int degree);
void checkKey(unsigned char key, int x, int y);
void parseCommand(char inputBuffer[]);
void callCommand(int response);
int compareCommand(char str1[], char str2[]);
void postRedisplay(void);
void drawInputBox(void);
