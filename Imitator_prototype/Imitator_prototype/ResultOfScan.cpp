#include "stdafx.h"

CResultOfScan::CResultOfScan(float x, float y, float z, float time)
{
	this->x = x;
	this->y = y;
	this->z = z;
	detectionTime = time;
}

CResultOfScan::~CResultOfScan()
{}