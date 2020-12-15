double v60(int *CN)
{
/*
	60 FLOPS volume calculation for any arbitrary hexahedron
	Reference: https://www.osti.gov/servlets/purl/632793 
	m_COORN stores the vertex coordinates of hexahedron
	CN stores the node numbers of the vertices
*/
	
	double v1a[3], v1b[3], v1c[3], v2b[3], v2c[3], v3b[3], v3c[3], cp1[3], cp2[3], cp3[3], vol1, vol2, vol3, vol;

	//vectors
	v1a[0] = m_COORN[3 * CN[6]] - m_COORN[3 * CN[0]];
	v1a[1] = m_COORN[3 * CN[6] + 1] - m_COORN[3 * CN[0] + 1];
	v1a[2] = m_COORN[3 * CN[6] + 2] - m_COORN[3 * CN[0] + 2];

	v1b[0] = m_COORN[3 * CN[1]] - m_COORN[3 * CN[0]];
	v1b[1] = m_COORN[3 * CN[1] + 1] - m_COORN[3 * CN[0] + 1];
	v1b[2] = m_COORN[3 * CN[1] + 2] - m_COORN[3 * CN[0] + 2];

	v1c[0] = m_COORN[3 * CN[3]] - m_COORN[3 * CN[5]];
	v1c[1] = m_COORN[3 * CN[3] + 1] - m_COORN[3 * CN[5] + 1];
	v1c[2] = m_COORN[3 * CN[3] + 2] - m_COORN[3 * CN[5] + 2];

	v2b[0] = m_COORN[3 * CN[4]] - m_COORN[3 * CN[0]];
	v2b[1] = m_COORN[3 * CN[4] + 1] - m_COORN[3 * CN[0] + 1];
	v2b[2] = m_COORN[3 * CN[4] + 2] - m_COORN[3 * CN[0] + 2];

	v2c[0] = m_COORN[3 * CN[5]] - m_COORN[3 * CN[7]];
	v2c[1] = m_COORN[3 * CN[5] + 1] - m_COORN[3 * CN[7] + 1];
	v2c[2] = m_COORN[3 * CN[5] + 2] - m_COORN[3 * CN[7] + 2];

	v3b[0] = m_COORN[3 * CN[3]] - m_COORN[3 * CN[0]];
	v3b[1] = m_COORN[3 * CN[3] + 1] - m_COORN[3 * CN[0] + 1];
	v3b[2] = m_COORN[3 * CN[3] + 2] - m_COORN[3 * CN[0] + 2];

	v3c[0] = m_COORN[3 * CN[7]] - m_COORN[3 * CN[2]];
	v3c[1] = m_COORN[3 * CN[7] + 1] - m_COORN[3 * CN[2] + 1];
	v3c[2] = m_COORN[3 * CN[7] + 2] - m_COORN[3 * CN[2] + 2];

	//cross products
	cp1[0] = v1b[1] * v1c[2] - v1b[2] * v1c[1];	//v1bXv1c
	cp1[1] = -(v1b[0] * v1c[2] - v1b[2] * v1c[0]);
	cp1[2] = v1b[0] * v1c[1] - v1b[1] * v1c[0];

	cp2[0] = v2b[1] * v2c[2] - v2b[2] * v2c[1];	//v2bXv2c
	cp2[1] = -(v2b[0] * v2c[2] - v2b[2] * v2c[0]);
	cp2[2] = v2b[0] * v2c[1] - v2b[1] * v2c[0];

	cp3[0] = v3b[1] * v3c[2] - v3b[2] * v3c[1];	//v3bXv3c
	cp3[1] = -(v3b[0] * v3c[2] - v3b[2] * v3c[0]);
	cp3[2] = v3b[0] * v3c[1] - v3b[1] * v3c[0];

	//volumes
	vol1 = fabs(v1a[0] * cp1[0] + v1a[1] * cp1[1] + v1a[2] * cp1[2]);
	vol2 = fabs(v1a[0] * cp2[0] + v1a[1] * cp2[1] + v1a[2] * cp2[2]);
	vol3 = fabs(v1a[0] * cp3[0] + v1a[1] * cp3[1] + v1a[2] * cp3[2]);

	//total volume
	vol = (vol1 + vol2 + vol3) / 6.;

	return vol;
}