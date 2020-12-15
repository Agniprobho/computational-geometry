void normalize(double v[3])
{
/*
	Purpose: Normalize a vector v
	Author: Agniprobho Mazumder
*/

	double d=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);

	if(d!=0)
	{
		v[0] /=d;
		v[1] /=d;
		v[2] /=d;
	}
}