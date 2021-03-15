#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include "omp.h"
#include <chrono>

using namespace std;

class Point
{
public:
	double x, y;
};

class Edge : public Point
{
public:
	Point a, b;
};

class Triangle : public Point
{
public:
	Point a, b, c;
};

bool operator==(const Triangle& t1, const Triangle& t2)
{
	return (t1.a.x == t2.a.x && t1.a.y == t2.a.y && t1.b.x == t2.b.x && t1.b.y == t2.b.y && t1.c.x == t2.c.x && t1.c.y == t2.c.y);
}

bool operator==(const Point& p1, const Point& p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}

bool circumPoint(Point A, Point B, Point C, Point D)
{
	//find whether a point D lies inside the circumcircle of triangle formed by points A, B, C
	double a = A.x - D.x;
	double b = A.y - D.y;
	double c = (A.x * A.x - D.x * D.x) + (A.y * A.y - D.y * D.y);
	double d = B.x - D.x;
	double e = B.y - D.y;
	double f = (B.x * B.x - D.x * D.x) + (B.y * B.y - D.y * D.y);
	double g = C.x - D.x;
	double h = C.y - D.y;
	double i = (C.x * C.x - D.x * D.x) + (C.y * C.y - D.y * D.y);

	double detD = a * (e * i - f * h) + b * (f * g - d * i) + c * (d * h - e * g);

	if (detD > 0)
		return true;
	else
		return false;
}

void triangulation(array<double, 2> Points[], int N, double scale)
{
	//Delaunay triangulation: subdivide convex hull into triangles
	Point A, B, C;
	Triangle supT, tri, T_new;
	Edge e1, e2, e3, e4, e5, e6;
	vector<Triangle> T, badT;
	vector<Edge> Poly; //polygon class, made of edges
	T.clear();	//empty triangle mesh data structure
	badT.clear();
	bool E1, E2, E3;

	//1. get super triangle
	double maxX = -1000;
	double minX = 1000;
	double maxY = -1000;
	double minY = 1000;
	for (int i = 0; i < N; i++)
	{
		if (Points[i][0] > maxX)
			maxX = Points[i][0];
		if (Points[i][0] < minX)
			minX = Points[i][0];
		if (Points[i][1] > maxY)
			maxY = Points[i][1];
		if (Points[i][1] < minY)
			minY = Points[i][1];
	}

	A.x = maxX + ((maxX - minX) / 2.) + scale;
	A.y = minY - scale;

	B.x = (maxX + minX) / 2.;
	B.y = maxY - minY + maxY;

	C.x = (maxX + minX - A.x);
	C.y = A.y;

	supT.a.x = A.x;
	supT.b.x = B.x;
	supT.c.x = C.x;

	supT.a.y = A.y;
	supT.b.y = B.y;
	supT.c.y = C.y;

	T.push_back(supT);	//add super triangle to triangulation

	//2. add all points one at a time to triangulation
#pragma omp parallel for private (pt, tri, tri1, edg, N)
	for (int pt = 0; pt < N; pt++)	//pt = point
	{
		badT.clear();	//empty badTriangles set
		A.x = Points[pt][0];
		A.y = Points[pt][1];

		for (int tri = 0; tri < T.size(); tri++)	//find triangles that are not valid due to point insertion
		{
			if (circumPoint(T.at(tri).a, T.at(tri).b, T.at(tri).c, A) == true)	//pt (point) is inside circumcircle of tri (triangle)
				badT.push_back(T.at(tri)); //add T.at(tri) (triangle) to badTriangles set
		}

		Poly.clear(); //create empty set polygon, consisting of edges in counterclockwise direction

//#pragma omp parallel for
		for (int tri = 0; tri < badT.size(); tri++)	//for each triangle in bad Triangle, find boundary of polygon hole
		{
			e1.a.x = badT.at(tri).a.x;
			e1.b.x = badT.at(tri).b.x;
			e2.a.x = badT.at(tri).b.x;
			e2.b.x = badT.at(tri).c.x;
			e3.a.x = badT.at(tri).c.x;
			e3.b.x = badT.at(tri).a.x;

			e1.a.y = badT.at(tri).a.y;
			e1.b.y = badT.at(tri).b.y;
			e2.a.y = badT.at(tri).b.y;
			e2.b.y = badT.at(tri).c.y;
			e3.a.y = badT.at(tri).c.y;
			e3.b.y = badT.at(tri).a.y;

			E1 = true;
			E2 = true;
			E3 = true;
			
			for (int tri1 = 0; tri1 < badT.size(); tri1++)	//for each edge in tri, if edge is not shared by any other triangles in bad triangles, add to polygon
			{
				e4.a.x = badT.at(tri1).a.x;
				e4.b.x = badT.at(tri1).b.x;
				e5.a.x = badT.at(tri1).b.x;
				e5.b.x = badT.at(tri1).c.x;
				e6.a.x = badT.at(tri1).c.x;
				e6.b.x = badT.at(tri1).a.x;

				e4.a.y = badT.at(tri1).a.y;
				e4.b.y = badT.at(tri1).b.y;
				e5.a.y = badT.at(tri1).b.y;
				e5.b.y = badT.at(tri1).c.y;
				e6.a.y = badT.at(tri1).c.y;
				e6.b.y = badT.at(tri1).a.y;

				//shared edge will be in opposite order, because all triangles are counter clockwise: ab-b'a'
				//if 2 points in tri and tri1 are same, an edge is shared
				if (!(((e1.a == e4.b) && (e1.b == e4.a)) || ((e1.a == e5.b) && (e1.b == e5.a)) || ((e1.a == e6.b) && (e1.b == e6.a))) && E1 != false)
					E1 = true;
				else
					E1 = false;

				if (!(((e2.a == e4.b) && (e2.b == e4.a)) || ((e2.a == e5.b) && (e2.b == e5.a)) || ((e2.a == e6.b) && (e2.b == e6.a))) && E2 != false)
					E2 = true;
				else
					E2 = false;

				if (!(((e3.a == e4.b) && (e3.b == e4.a)) || ((e3.a == e5.b) && (e3.b == e5.a)) || ((e3.a == e6.b) && (e3.b == e6.a))) && E3 != false)
					E3 = true;
				else
					E3 = false;
			}

			if (E1 == true)
				Poly.push_back(e1);
			if (E2 == true)
				Poly.push_back(e2);
			if (E3 == true)
				Poly.push_back(e3);
		}

		for (int tri = 0; tri < badT.size(); tri++)	//for each triangle in bad Triangle, remove triangle from T(triangulation)
			T.erase(remove(T.begin(), T.end(), badT.at(tri)), T.end());

		for (int edg = 0; edg < Poly.size(); edg++)	//re-triangulate polygon
		{
			T_new.a.x = Poly.at(edg).a.x;	//form a triangle from edge to point
			T_new.b.x = Poly.at(edg).b.x;
			T_new.c.x = A.x;

			T_new.a.y = Poly.at(edg).a.y;	//form a triangle from edge to point
			T_new.b.y = Poly.at(edg).b.y;
			T_new.c.y = A.y;

			T.push_back(T_new);			//add new triangle to T(triangulation)
		}
	}
	//3. if triangle (tri) contains vertex from super triangle, remove triangle
	for (int tri = 0; tri < T.size(); tri++)	//each triangle in triangulation
	{
		if (T.at(tri).a == supT.a || T.at(tri).b == supT.a || T.at(tri).c == supT.a || T.at(tri).a == supT.b || T.at(tri).b == supT.b || T.at(tri).c == supT.b || T.at(tri).a == supT.c || T.at(tri).b == supT.c || T.at(tri).c == supT.c)
		{
			T.erase(remove(T.begin(), T.end(), T.at(tri)), T.end());
			tri -= 1;
		}
	}
	//print all triangles
	cout << "Number of Triangles: " << T.size();
	for (int i = 0; i < T.size(); i++)
		cout << "\n\n" << T.at(i).a.x << " " << T.at(i).a.y << "\n" << T.at(i).b.x << " " << T.at(i).b.y << "\n" << T.at(i).c.x << " " << T.at(i).c.y << "\n";
}

int main(int argc, char** argv)
{
	array<double, 2> Points[8] = { {0.5,0.2}, {0.3,0.4}, {0.8,0.8}, {0.1,0.9}, {0.9,0.1},{0.6,0.5},{0.7,0.4}, {0.2,0.7} };
	
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	triangulation(Points, 8, 0.1);
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	cout<< "Time difference = " << chrono::duration_cast<chrono::microseconds>(end-begin).count() << "[us]" << endl;

	std::cin.get();

	return 0;
}