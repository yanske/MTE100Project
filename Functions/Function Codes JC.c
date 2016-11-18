// Rotate Function
void rotate(bool left, float time, int encoder)
{
	float halfTime = time / 2, randomTime = 0;
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
		randomTime = random[halfTime];	// Select random time between 0 and halfTime
		time[T1] = 0;					// Reset timer
		motor[motorB] = power;			// Begin moving shooting mechanism
		
		while(fabs(nMotorEncoder[motorB]) < fabs(encoder) && time[T1] < randomTime)
		{
		}
	}
	
	motor[motorB] = 0;
}

//Touch Sensor Timer Function
float touchTimer()
{
	displayString(0, "Hold Touch Sensor for duration");
	displayString(1, "of desired shot interval");
	
	float recordedTime = 0;
	
	while(Sensor[S1] == 0) // Need to check sensor port
	{
	}
	
	time[T1] = 0;
	
	while(Sensor[S1] == 1) 
	{
	}
	
	recordedTime = time[T1];
	
	displayString(0, "Time Interval Set: %f", recordedTime);
	
	return recordedTime;
}
