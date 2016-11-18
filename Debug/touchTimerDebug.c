float touchTimer()
{
	displayString(0, "Hold Touch Sensor for duration");
	displayString(1, "of desired shot interval");
	
	for(int i = 0; i < 5; i ++)	//5 test cases: 1s, 2s, 3s, 4s, 5s
	{
		float recordedTime = 0;
		
		while(Sensor[S1] == 0) // Need to check sensor port
		{
		}
		
		time[T1] = 0;
		
		while(Sensor[S1] == 1) 
		{
		}
		
		recordedTime = time[T1];
	
		displayString(i, "Time Interval Set: %f", recordedTime);
	}
	
	return recordedTime;
}
