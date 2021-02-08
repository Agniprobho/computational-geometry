void Intevals()
{
	int n = 28;
	int N = 28;
	double X[28] = {};
	double Y[28] = {};
	double x[28], y[28], m, interval;
	double firstX = 0.0;
	double firstY = 0.0;
	double lastX = ;
	double lastY = ;
	interval = (lastX - firstX)/(N-1);
	
	x[0] = 0.0;
	y[0] = 0.0;
	
	for (int i=1; i<N-1; i++)
	{
		x[i] = x[i-1]+interval;
	}
	
	x[N-1] = lastX;
	y[N-1] = lastY;
	
	for (int i=1; i<N-1; i++)
	{
		for (int j=0; j<n-1; j++)
		{
			if (x[i]>=X[j] && x[i]<=X[j+1])
			{
				m = (Y[j+1]-Y[j])/(X[j+1]-X[j]);
				y[i] = m*(x[i]-X[j]) + Y[j];
			}
		}
	}
	
	ofstream foutXY;
	foutXY.open(newDir+"//datapoints.txt");
	for (int i=0; i<N; i++)
	{
		foutXY<<x[i]<<"\t"<<y[i]<<"\n";
	}
	foutXY.close();
}

