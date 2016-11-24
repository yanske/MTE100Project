//=== JC Functions =======================================
void rotate(bool left, float time, int encoder)
{
	float halfTime = time / 2, randomTime = 0;
	int power = 5;

	if(left)
		power = 10;

	else
		power = -10;

	if(time < 0) 							// User setting location manually
	{
		motor[motorB] = power; 	// Need to check if this rotates left or right
		wait1Msec(500);
	}

	else	// Randomized
	{
		randomTime = random[halfTime];	// Select random time between 0 and halfTime
		time1[T1] = 0;									// Reset timer
		motor[motorB] = power;					// Begin moving shooting mechanism

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

//Touch Sensor Timer Function
float touchTimer()
{
	displayString(0, "Hold Touch Sensor");
	displayString(1, "to set shot");
	displayString(2, "interval");

	float recordedTime = 0;

	while(SensorValue[S1] == 0) // Need to check sensor port
	{
	}

	time1[T1] = 0;

	while(SensorValue[S1] == 1)
	{
	}

	recordedTime = time1[T1];

	eraseDisplay();
	displayString(0, "Time Interval");
	displayString(1, "Set: %f", recordedTime);

	return recordedTime;
}

//=== NC Functions ================================
void setLocation(float time)
{
	/*
	Assuming we already set the motor encoder
	Shooting mechanism pointing straight = motor encoder is 0
	*/

	float encCount = 0;						// Random encoder count
	bool turn = false;

	int firstRandom = 0, secondRandom = 0;
	firstRandom = random(3);
	secondRandom = random(3);

	if(firstRandom == secondRandom)
		turn = true;

	encCount = random(25);				// Randomize encoder location

	if(!turn)
		encCount = -encCount;				// Set to negative count if turning right

	rotate(turn, time, encCount);	// Send L/R, shot interval, encoder loaction
}


void loadBall(){
	nMotorEncoder[motorC] = 0;
	while (nMotorEncoder[motorC] > -360)
		motor[motorC] = -50;
	motor[motorC] = 0;
}

//=== YK Functions ==========================================
void shootBall(float time, int pullBackValue, int power)
{
	const int PULL_BACK = pullBackValue;
	//time1[T1] = 0;
	nMotorEncoder[motorA] = 0;
	motor[motorA] = power;

	while(nMotorEncoder[motorA]>PULL_BACK){}
	motor[motorA] = 0;

	//loadBall(); //edit to appropriate power
	//while(time1[T1]< time){}
	motor[motorA] = power;

	while(nMotorEncoder[motorA]>-360){}  //test to see if there is a margine of error and a loop to set it to 360 is needed
	motor[motorA] = 0;
}

bool checkStop(bool shotsLeft)
{
	const int MAX_RANGE = 100;
	if(SensorValue[S2] < MAX_RANGE || !shotsLeft)
		return true; //ie stop
	else
		return false;
}

//=== SQ Functions ======================================
bool displayData(float time, int shotIndex, int total)
{
	eraseDisplay();
	bool shotsRemaining = false;
	displayString(1, "Frequency: 1 ball/%.2fs", time/1000);
	displayString(2, "Balls shot: %d", shotIndex);
	displayString(3, "Remaining shots: %d", total - shotIndex);
	if(total - shotIndex > 0)
		shotsRemaining = true;

	return shotsRemaining;
}

//=== Button Hold / Release Function ====================
void buttonHold(button)
{
	while(nNxtButtonPressed == -1){}
	while(nNxtButtonPressed != -1){}
}

//=== MAIN ==============================================
task main()
{

	
	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorSONAR;
	float time = 0;
	int totalShots = 0, shotsShot = 0;

	bool randomShot = true, eStop = false; //emergency stop

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
		displayString(6, "Press orange")
		displayString(7, "button to go on");

		while(nNxtButtonPressed == -1) {}

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

	do
	{
		eraseDisplay();
		time = touchTimer();
		displayString(3, "Press Orange");
		displayString(4, "button to go on");
		displayString(5, "Else press any");
		displayString(6, "other button");
		displayString(7, "to reset interval");

		while(nNxtButtonPressed == -1){}
	} while(nNxtButtonPressed != 3);

	eraseDisplay();
	displayString(1, "Select # of shots:");
	displayString(2, "-Left to -1");
	displayString(3, "-Right to +1");
	displayString(4, "-Hold to +-5");
	displayString(5, "-Orange to enter");
	displayString(6, "Total Shots: %d", totalShots);
	wait1Msec(1000);

	while (nNxtButtonPressed !=3){
		while(nNxtButtonPressed == -1){}
		if(nNxtButtonPressed == 1)
		{
			time1[T2] = 0;
			while(nNxtButtonPressed == 1)
			{

				if(time1[T2] > 1000)
				{
					totalShots+=5;
					displayString(6, "                         ");
					displayString(6, "Total Shots: %d", totalShots);
					time1[T2] = 0;
				}
			}

			if(time1[T2] <= 500)
			{
				totalShots++;
				displayString(6, "                         ");
				displayString(6, "Total Shots: %d", totalShots);
			}

		}

		else if(nNxtButtonPressed == 2)
		{
			time1[T2] = 0;
		while(nNxtButtonPressed == 2)
			{

				if(time1[T2] > 1000)
				{
					totalShots-=5;
					displayString(6, "                         ");
					displayString(6, "Total Shots: %d", totalShots);
					time1[T2] = 0;
				}
			}

			if(time1[T2] <= 500)
			{
				totalShots--;
				displayString(6, "                         ");
				displayString(6, "Total Shots: %d", totalShots);
			}

		}
	}
	while(nNxtButtonPressed == 3){};

	eraseDisplay();
	displayString(0, "Start by");
	displayString(1, "putting racket");
	displayString(2, "in front of");
	displayString(3, "sonar sensor");

	while(SensorValue[S2] > 150){}

	if(totalShots-shotsShot){

	while(!eStop)
	{
		time1[T1] = 0;

		if(randomShot)
			setLocation(time);

		loadBall();

		while(time1[T1] < time - 200){}

		shootBall(0, -170, -60);
		shotsShot++;

		eStop = displayData(time, shotsShot, totalShots);
		eStop = checkStop(totalShots-shotsShot);
	}

	while(nNxtButtonPressed == -1){}   //Let user see displayData stuff
	eraseDisplay();
	displayString(0, "Press any button");
	displayString(1, "to end program");
	}
}
