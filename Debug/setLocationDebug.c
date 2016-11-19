void setLocation(float time, bool left, int encoder)
{
	float halfTime = time / 2;
	int power = 5;
	displayString(0, "%d" , encoder);



	if(!left)
		power = -5;

	if(time < 0) // User setting location manually
	{
		motor[motorB] = power; // Need to check if this rotates left or right
		wait1Msec(100);
	}

		float randomTime = time ;		// Select random time between 0 and halfTime
		time1[T1] = 0;							// Reset timer
		motor[motorB] = power;			// Begin moving shooting mechanism

		if(left)
		while((nMotorEncoder[motorB]) < (encoder) && time1[T1] < randomTime){}

		else
					while((nMotorEncoder[motorB]) > (encoder) && time1[T1] < randomTime){}

		motor[motorB] = 0;

}


void buttonwait()
{
	while(nNxtButtonPressed == -1){}
	while(nNxtButtonPressed != -1){}
}

task main()
{
	nMotorEncoder[motorB] = 0;
	setLocation(2000, true, 20);
	buttonwait();

	eraseDisplay();
	setLocation(5000, false, -40);
	buttonwait();

	eraseDisplay();
	setLocation(5000, true, 60);
	buttonwait();

	eraseDisplay();
	setLocation(4500, false, -5);
	buttonwait();

	eraseDisplay();
	setLocation(6500, true, 32);
	buttonwait();

}
