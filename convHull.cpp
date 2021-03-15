#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include "omp.h"
#include <chrono>

using namespace std;

double crossProduct(vector<double> vect_A, vector<double> vect_B)
{
	double x, y, z;
	x = vect_A.at(1) * vect_B.at(2) - vect_A.at(2) * vect_B.at(1);
	y = vect_A.at(2) * vect_B.at(0) - vect_A.at(0) * vect_B.at(2);
	z = vect_A.at(0) * vect_B.at(1) - vect_A.at(1) * vect_B.at(0);
	return z;
}

void convHull(array<double, 2> Points[], vector<int> CH, int N)
{
	/*
		Gift-wrapping algorithm: Not the most efficient but a good starter code. O(nk)
		Jarvis, R. A. (1973). "On the identification of the convex hull of a finite set of points in the plane". Information Processing Letters
		https://en.wikipedia.org/wiki/Gift_wrapping_algorithm
	*/

	int leftMost, hullPoint, endPoint, i;
	vector<double> vec1, vec2;
	vec1.clear();
	vec2.clear();
	double cp;

	//1. Find leftmost point as starter point
	sort(Points, Points + N);
	leftMost = 0; //once sorted by x-coordinates, left most point is the first point, guaranteed to be part of the convex hull

	hullPoint = leftMost;
	endPoint = -1;

	i = 0;
	while (endPoint != leftMost)
	{
		CH.push_back(hullPoint);
		endPoint = 0;
		for (int j = 0; j < N; j++)
		{
			vec1.push_back(Points[endPoint][0] - Points[CH.at(i)][0]);    //vec1: P[i]-endPoint
			vec1.push_back(Points[endPoint][1] - Points[CH.at(i)][1]);
			vec1.push_back(0);

			vec2.push_back(Points[j][0] - Points[CH.at(i)][0]);    //vec2: P[i]-j
			vec2.push_back(Points[j][1] - Points[CH.at(i)][1]);
			vec2.push_back(0);

			//if cross-product of vec1Xvec2<0, vec1 is to the left of line2
			cp = crossProduct(vec1, vec2);
			if (endPoint == hullPoint || cp > 0)
				endPoint = j;

			vec1.clear();
			vec2.clear();
		}
		i += 1;
		hullPoint = endPoint;
	}

	for (int k = 0; k < CH.size(); k++)
		cout << CH.at(k) << " ";
}

int main(int argc, char** argv)
{
	//construct the convex hull for the set of points
	vector<int> CH;	//vector that store the points forming the convex hull
	CH.clear();
	array<double, 2> Points[8] = { {0.5,0.2}, {0.3,0.4}, {0.8,0.8}, {0.1,0.9}, {0.9,0.1},{0.6,0.5},{0.7,0.4}, {0.2,0.7} };
	
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	convHull(Points, CH, 8);
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	cout<< "Time difference = " << chrono::duration_cast<chrono::microseconds>(end-begin).count() << "[us]" << endl;

	std::cin.get();

	return 0;
}
