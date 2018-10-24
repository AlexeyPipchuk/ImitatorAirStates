#include "stdafx.h"

CResultOfScan::CResultOfScan(int x, int y, int z, float time)
{
	this->x = x;
	this->y = y;
	this->z = z;
	detectionTime = time;
}

CResultOfScan::~CResultOfScan()
{}