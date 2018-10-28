#include "stdafx.h"

CReferenceState::CReferenceState(CVector coordinate, CVector speed, CVector acceleration, float time, int Nt)
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
	detectionTime = time;
	Ntarget = Nt;
}

CReferenceState::~CReferenceState()
{

}
