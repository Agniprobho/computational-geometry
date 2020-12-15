void shape(double& N1, double& N2, double& N3)
{
/*
	Author: Agniprobho Mazumder 
	Purpose: Calculates shape functions N1, N2, N3 of a triangle projected on the x-y plane
	Parameters: 
		x1,y1 are x and y coordinates of vertex 1
		x2,y2 are x and y coordinates of vertex 2
		x3,y3 are x and y coordinates of vertex 3
		Output, N1, N2, N3
*/
	
	double delta1, delta2, delta3, delta;

	delta = x2*y3 - y2*x3 - x1*y3 + x3*y1 + x1*y2 - x2*y1;

	if (fabs(delta)> 0)
	{
		delta1 = x2*y3 - y2*x3 - x*y3 + x3*y + x*y2 - x2*y;
		delta2 = x*y3 - y*x3 - x1*y3 + x3*y1 + x1*y - x*y1;
		delta3 = x2*y - y2*x - x1*y + x*y1 + x1*y2 - x2*y1;
		N1 = delta1/delta;
		N2 = delta2/delta;
		N3 = delta3/delta;
	}
}