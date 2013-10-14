/* Nicolas Perez
   CSC 451 Fall 2012
   Term Project */

/* movement.c:
   this source file holds functions related to 
   the movement of the turtle cursor */

/* saveCoordinates():
   This function saves the current x and y position in the
   turtle struct to the line vertex array */
void saveCoordinates(void)
{
	lineVertices[lineEndIndex] = turtle.position.x;
	lineVertices[lineEndIndex+1] = turtle.position.y;
	lineEndIndex += 2;
}

/* forward(): mathematical vertex coordinate transformation
   if the distance passed in was smaller than the window area,
   this function calculates the position of the turtle cursor
   if moved forward along the current angle */
int forward(int distance)
{
	/* only move turtle if within bounds of work area */
	if ( (turtle.position.x > -windowWidth) && (turtle.position.x < windowWidth) )
	{
		if ( (turtle.position.y > -windowWidth) && (turtle.position.y < windowWidth) )
		{
			turtle.position.x += sin(DEGREES_TO_RADIANS * angleIndex) * (DISTANCE_FACTOR * distance);
			turtle.position.y += cos(DEGREES_TO_RADIANS * angleIndex) * (DISTANCE_FACTOR * distance);
			
			/* if the pen is down and turtle is within bounds of work area,
         save the current position for addition to line vertex array */
			if (penState == 1)
			{
				saveCoordinates();
			}
			
			/* redraw screen to reflect the change in position */
			glutPostRedisplay();
			
			return 0;
		}
	}
	return 1;
}

/* backward(): mathematical vertex transformation
   if the distance passed in was smaller than the window area,
   this function calculates the position of the turtle cursor
   if moved backward along the current angle */
int backward(int distance)
{
	if ( (turtle.position.x > -windowWidth) && (turtle.position.x < windowWidth) )
	{
		if ( (turtle.position.y > -windowWidth) && (turtle.position.y < windowWidth) )
		{
			turtle.position.x -= sin(DEGREES_TO_RADIANS * angleIndex) * (DISTANCE_FACTOR * distance);
			turtle.position.y -= cos(DEGREES_TO_RADIANS * angleIndex) * (DISTANCE_FACTOR * distance);
						
			if (penState == 1)
			{
				saveCoordinates();
			}

			glutPostRedisplay();

			return 0;
		}
	}
	return 1;
}

/* turnRight():
   this function sets the rotation value in the
   right turning direction in the turtle struct */
int turnRight(int degree)
{
	/* save the true angle in case user wants to move forward or backward */
	angleIndex = (angleIndex + degree) % 360;

	/* set rotation amount of the triangle for the next screen draw */
	turtle.rotate -= degree;
	
	if (penState == 1)
		saveCoordinates();

	glutPostRedisplay();

	return 0;
}

/* turnLeft():
   this function sets the rotation value
   in the left turning direction in the turtle struct */
int turnLeft(int degree)
{
	angleIndex = (angleIndex - degree) % 360;

	turtle.rotate += degree;

	if (penState == 1)
		saveCoordinates();

	glutPostRedisplay();

	return 0;
}

/* penUp():
   this function sets the pen state to up,
   no line will be drawn behind the turtle cursor */
int penUp(void)
{
	penState = 0;

	return 0;
}

/* penDown():
   this function sets the pen state to down,
   a line will be drawn trailing the turtle cursor */
int penDown(void)
{
	penState = 1;

	return 0;
}
