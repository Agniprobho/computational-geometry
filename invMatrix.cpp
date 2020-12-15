void inverseMatrix(double **Matrix, double **inverseMatrix, int Size)
{
/*
	Purpose: Matrix inversion
	Author: Agniprobho Mazumder 
	Parameters: 
		Input, Matrix to be inverted and its size
		Output, Inverse matrix
*/

	double det, **MatrixT, M11, M12, M13, M21, M22, M23, M31, M32, M33;

	// inverse of a 3x3 matrix
	MatrixT=new double *[3];
	for(int i=0; i<3; i++)
	{
		MatrixT[i]=new double[3];
	}

	det=Matrix[0][0]*(Matrix[1][1]*Matrix[2][2]-Matrix[2][1]*Matrix[1][2])-Matrix[0][1]*(Matrix[2][2]*Matrix[1][0]-Matrix[2][0]*Matrix[1][2])
		+Matrix[0][2]*(Matrix[2][1]*Matrix[1][0]-Matrix[2][0]*Matrix[1][1]);

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			MatrixT[i][j]=Matrix[j][i];
		}
	}

	M11=MatrixT[2][2]*MatrixT[1][1]-MatrixT[2][1]*MatrixT[1][2];
	M12=MatrixT[2][2]*MatrixT[1][0]-MatrixT[2][0]*MatrixT[1][2];
	M13=MatrixT[2][1]*MatrixT[1][0]-MatrixT[2][0]*MatrixT[1][1];

	M21=MatrixT[2][2]*MatrixT[0][1]-MatrixT[2][1]*MatrixT[0][2];
	M22=MatrixT[2][2]*MatrixT[0][0]-MatrixT[2][0]*MatrixT[0][2];
	M23=MatrixT[2][1]*MatrixT[0][0]-MatrixT[2][0]*MatrixT[0][1];

	M31=MatrixT[1][2]*MatrixT[0][1]-MatrixT[1][1]*MatrixT[0][2];
	M32=MatrixT[1][2]*MatrixT[0][0]-MatrixT[1][0]*MatrixT[0][2];
	M33=MatrixT[1][1]*MatrixT[0][0]-MatrixT[1][0]*MatrixT[0][1];

	inverseMatrix[0][0]=M11/det;
	inverseMatrix[0][1]=-M12/det;
	inverseMatrix[0][2]=M13/det;

	inverseMatrix[1][0]=-M21/det;
	inverseMatrix[1][1]=M22/det;
	inverseMatrix[1][2]=-M23/det;

	inverseMatrix[2][0]=M31/det;
	inverseMatrix[2][1]=-M32/det;
	inverseMatrix[2][2]=M33/det;


	for(int i=0; i<3; i++)
	{
		delete []MatrixT[i];
	}
	delete []MatrixT;
}