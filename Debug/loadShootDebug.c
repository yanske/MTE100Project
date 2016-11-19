//Debugging for shooting and loading mechanism

void buttonPress()
{
	while(nNxtButtonPressed==-1){}
	while(nNxtButtonPressed!=-1){}
}

bool buttonPressed()
{
	if(nNxtButtonPressed!=-1)
		return true;
	else
		return false;
}

int modifiedShootBall(float time, int power, int pullBackValue, int i)
{
	const int PULL_BACK = pullBackValue;
	time1[T1] = 0;
	nMotorEncoder[motorA] = 0;
	motor[motorA] = power;
	int cnt;

	while(nMotorEncoder[motorA]<PULL_BACK){
		if(buttonPressed())
		{
			displayString(i,"Cnt: %d", nMotorEncoder[motorA]);
			cnt = nMotorEncoder[motorA];
		}
	}
	motor[motorA] = 0;

	while(time1[T1]<time){}
	motor[motorA] = power;

	while(nMotorEncoder[motorA]<360){}  //test to see if there is a margine of error and a loop to set it to 360 is needed
	motor[motorA] = 0;
	return cnt;
}

void loadBall(int power)
{
	nMotorEncoder[motorC] = 0;
	motor[motorC] = power;
	while (nMotorEncoder[motorC] > -360){}
	motor[motorC] = 0;
}

void shootBall(float time, int pullBackValue, int power)
{
	const int PULL_BACK = pullBackValue;
	time1[T1] = 0;
	nMotorEncoder[motorA] = 0;
	motor[motorA] = power;

	while(nMotorEncoder[motorA]>PULL_BACK){}
	motor[motorA] = 0;

	loadBall(-20); //edit to appropriate power
	//while(time1[T1]< time){}
	buttonPress();
	motor[motorA] = power;

	while(nMotorEncoder[motorA]>-360){}  //test to see if there is a margine of error and a loop to set it to 360 is needed
	motor[motorA] = 0;
}

float returnLoadTime(int power)
{
	/*
	Purpose: find appropraite power for ball loading motor
	*/
	time1[T1] = 0;
	loadBall(power);
	return time1[T1]*1000;
}

void testingLoading()
{
	displayString(0, "P%d, T%f", -20, returnLoadTime(-20));
	buttonPress();
	displayString(0, "P%d, T%f", -30, returnLoadTime(-30));
	buttonPress();
	displayString(0, "P%d, T%f", -40, returnLoadTime(-40));
	buttonPress();
	displayString(0, "P%d, T%f", -50, returnLoadTime(-50));
	buttonPress();
	eraseDisplay();
}

int findENCShooting()
{
	//find correct encoder count
	int cnt = 0;
	for(int i = 0; i<3; i++)
	{
		cnt += modifiedShootBall(0, -10, 150, i);
		buttonPress();
	}
	eraseDisplay();
	return cnt/3;
}

task main()
{
	//testingLoading();
	//using loading power of -20;

	//int PB = findENCShooting();
	//displayString(0,"%d", PB);
	shootBall(0, -170, -60);
	buttonPress();
	//combined function
	//shootBall(0, PB, 20);

}
