void matrixMult(double **MatrixA, int RowA, int ColA, double **MatrixB, int ColB, double **MatrixC)
{
/*
	Purpose: Matrix Multiplication
	Author: Agniprobho Mazumder 
	Parameters: 
		Input, Matrices A and B and their sizes
		Output, Matrix C
*/

	//ColA=RowB  RowC=RowA  ColC=ColB
	for(int k=0; k<ColB; k++)
	{
		for(int i=0; i<RowA; i++)
		{
			for(int j=0; j<ColA; j++)
			{
				MatrixC[i][k]+= MatrixA[i][j]*MatrixB[j][k];
			}
		}
	}
}