#include "stdafx.h"

CResultOfScan::CResultOfScan(CVector coordinates, double vr, double time, double** cov)
{
	this->Coordinates.x = coordinates.x;
	this->Coordinates.y = coordinates.y;
	this->Coordinates.z = coordinates.z;
	this->Vr = vr;
	DetectionTime = time;
	CovMat = cov;
}

CResultOfScan::~CResultOfScan()
{

}