//=== JC Functions =======================================
void rotate(bool left, float time, int encoder)
{
	float halfTime = time / 2, randomTime = 0;
	int power = 5;

	if(left)
		power = 5;

	else
		power = -5;

	if(time < 0) 	// User setting location manually
	{
		motor[motorB] = power; 	// Need to check if this rotates left or right
		wait1Msec(100);
	}

	else	// Randomized
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

//Touch Sensor Timer Function
float touchTimer()
{
	displayString(0, "Hold Touch Sensor for duration");
	displayString(1, "of desired shot interval");

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
	displayString(0, "Time Interval Set: %f", recordedTime);

	return recordedTime;
}

//=== NC Functions ================================
void setLocation(float time)
{
	/*
	Assuming we already set the motor encoder
	Shooting mechanism pointing straight = motor encoder is 0
	*/

	float encCount = 0;		// Random encoder count
	bool turn = true; 		// assuming going left is true

	turn = random(1);		// Left or right? 1 = Left
	encCount = random(45);		// Randomize encoder location

	if(!turn)
		encCount = -encCount;	// Set to negative count if turning right

	rotate(turn, time, encCount);	// Send L/R, shot interval, encoder loaction
}


void loadBall(){
	nMotorEncoder[motorA] = 0;
	while (nMotorEncoder[motorA] < 360)
		motor[motorA] = 20;
	motor[motorA] = 0;
}

//=== YK Functions ==========================================
void shootBall(float time)
{
	const int PULL_BACK = 0 //replace
	time1[T1] = 0;
	nMotorEncoder[motorA] = 0;
	motor[motorA] = 40;
	while(nMotorEncoder[motorA]<PULL_BACK){}
	motor[motorA] = 0;
	while(time1[T1]<time){}
	motor[motorA] = 40;
	while(nMotorEncoder[motorA]<360){}  //test to see if there is a margine of error and a loop to set it to 360 is needed
	motor[motorA] = 0;
}

bool checkStop(bool shotsReached)
{
	const int MAX_RANGE = 50;
	if(SensorValue[S1] < MAX_RANGE || shotsReached)
		return true; //ie stop
	else
		return false;
}

//=== SQ Functions ======================================
bool displayData(float time, int shotIndex, int total)
{
	bool shotsRemaining = false;
	displayString(1, "Frequency: 1 ball/%.2fs", time/1000);
	displayString(2, "Balls shot: %d", shotIndex);
	displayString(3, "Remaining shots: %d", total - shotIndex);
	if(total - shotIndex > 0)
		shotsRemaining = true;

	return shotsRemaining;
}

//=== MAIN =====================================
task main()
{
	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorSONAR;
	float time = 0;

	bool randomShot = true, eStop = false; //emergency stop

	//Output Instructions

	while(nNxtButtonPressed != 1 || nNxtButtonPressed != 2){}

	//Accept number of desired shots

	if(nNxtButtonPressed == 1)
	{
		//Output Instructions
		while(nNxtButtonPressed != 3)
		{
			if(nNxtButtonPressed == 1)
				rotate(true, -1, 0);
			else
				rotate(false, -1, 0);
		}
		randomShot = false;
	}

	while(nNxtButtonPressed != 3)
	{
		eraseDisplay();
		time = touchTimer();
		displayString(1, "Press 3 to continue");
		displayString(2, "Else press any other");
		displayString(3, "button to reset time");

		while(nNxtButtonPressed == -1){}
	}

	while(SensorValue[S2] > 100){}
	time1[T1] = 0;

	if(randomShot)
		setLocation(time);

	loadBall();

	//While time < interval location on flowchart
}
