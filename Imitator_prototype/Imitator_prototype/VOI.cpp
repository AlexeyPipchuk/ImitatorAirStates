#include "stdafx.h"

CVOI::CVOI(CVector coordinate, CVector speed, CVector acceleration, double time, int Nt)
{
	Coordinate.x = coordinate.x;
	Coordinate.y = coordinate.y;
	Coordinate.z = coordinate.z;
	Speed.x = speed.x;
	Speed.y = speed.y;
	Speed.z = speed.z;
	Acceleration.x = acceleration.x;
	Acceleration.y = acceleration.y;
	Acceleration.z = acceleration.z;
	DetectionTime = time;
	NumberOfTarget = Nt;
}

CVOI::~CVOI()
{

}