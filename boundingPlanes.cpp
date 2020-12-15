bool boundingPlanes(double *p1, double *p2, double *P)
{
/*
	Author: Agniprobho Mazumder 
	Purpose: Checks wheter a point lies bewteen 2 bounding planes
	Parameters: 
		Input, p1 and p2 store coordinates of 3 points on plane 1 and plane 2 respectively
		Input, P stores coordinates of point P
		Output, true if point lies inside the bounds otherwise false
*/
	double x1, y1, z1, x2, y2, z2, x3, y3, z3, n1[3], n2[3];
	bool condition1, condition2;
	
	condition1 = false;
	condition2 = false;
		 			
	//plane at j: plane 1: need only 3 points to define a plane
	x1 = p1[0];	//plane 1 first point coordinates
	y1 = p1[1];
	z1 = p1[2];
	
	x2 = p1[3];	//plane 1 second point coordinates
	y2 = p1[4];
	z2 = p1[5];
	
	x3 = p1[6];	//plane 1 third point coordinates
	y3 = p1[7];
	z3 = p1[8];
	
	//get equation of plane 1: A1x+B1y+C1z+D1=0
	n1[0] = (y2-y1)*(z3-z1) - (z2-z1)*(y3-y1);	//normal vector x-component: a2b3-a3b2
	n1[1] = (z2-z1)*(x3-x1) - (x2-x1)*(z3-z1);	//normal vector y-component: a3b1-a1b3
	n1[2] = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);	//normal vector z-component: a1b2-a2b1
	normalize(n1);
	D1 = -(n1[0]*x1 + n1[1]*y1 + n1[2]*z1);
				
	//plane 2: need only 3 points to define a plane
	x1 = p2[0];	//plane 2 first point coordinates
	y1 = p2[1];
	z1 = p2[2];
	
	x2 = p2[3];	//plane 2 second point coordinates
	y2 = p2[4];
	z2 = p2[5];
	
	x3 = p2[6];	//plane 2 third point coordinates
	y3 = p2[7];
	z3 = p2[8];
	
	//get equation of plane 2: A2x+B2y+C2z+D2=0
	n2[0] = (y2-y1)*(z3-z1) - (z2-z1)*(y3-y1);	//normal vector x-component: a2b3-a3b2
	n2[1] = (z2-z1)*(x3-x1) - (x2-x1)*(z3-z1);	//normal vector y-component: a3b1-a1b3
	n2[2] = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);	//normal vector z-component: a1b2-a2b1
	normalize(n2);
	D2 = -(n2[0]*x1 + n2[1]*y1 + n2[2]*z1)
	
	val1 = n1[0]*P[0] + n1[1]*P[1] + n1[2]*P[2] + D1;	//takes point and returns the value by substituting the x,y,z from point into the plane equation
	val2 = n1[0]*p1[0] + n1[1]*p1[1] + n1[2]*p1[2] + D1;
	val3 = n2[0]*P[0] + n2[1]*P[1] + n2[2]*P[2] + D2;	//P: point coordinates, p1: plane 1, p2: plane 2
	val4 = n2[0]*p2[0] + n2[1]*p2[1] + n2[2]*p2[2] + D2;
	
	//https://stackoverflow.com/questions/15688232/check-which-side-of-a-plane-points-are-on#:~:text=3%20Answers&text=Let%20a*x%2Bb*,same%20side%20of%20the%20plane.
	val1 = (val1<0) ? -1 : 1;	//val is sign: returns 1 for positive and -1 for negative
	val2 = (val2<0) ? -1 : 1;
	val3 = (val3<0) ? -1 : 1;
	val4 = (val4<0) ? -1 : 1;
	
	if (val1!=val2)	//point P is inside the zone
		condition1 = true;
	if (val3!=val4)
		condition2 = true;
	
	if (condition1==true && condition2==true)
		return true;
	else
		return false;
}

