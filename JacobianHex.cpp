double Jacobian(double x, double y, double z, double *CN)
{
/*
	Author: Agniprobho Mazumder 
	Purpose: Returns determinant of Jacobian (of a hex element) at sampling location with coordinates x, y, z
	Parameters: 
		Input, x, y and z are coordinates of sampling location in consideration coordinates of vertex 1
		Input, Input, CN stores the coordinates of the vertices/sampling locations
		Output, detJ determinant of Jacobian at given sampling location
*/
	
	double detJ; 
	double K= normalise_J(CN);	//normalize value
	double J[3][3];

	double A[8][3];	//derivatives of shape functions
	A[0][0]= -0.125*(1-y)*(1-z);
	A[0][1]= -0.125*(1-x)*(1-z);
	A[0][2]= -0.125*(1-x)*(1-y);

	A[1][0]= 0.125*(1-y)*(1-z);
	A[1][1]= -0.125*(1+x)*(1-z);
	A[1][2]= -0.125*(1+x)*(1-y);

	A[2][0]= 0.125*(1+y)*(1-z);
	A[2][1]= 0.125*(1+x)*(1-z);
	A[2][2]= -0.125*(1+x)*(1+y);

	A[3][0]= -0.125*(1+y)*(1-z);
	A[3][1]= 0.125*(1-x)*(1-z);
	A[3][2]= -0.125*(1-x)*(1+y);

	A[4][0]= -0.125*(1-y)*(1+z);
	A[4][1]= -0.125*(1-x)*(1+z);
	A[4][2]= 0.125*(1-x)*(1-y);

	A[5][0]= 0.125*(1-y)*(1+z);
	A[5][1]= -0.125*(1+x)*(1+z);
	A[5][2]= 0.125*(1+x)*(1-y);

	A[6][0]= 0.125*(1+y)*(1+z);
	A[6][1]= 0.125*(1+x)*(1+z);
	A[6][2]= 0.125*(1+x)*(1+y);

	A[7][0]= -0.125*(1+y)*(1+z);
	A[7][1]= 0.125*(1-x)*(1+z);
	A[7][2]= 0.125*(1-x)*(1+y);

	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			J[i][j]=0;
		}
	}

	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++)
		{
			for (int k=0; k<8; k++)
			{
				J[i][j]+=A[k][j]*CN[3*k+i];	//get the Jacobian matrix
			}
		}
	}

	detJ = J[0][0]*(J[1][1]*J[2][2] - J[1][2]*J[2][1]) - J[0][1]*(J[1][0]*J[2][2] - J[1][2]*J[2][0]) + J[0][2]*(J[1][0]*J[2][1] - J[1][1]*J[2][0]);	//determinant of Jacobian matrix

	return K*detJ;
}