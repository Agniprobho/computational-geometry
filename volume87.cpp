void v87(double *CN)
{
/*
	Purpose: 87 FLOPS volume calculation for any arbitrary hexahedron
	Author: Agniprobho Mazumder 
	Details: Splits hexahedron into 5 tetrahedrons 
	Parameters: 
		m_COORN stores the vertex coordinates of hexahedron
		Input, CN stores the node numbers of the vertices
*/

	double v1a[3], v1b[3], v1c[3], v2c[3], v3c[3], v4c[3], v5a[3], v5b[3], v5c[3], cp1[3], cp3[3], cp4[3], cp5[3];
	double 	vol1, vol2, vol3, vol4, vol5, volumeEle;
	
	//vectors
	v1a[0] = m_COORN[3*CN[6]] - m_COORN[3*CN[4]];
	v1a[1] = m_COORN[3*CN[6]+1] - m_COORN[3*CN[4]+1];
	v1a[2] = m_COORN[3*CN[6]+2] - m_COORN[3*CN[4]+2];
	
	v1b[0] = m_COORN[3*CN[7]] - m_COORN[3*CN[4]];
	v1b[1] = m_COORN[3*CN[7]+1] - m_COORN[3*CN[4]+1];
	v1b[2] = m_COORN[3*CN[7]+2] - m_COORN[3*CN[4]+2];
	
	v1c[0] = m_COORN[3*CN[3]] - m_COORN[3*CN[4]];
	v1c[1] = m_COORN[3*CN[3]+1] - m_COORN[3*CN[4]+1];
	v1c[2] = m_COORN[3*CN[3]+2] - m_COORN[3*CN[4]+2];
	
	v2c[0] = m_COORN[3*CN[1]] - m_COORN[3*CN[4]];
	v2c[1] = m_COORN[3*CN[1]+1] - m_COORN[3*CN[4]+1];
	v2c[2] = m_COORN[3*CN[1]+2] - m_COORN[3*CN[4]+2];
	
	v3c[0] = m_COORN[3*CN[0]] - m_COORN[3*CN[4]];
	v3c[1] = m_COORN[3*CN[0]+1] - m_COORN[3*CN[4]+1];
	v3c[2] = m_COORN[3*CN[0]+2] - m_COORN[3*CN[4]+2];
	
	v4c[0] = m_COORN[3*CN[5]] - m_COORN[3*CN[4]];
	v4c[1] = m_COORN[3*CN[5]+1] - m_COORN[3*CN[4]+1];
	v4c[2] = m_COORN[3*CN[5]+2] - m_COORN[3*CN[4]+2];
	
	v5a[0] = m_COORN[3*CN[6]] - m_COORN[3*CN[3]];
	v5a[1] = m_COORN[3*CN[6]+1] - m_COORN[3*CN[3]+1];
	v5a[2] = m_COORN[3*CN[6]+2] - m_COORN[3*CN[3]+2];
	
	v5b[0] = m_COORN[3*CN[2]] - m_COORN[3*CN[3]];
	v5b[1] = m_COORN[3*CN[2]+1] - m_COORN[3*CN[3]+1];
	v5b[2] = m_COORN[3*CN[2]+2] - m_COORN[3*CN[3]+2];
	
	v5c[0] = m_COORN[3*CN[1]] - m_COORN[3*CN[3]];
	v5c[1] = m_COORN[3*CN[1]+1] - m_COORN[3*CN[3]+1];
	v5c[2] = m_COORN[3*CN[1]+2] - m_COORN[3*CN[3]+2];
	
	//cross products
	cp1[0] = v1a[1]*v1c[2]-v1a[2]*v1c[1];	//v1aXv1c
	cp1[1] = -(v1a[0]*v1c[2]-v1a[2]*v1c[0]);
	cp1[2] = v1a[0]*v1c[1]-v1a[1]*v1c[0];
	
	cp3[0] = v1c[1]*v3c[2]-v1c[2]*v3c[1];	//v1cXv3c
	cp3[1] = -(v1c[0]*v3c[2]-v1c[2]*v3c[0]);
	cp3[2] = v1c[0]*v3c[1]-v1c[1]*v3c[0];
	
	cp4[0] = v1a[1]*v4c[2]-v1a[2]*v4c[1];	//v1aXv4c
	cp4[1] = -(v1a[0]*v4c[2]-v1a[2]*v4c[0]);
	cp4[2] = v1a[0]*v4c[1]-v1a[1]*v4c[0];
	
	cp5[0] = v5b[1]*v5c[2]-v5b[2]*v5c[1];	//v5bXv5c
	cp5[1] = -(v5b[0]*v5c[2]-v5b[2]*v5c[0]);
	cp5[2] = v5b[0]*v5c[1]-v5b[1]*v5c[0];
	
	//volumes
	vol1 = fabs(v1b[0]*cp1[0] + v1b[1]*cp1[1] + v1b[2]*cp1[2]);
	vol2 = fabs(v2c[0]*cp1[0] + v2c[1]*cp1[1] + v2c[2]*cp1[2]);
	vol3 = fabs(v2c[0]*cp3[0] + v2c[1]*cp3[1] + v2c[2]*cp3[2]);
	vol4 = fabs(v2c[0]*cp4[0] + v2c[1]*cp4[1] + v2c[2]*cp4[2]);
	vol5 = fabs(v5a[0]*cp5[0] + v5a[1]*cp5[1] + v5a[2]*cp5[2]);
	
	//total volume
	volumeEle = (vol1 + vol2 + vol3 + vol4 + vol5)/6.;
}