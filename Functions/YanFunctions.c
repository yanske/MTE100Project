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