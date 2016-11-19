void setLocation(float time){ 

	/*
	Assuming we already set the motor encoder 
	i also assumed the motor encoder was set at the end of the table (so at the end it = 0)
	assumes the table can handle 90 degrees (so 45 degrees to each side)
	*/

	float encCount = 0;
	float time = 0;
	float timeRotate = 0;	 
	bool turn = true; // assuming going forward is true
	time = // some formula that converts time to encoder count
	turn = random(1)
	encCount = random (time/2)
	if (turn){
		if (encCount + nMotorEncoder[motorA] > 90){
			encCount = 90;
	}
	}

	else{
		if(nMotorEncoder[motorA] - encCount < 0){
			encCount = 0;
		}
	}
	timeRotate = // some formula that converts encoder count back to time

		

	rotate(turn, timeRotate); // jon's function

}

/*editing in debug
bool checkBall(bool ball){
	if(there is no ball){
		nMotorEncoder[motorA] = 0;
		while (nMotorEncoder < 360){
			motor[motorA] = 20;
		}
		motor[motorA] = 0;
	}
}
*/

bool displayData(float time, int shotIndex, int total)
{
	bool shotsRemaining = 0;
	displayString(1, "Frequency: 1 ball/%.2fs", time/1000);
	displayString(2, "Balls shot: %d", shotIndex);
	displayString(3, "Remaining shots: %d", total - shotIndex;
	if(total - shotIndex > 0)
		shotsRemaining = 1;

	return shotsRemaining;
}

/*
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
*/


bool checkStop(bool shotsReached)
{
	const int MAX_RANGE = 50;
	if(SensorValue[S1] < MAX_RANGE || shotsReached)
		return true; //ie stop
	else 
		return false;
}


task main()
{
	//initializesensors
}