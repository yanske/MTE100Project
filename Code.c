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
	eraseDisplay();
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
	int totalShots = 0, shotsShot = 0;
	
	bool randomShot = true, eStop = false, ballsLeft = true; //emergency stop
	
	displayString(0, "Set Location");
	displayString(1, "Left - Random");
	displayString(2, "Right - Manual");
	
	while(nNxtButtonPressed == -1 || nNxtButtonPressed == 3 || nNxtButtonPressed == 0){}
	
	//Accept number of desired shots
	
	if(nNxtButtonPressed == 1)
	{
		//Output Instructions
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
		displayString(1, "Press 3 to go on");
		displayString(2, "Else press any");
		displayString(3, "other button");
		displayString(4, "to set interval");
		displayString(5, "again");
		
		while(nNxtButtonPressed == -1){}
	} while(nNxtButtonPressed != 3);
	
	eraseDisplay();
	displayString(0, "Start by");
	displayString(1, "putting racket");
	displayString(2, "in front of");
	displayString(3, "sonar sensor");
	
	while(SensorValue[S2] > 150){}
	
	while(ballsLeft && eStop == false)
	{
		time1[T1] = 0;
	
		if(randomShot)
			setLocation(time);
		
		loadBall();	
		
		while(time1[T1] < time - 200){}
		
		shootBall(0, -170, -60);
		
		eStop = displayData(time, shotsShot, totalShots);
		eStop = checkStop(shotsShot);
	}
}
