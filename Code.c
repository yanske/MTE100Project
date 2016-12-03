//=== Rotate Function - Written by Jonathan Chung =============
void rotate(bool left, float time, int encoder)
{
	float halfTime = time / 2, randomTime = 0;
	int power = 5;

	if(left)
		power = 10;

	else
		power = -10;

	if(time < 0) 			// User setting location manually
	{
		motor[motorB] = power; 	// Rotate in direction user is indicating
		wait1Msec(500);		
	}

	else		// Randomized location setting
	{
		randomTime = random[halfTime];	// Select random time between 0 and halfTime
		time1[T1] = 0;			// Reset timer
		motor[motorB] = power;		// Begin moving shooting mechanism

		while(time1[T1] < randomTime)
		{
			if(left)
				while(nMotorEncoder[motorB] < encoder){}
			else
				while(nMotorEncoder[motorB] > encoder){}
		}
	}

	motor[motorB] = 0;
}

//=== Timer Function - Written by Jonathan Chung ===============
float touchTimer()
{
	displayString(0, "Hold Touch Sensor");
	displayString(1, "to set shot");
	displayString(2, "interval");

	float recordedTime = 0;

	while(SensorValue[S1] == 0)
	{
	}

	time1[T1] = 0;

	while(SensorValue[S1] == 1)
	{
	}

	recordedTime = time1[T1];

	eraseDisplay();
	displayString(0, "Time Interval");
	displayString(1, "Set: %f", recordedTime/1000);

	return recordedTime;
}

//=== Randomized Location Function - Written by Naitao Cui ==============
void setLocation(float time)
{
	/*
	Shooting mechanism pointing straight = motor encoder is 0
	Maximum Angle of Rotateion = 25 degrees on both sides
	*/

	float encCount = 0;				// Variable for random encoder count
	bool turn = false;

	int firstRandom = 0, secondRandom = 0;
	firstRandom = random(3);
	secondRandom = random(3);

	if(firstRandom == secondRandom)
		turn = true;

	encCount = random(25);				// Randomize encoder location

	if(!turn)
		encCount = -encCount;			// Set to negative encoder count if turning right

	rotate(turn, time, encCount);	// Send L/R, shot interval, encoder loaction to rotate function
}

//=== Load Function - Written by Naitao Cui ==============
void loadBall(){
	nMotorEncoder[motorC] = 0;
	while (nMotorEncoder[motorC] > -341)		// Encoder count for 1 rotation (Motor slightly off)
		motor[motorC] = -42;
	motor[motorC] = 0;
}

//=== Shoot Function - Written by Yan Song Ke =============
void shootBall(float time, int pullBackValue, int power)
{
	const int PULL_BACK = pullBackValue;		// Encoder count to pull shooter arm back
	nMotorEncoder[motorA] = 0;
	motor[motorA] = power;

	while(nMotorEncoder[motorA] > PULL_BACK){}
	motor[motorA] = 0;

	motor[motorA] = power;

	while(nMotorEncoder[motorA] > -380){} 		// Reset arm back to original position
	motor[motorA] = 0;
}

//=== Emergency Stop Function - Written by Yan Song Ke ==============
bool checkStop(bool shotsLeft)
{
	const int MAX_RANGE = 100;			// Max range to trigger sonar sensor
	if(SensorValue[S2] < MAX_RANGE || !shotsLeft)	// If object in front of sensor or no more shots left
		return true; //ie stop
	return false;
}

//=== Button Held Down for Desired Shots Function - Written by Yan Song Ke ==============
void buttonHold(bool right, int & totalShots)
{
		time1[T2] = 0;
		bool debounce = false;			// Boolean to jump 5 shots
		int buttonValue = 1;
		if(!right)
		{
			buttonValue =2;
		}
		while(nNxtButtonPressed == buttonValue)	// While button is being held down
		{
			if(time1[T2] > 900)		// If button held for more than certain time
			{
				debounce = true;
				if(right)
				{
					totalShots+=5;	// +5 shots to "desired shots"
				}
				else
				{
					totalShots-=5;	// -5 shots to "desired shots"
				}

				if(totalShots < 0)
				{
					totalShots =0;
				}

				displayString(6, "                         ");
				displayString(6, "Total Shots: %d", totalShots);
				time1[T2] = 0;
			}
		}
		if(!debounce)				//ensures that if held for slightly more than the set interval, it doesn't also in/de-crement by 1
		{
				if(right)
				{
					totalShots++;
				}
				else
				{
					totalShots--;
				}

				if(totalShots < 0)
				{
					totalShots = 0;
				}
			displayString(6, "                         ");
			displayString(6, "Total Shots: %d", totalShots);
		}
}

//=== Display Data Function - Written by Sara Qi ==============
void displayData(float time, int shotIndex, int total)
{
	eraseDisplay();
	displayString(1, "Frequency: 1 ball/%.2fs", time/1000);
	displayString(2, "Balls shot: %d", shotIndex);
	displayString(3, "Remaining shots: %d", total - shotIndex);
}

//=== Button Hold / Release Function ====================
void buttonHold()
{
	while(nNxtButtonPressed == -1){}
	while(nNxtButtonPressed != -1){}
}

//=== MAIN ==============================================
task main()
{
	SensorType[S1] = sensorTouch;		// Initialize sensors
	SensorType[S2] = sensorSONAR;
	float time = 0;				// Shooting time interval (time between shots)
	int totalShots = 0, shotsShot = 0;
	bool randomShot = true, eStop = false;	// Random location boolean 
						// and emergency stop boolean

	displayString(0, "Set Location");
	displayString(1, "Press left button");
	displayString(2, "for random");
	displayString(3, "locations");
	displayString(5, "Press right button");
	displayString(6, "to set manually");

	while(nNxtButtonPressed == -1 || nNxtButtonPressed == 3 || nNxtButtonPressed == 0){}

	if(nNxtButtonPressed == 1)
	{
		eraseDisplay();
		displayString(0, "Manual Set");
		displayString(1, "Press right button");
		displayString(2, "to rotate right");
		displayString(3, "Press left button");
		displayString(4, "to rotate left");
		displayString(6, "Press orange");
		displayString(7, "button to go on");

		while(nNxtButtonPressed != -1){}

		while(nNxtButtonPressed != 3)
		{
			while(nNxtButtonPressed == -1){}

			if(nNxtButtonPressed == 1)
				rotate(false, -1, 0);

			else if(nNxtButtonPressed == 2)
				rotate(true, -1, 0);

			while(nNxtButtonPressed == -1){}
		}
		randomShot = false;
	}

	while(nNxtButtonPressed != -1){} // If button being held down, don't do anything

	do
	{
		eraseDisplay();
		time = touchTimer();	// Set shooting time interval via touch sensor
		displayString(3, "Press Orange");
		displayString(4, "button to go on");
		displayString(5, "Else press any");
		displayString(6, "other button");
		displayString(7, "to reset interval");

		while(nNxtButtonPressed == -1){}
	} while(nNxtButtonPressed != 3);

	while(nNxtButtonPressed != -1){} // If button being held down, don't do anything

	eraseDisplay();
	displayString(1, "Select # of shots:");
	displayString(2, "-Left to -1");
	displayString(3, "-Right to +1");
	displayString(4, "-Hold to +5/-5");
	displayString(5, "-Orange to enter");
	displayString(6, "Total Shots: %d", totalShots);
	wait1Msec(1000);

	while (nNxtButtonPressed !=3)
	{
		while(nNxtButtonPressed == -1){}
		if(nNxtButtonPressed == 1)
		{
			buttonHold(true, totalShots);
		}

		else if(nNxtButtonPressed == 2)
		{
			buttonHold(false,totalShots);
		}
	}

	while(nNxtButtonPressed == 3){}; 

	eraseDisplay();
	displayString(0, "Start by");
	displayString(1, "putting racket");
	displayString(2, "in front of");
	displayString(3, "sonar sensor");

	while(SensorValue[S2] > 100){}

	if(totalShots-shotsShot){

		while(!eStop)
		{
			time1[T1] = 0;

			if(randomShot)		// If random location setting
				setLocation(time);

			loadBall();

			while(time1[T1] < time - 200){}	// Wait for time interval to be reached

			shootBall(0, -170, -60);
			shotsShot++;

			displayData(time, shotsShot, totalShots);
			eStop = checkStop(totalShots-shotsShot);
		}

		displayString(4, "Press any button");
		displayString(5, "to end program");
		buttonHold(); 	//Let user see displayData data
		eraseDisplay();
	}
}
