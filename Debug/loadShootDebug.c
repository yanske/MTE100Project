//Debugging for shooting and loading mechanism

void shootBall(float time, int pullBackValue)
{
	const int PULL_BACK = pullBackValue;
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

void loadBall(int power)
{
	nMotorEncoder[motorA] = 0;
	while (nMotorEncoder < 360)
	{
		motor[motorA] = power;
	}
	motor[motorA] = 0;
	
}

float debugLoadBall(int power)
{
	/*
	Purpose: find appropraite power for ball loading motor
	*/
	time1[T1] = 0;
	loadBall(power);
	return time1[T1] = 0;
}


int main()
{
	displayString(0, "P%d, T%f", 20, debugLoadBall(20));
	displayString(0, "P%d, T%f", 30, debugLoadBall(30));
	displayString(0, "P%d, T%f", 40, debugLoadBall(40));
	displayString(0, "P%d, T%f", 50, debugLoadBall(50));

}