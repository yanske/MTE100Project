void setLocation(float time)
{
	/*
	Assuming we already set the motor encoder 
	Shooting mechanism pointing straight = motor encoder is 0
	*/
	
	float encCount = 0;	// Random encoder count
	bool turn = true; // assuming going left is true
	
	turn = random(1);	// Left or right? 1 = Left
	
	encCount = random(45);	// Randomize encoder location
	
	if(!turn)	
		encCount = -encCount;	// Set to negative count if turning right

	rotate(turn, time, encCount)	// Send L/R, shot interval, encoder loaction
}


bool checkBall(bool ball){
	if(there is no ball){
		nMotorEncoder[motorA] = 0;
		while (nMotorEncoder < 360){
			motor[motorA] = 20;
		}
		motor[motorA] = 0;
	}
}
