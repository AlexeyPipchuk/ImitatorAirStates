	// ����: 02.11.18
// �����: ������ �.�.
// ��������: ����������� �������� ����� - ��������, ������� ����� �����, ���������������� �� ������ �� ������ ������ � ������� �������
// getConfig() - ����� ������ ����, init(char* path, bool withStates) - ������� ������ ����. ����� Scan() ��������� ��������.

#ifndef Imitator_H
#define Imitator_H

#include "AirObject.h"
#include <vector>

#include <stdio.h>
#include <tchar.h>
#include "Imitator.h"
#include "AirObject.h"
#include "ResultOfScan.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <random> 

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
	std::mt19937 eqGenerator;
	std::mt19937 poGenerator; // ��������� ����������� ��� ����������� ������ ��������

	void getConfig(); // ������������� ��������� �������� ������ ������
	void init(char* path, bool withStates);  // ������������� ����� ������� ������ ������
	int returnUniformRandom(int max);
	int returnPoissonRandom(int lambda);
};

#endif Imitator_H