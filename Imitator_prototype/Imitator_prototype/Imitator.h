#ifndef Imitator_H
#define Imitator_H

#include "AirObject.h"
#include <vector>

class CImitator {
public:
	CImitator();
	~CImitator();
	void Scan();
private:
	CAirObject* targets;
	CVector StationCoordinates;
	int NumberOfTargets;
	int NumberOfSteps;
	float CurrentTime;
	float TimeOfTakt;
	int widthOfAzimuth;
	int heightOfPlaceCorner;
};

#endif Imitator_H