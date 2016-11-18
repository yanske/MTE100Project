bool checkStop(bool shotsReached, int range)
{
	const int MAX_RANGE = range;
	if(SensorValue[S1] < MAX_RANGE || shotsReached)
		return true; //ie stop
	else 
		return false;
}

task main()
{
	SensorType[S1] = sensorSONAR;
	if(checkStop(false, 50))
	{
		displayString(0, "Found.");
	}
}