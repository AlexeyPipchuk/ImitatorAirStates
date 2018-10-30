#include "stdafx.h"

CResultOfScan::CResultOfScan(CVector coordinates, double vr, double time)
{
	this->Coordinates.x = coordinates.x;
	this->Coordinates.y = coordinates.y;
	this->Coordinates.z = coordinates.z;
	this->Vr = vr;
	detectionTime = time;
}

CResultOfScan::~CResultOfScan()
{}