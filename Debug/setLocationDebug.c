void rotate(bool left, float time, int encoder)
{
	float halfTime = time / 2;
	int power = 5;
	
	if(left)
		power = 5;
		
	else
		power = -5;
	
	if(time < 0) // User setting location manually
	{
		motor[motorB] = power; // Need to check if this rotates left or right
		wait1MSec(100);
	}
	
	else	// Randomized
	{
		randomTime = halfTime * (3 / 4);	// Select random time between 0 and halfTime
		time1[T1] = 0;					// Reset timer
		motor[motorB] = power;			// Begin moving shooting mechanism
		
		while(fabs(nMotorEncoder[motorB]) < fabs(encoder) && time1[T1] < randomTime)
		{
		}
	}
	
	motor[motorB] = 0;
}

void setLocation(float time, bool left, int encoder)
{	
	rotate(turn, time, encCount);
}

task main()
{
	setLocation(2, true, 20);
	setLocation(3, false, -40);
	setLocation(1, true, 12);
	setLocation(2.5, false, -5);
	setLocation(1.5, true, 32);
}

