void radialVector(double *P, double *A, double *v)
{
/*	
//https://stackoverflow.com/questions/5227373/minimal-perpendicular-vector-between-a-point-and-a-line
Purpose: perpendicular vector between point and line

	P
   /|
  / ^
 /  |
A---X----->v
P - point
v - unit vector along line
A - point in line
X - base of the perpendicular line
*/
	double constant, v2[3];
	
	constant = (P[0] - A[0])*v[0] + (P[1] - A[1])*v[1] + (P[2] - A[2])*v[2]; //(P-A).D
	v2[0] = P[0] - (A[0] + constant*v[0]);
	v2[1] = P[1] - (A[1] + constant*v[1]);
	v2[2] = P[2] - (A[2] + constant*v[2]);
	normalize(v2);	//radial vector
}
