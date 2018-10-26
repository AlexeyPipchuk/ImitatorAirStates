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
	int NumberOfSteps;  // длительность модели в тактах
	float CurrentTime;
	float TimeOfTakt; // в секундах
	int widthOfAzimuth; // в градусах
	int heightOfPlaceCorner; // в градусах

	void GetConfig();
};

#endif Imitator_H