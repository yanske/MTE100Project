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


bool checkBall(bool ball){
	if(there is no ball){
		nMotorEncoder[motorA] = 0;
		while (nMotorEncoder < 360){
			motor[motorA] = 20;
		}
		motor[motorA] = 0;
	}
}
