void directionVectors(int ng)
{
/*
	Purpose: SPHERE_FIBONACCI_GRID_POINTS computes sphere points on a Fibonacci spiral, generate uniformly distributed points for unit vector directions
	Licensing: This code is distributed under the GNU LGPL license.
	Modified: 14 May 2015
	Author: John Burkardt
	Reference:
		Richard Swinbank, James Purser, Fibonacci grids: A novel approach to global modelling, Quarterly Journal of the Royal Meteorological Society,
		Volume 132, Number 619, July 2006 Part B, pages 1769-1793.
	Parameters:
		Input, int NG, the number of points.
		Output, double SPHERE_FIBONACCI_GRID_POINTS[3*NG], the Fibonacci spiral points.	
*/

	double cphi;
	double i_r8;
	int j;
	double ng_r8;
	double r8_phi;
	double sphi;
	double theta;

	vec = new double[3*ng];

	r8_phi = ( 1.0 + sqrt ( 5.0 ) ) / 2.0;
	ng_r8 = ( double ) ( ng );

	for ( j = 0; j < ng; j++ )
	{
		i_r8 = ( double ) ( - ng + 1 + 2 * j );
		theta = 2.0 * PI2 * i_r8 / r8_phi;
		sphi = i_r8 / ng_r8;
		cphi = sqrt ( ( ng_r8 + i_r8 ) * ( ng_r8 - i_r8 ) ) / ng_r8;
		vec[0+j*3] = cphi * sin ( theta );
		vec[1+j*3] = cphi * cos ( theta );
		vec[2+j*3] = sphi;
	}
}