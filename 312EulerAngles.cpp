void EulerAngles(double *v1, double *v2, double& thxy, double& thyz, double& thzx)
{
/*
	Author: Agniprobho Mazumder 
	Purpose: Calculates 3-1-2 Tait Bryan angles
	Parameters: 
		Input, vector v1 is the unit vector in the principal direction (parallel to local x-axis)
		Input, vector v2 is the unit vector in transverse direction (parallel to local y-axis)
		vector v3 is cross product of vector v1 and v2 (parallel to local z-axis)
		Output, rotation angles thxy, thyz, thzx (in degrees)
*/

	double v3[3];
	v3[0] = v1[1] * v2[2] - v1[2] * v2[1];
	v3[1] = v1[2] * v2[0] - v1[0] * v2[2];
	v3[2] = v1[0] * v2[1] - v1[1] * v2[0];
	normalize(v3);

	thxy = atan2(-v2[0], v2[1]) * (180 / PI2);
	thyz = asin(v2[2]) * (180 / PI2);
	thzx = atan2(-v1[2], v3[2]) * (180 / PI2);
}