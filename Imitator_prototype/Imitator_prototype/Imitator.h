	// ����: 02.11.18
// �����: ������ �.�.
// ��������: ����������� �������� ����� - ��������, ������� ����� �����, ���������������� �� ������ �� ������ ������ � ������� �������
// getConfig() - ����� ������ ����, init(char* path, bool withStates) - ������� ������ ����. ����� Scan() ��������� ��������.

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
	CVector stationCoordinates;
	int numberOfTargets;
	int numberOfSteps;  // ������������ ������ � ������
	double currentTime;
	double timeOfTakt; // � ��������
	int widthOfAzimuth; // � ��������
	int heightOfPlaceCorner; // � ��������

	void getConfig(); // ������������� ��������� �������� ������ ������
	void init(char* path, bool withStates);  // ������������� ����� ������� ������ ������
};

#endif Imitator_H