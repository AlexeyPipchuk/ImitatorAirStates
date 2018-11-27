#include "stdafx.h"

CNoize::CNoize(CVector coordinates, double vr, double time)
{
	this->Coordinates.x = coordinates.x;
	this->Coordinates.y = coordinates.y;
	this->Coordinates.z = coordinates.z;
	this->Vr = vr;
	DetectionTime = time;
}

CNoize::~CNoize()
{}