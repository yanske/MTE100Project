void setLocation(float time){ 

	float encCount = 0;
	float time = 0;
	float timeRotate = 0;	 
	bool left = true; // assuming going forward is true
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