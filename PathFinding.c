
void loop(){
	readSensors();
  	//if only the middle two sensors can see the black line
	if(leftFarReading<200 && rightFarReading<200 && (leftCenterReading>200 || rightCenterReading>200)) 
	{ 
		straight();                                                                                    
	}
  	//otherwise goes to the leftHandWall method
	else
	{                                                                                              
		leftHandWall();                                                                                   
	}
}


void readSensors()	//accepts input from sensors
{
	leftCenterReading  = analogRead(leftCenterSensor);
	leftNearReading    = analogRead(leftNearSensor);
	leftFarReading     = analogRead(leftFarSensor);
	rightCenterReading = analogRead(rightCenterSensor);
	rightNearReading   = analogRead(rightNearSensor);
	rightFarReading    = analogRead(rightFarSensor); 
}

void leftHandWall(){
	if( leftFarReading<200 && rightFarReading<200)	//indicates either 3way intersection or end of maze
	{
		digitalWrite(leftMotor1, HIGH);
		digitalWrite(leftMotor2, LOW);
		digitalWrite(rightMotor1, HIGH);
		digitalWrite(rightMotor2, LOW);
		delay(leapTime);
		readSensors();

		if(leftFarReading<200 || rightFarReading<200)	//if it moves forward and still sees all black, maze is done
		{
	  		done();
		}
		if(leftFarReading>200 && rightFarReading>200)	//otherwise it turns left
		{ 
	  		turnLeft();
		}
	}
  
	if(leftFarReading<200)	//indicates that a left turn is possible
	{ 
		digitalWrite(leftMotor1, HIGH);
		digitalWrite(leftMotor2, LOW);
		digitalWrite(rightMotor1, HIGH);
		digitalWrite(rightMotor2, LOW);
		delay(leapTime);
		readSensors();
		if(leftFarReading>200 && rightFarReading>200)	//checks to make sure maze isn't done
		{
			turnLeft();
		}
		else
		{
			done();
		}
	}
   
	if(rightFarReading<200)	//indicates a right turn is possible
	{
		digitalWrite(leftMotor1, HIGH);
		digitalWrite(leftMotor2, LOW);
		digitalWrite(rightMotor1, HIGH);
		digitalWrite(rightMotor2, LOW);
		delay(10);	//CHANGED FROM 30 to 10
		readSensors();

		if(leftFarReading<200)	//left turn is also possible
		{
			delay(leapTime-30);
			readSensors();

			if(rightFarReading<200 && leftFarReading<200)//end of maze
			{
				done();
			}
			else	//make the left turn
			{
			turnLeft();
			return;
			}
		}
		delay(leapTime-30);
		readSensors();
		if(leftFarReading>200 && leftCenterReading>200 && rightCenterReading>200 && rightFarReading>200)
		{
			turnRight();
			return;
		}
		path[pathLength] = 'S';
		pathLength++;
		if(path[pathLength-2] == 'B')
		{
			shortPath();
		}
		straight();
	}
	readSensors();
	if(leftFarReading>200 && leftCenterReading>200 && rightCenterReading>200 
  	&& rightFarReading>200 && leftNearReading>200 && rightNearReading>200)
	{
		turnAround();
	}
}

void shortPath()
{
	int shortDone = 0;
	if(path[pathLength-3] == 'L' && path[pathLength - 1] == 'R')
	{
		pathLength -= 3;
		path[pathLength] = 'B';
		shortDone = 1;
	}
	if(path[pathLength-3] == 'L' && path[pathLength - 1] == 'S' && shortDone == 0)
	{
		pathLength -= 3;
		path[pathLength] = 'R';
		shortDone = 1;
	}
	if(path[pathLength-3] == 'R' && path[pathLength - 1] == 'L' && shortDone == 0)
	{
		pathLength-=3;
		path[pathLength] = 'B';
		shortDone=1;
	}
	if(path[pathLength-3] == 'S' && path[pathLength - 1] == 'L' && shortDone == 0)
	{
		pathLength -= 3;
		path[pathLength] = 'R';
		shortDone = 1;
	}
	if(path[pathLength-3] == 'S' && path[pathLength - 1] =='S' && shortDone == 0)
	{
		pathLength-=3;
		path[pathLength] = 'B';
		shortDone=1;
	}
	if(path[pathLength-3] == 'L' && path[pathLength - 1] =='L' && shortDone == 0)
	{
		pathLength -= 3;
		path[pathLength] = 'S';
		shortDone = 1;
	}
	path[pathLength+1] = 'D';
	path[pathLength+2] = 'D';
	pathLength++;
}
