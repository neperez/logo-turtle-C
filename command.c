/* Nicolas Perez
   CSC 451 Fall 2012
   Term Project */

/* command.c:
   this source file holds functions related to
   processing user commands */

/* validateCommand():
   will determine if the command entered is valid.
	 it will return the result boolean to the calling function */
int validateCommand(void)
{  
	int response = 0;
	
	/* guard atoi() against NULL value */
	if (args[1] != NULL)
	{
		if (compareCommand(args[0], "forward") == 0)
		{
			if (checkForAndBack(atoi(args[1])) == 1)
				response = FORWARD;
		}
		else if (compareCommand(args[0], "backward") == 0)
		{
			if (checkForAndBack(atoi(args[1])) == 1)
				response = BACKWARD;
		}
		else if (compareCommand(args[0], "turnright") == 0)
		{
			if (checkTurns(atoi(args[1])) == 1)
				response = TURN_RIGHT;
		}
		else if (compareCommand(args[0], "turnleft") == 0)
		{
			if (checkTurns(atoi(args[1])) == 1)
				response = TURN_LEFT;
		}
	}
	else if (compareCommand(args[0], "penup") == 0)
	{
		penState = 0;
		response = PEN_UP;
	}
	else if (compareCommand(args[0], "pendown") == 0)
	{
		penState = 1;
		response = PEN_DOWN;
	}
	
	/* if response isn't changed, assume no validation */
	return response;
}

/* checkForAndBack():
   checks if window boundaries are reached */
int checkForAndBack(int distance)
{
	if ( (distance < 0) || (distance > windowHeight) )
		return 0;
	return 1;
}

/* checkTurns():
   makes sure entered degrees conform to domain of circle */
int checkTurns(int degree)
{
	if ( (degree < 0) || (degree > 360) )
		return 0;
	return 1;
}

/* outputText():
	 output text takes a window position, and an array containing a string.
	 The string is displayed at the position specified */
void outputText(GLfloat x, GLfloat y, char *text)
{
	char *p; /* pointer for text */
	glPushAttrib(GL_CURRENT_BIT); /* change color to black temporarily for text */
  glColor3f(0.0,0.0,0.0);
	
	/* reset matrix to prior state */
	glPushMatrix();
	glScalef(TEXT_SCALE,TEXT_SCALE,1.0); 
	glTranslatef(x, y, 0);

	/* write message to input box at desired location */
	for (p = text; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);

	glPopMatrix();
	glPopAttrib();
	glutPostRedisplay();
}

/* checkKey():
   The keyboard callback function */
void checkKey(unsigned char key,int x, int y )
{
	int i; /* loop index */
	switch(key)
	{
		case 27:/* escape button pressed, end program */
			exit(0);
			break;

		case 13:/* enter button pressed */
			/* signal end of line */
			keyBuffer[keyIndex] = '\n';
			keyIndex = 0;
			/* validate, then call appropriate command */
			parseCommand(keyBuffer);
			callCommand(validateCommand());
			/* reset keyBuffer */
			for (i=0;i<MAX_LINE;i++)
				keyBuffer[i] = '\0';
			break;

		case 8:/* backspace button pressed */
			if (keyIndex > 0)
			{
				keyIndex--;
				keyBuffer[keyIndex] = '\0';
				glutPostRedisplay();
			}
			break;

		default:/* keys are pressed, add to buffer */
			keyBuffer[keyIndex] = key;
			keyIndex++;
			break;
	}
}

/* callCommand():
   calls appropriate command based on integer argument */
void callCommand(int response)
{
	int param;
	/* guard atoi() against NULL value */ 
	if (args[1]!=NULL)
		param = atoi(args[1]);
	else param=0;
	/* call appropriate function */
	switch(response)
	{
		case 1:
			forward(param);
			break;
		case 2:
			backward(param);
			break;
 	 	case 3:
			turnRight(param);
			break;
		case 4:
			turnLeft(param);
			break;
		case 5:
			penUp();
			break;
		case 6:
			penDown();
			break;
		default:
			keyIndex = 0;
	}
}

/* compareCommand():
   Checks to see if command strings are the same */
int compareCommand(char str1[], char str2[])
{
	return strncmp(str1, str2, compareLimit);
}

/* drawText():
	 this function populates the input box with the command
   prompt and echoed text */
void drawText(void)
{
	/* get length of keyBuffer string */
	int i,count,arrayLength;
	count = 0;
	for(i = 0; i < 80; i++)
	{
		if (keyBuffer[i] != '\0')
			count++;
	}
	/* merge prompt and keyboard buffer arrays into one array */
	arrayLength = PROMPT_LENGTH + count + 1;
	char mergeArray[arrayLength];

	/* copy both arrays element by element into new third array */
	for (i = 0; i < arrayLength; i++)
	{
		if ( (i >= 0) && (i < PROMPT_LENGTH) )
			mergeArray[i] = PROMPT[i];
		else
			mergeArray[i] = keyBuffer[i-PROMPT_LENGTH];
	}
	outputText(-1900,-1900.0, mergeArray);
}

/* drawInputBox():
   this function draws a white rectangle that serves as the background
   of our window's input section */
void drawInputBox(void)
{
	glBegin(GL_POLYGON);
		glVertex2f(-10,-9.0);/* upper left */
		glVertex2f(-10,-10.0);/* lower left */
		glVertex2f(10,-10.0);/* lower right */
		glVertex2f(10,-9.0);/* upper right */
	glEnd();
}

/* parseCommand():
   takes the keyboard buffer and separates the command
   from the argument and places them into an array */
void parseCommand(char inputBuffer[])
{
	int length,i,begin,ct;
	ct = 0;
	length = 0;
	
  /* find length of keyboard buffer */
	for (i = 0; i < MAX_LINE; i++)
	{
		if (inputBuffer[i] != '\0')
			length++;
	}

	/* initialize start of token index */
	begin = -1;

	/* loop through passed in keyboard buffer */
	for(i = 0; i < length; i++)
	{
		switch (inputBuffer[i])
		{
			/* current element is whitespace */
			case ' ':
			case '\t':
				if (begin != -1)
				{
					/* if whitespace encountered, set current args string index
						to be the start of the next token */
					args[ct] = &inputBuffer[begin];/* set up pointer */
					ct++;
				}
				/* change current whitespace to null terminator */
				inputBuffer[i] = '\0';
				/* reset start variable, signaling start of another token */
				begin = -1;
				break;
			
			case '\n': /* should be the final char examined when enter key is pressed */
				if (begin != -1)
				{
					args[ct] = &inputBuffer[begin];
					ct++;
				}
        inputBuffer[i] = '\0';
        args[ct] = NULL; /* no more arguments to this command */
				break;
		
			/* current element anything else */
			default : /* some other character */
				if (begin == -1)
		    	begin = i;
		}
	}
	args[ct] = NULL;/* in case arguments were > MAX_LINE */
}
