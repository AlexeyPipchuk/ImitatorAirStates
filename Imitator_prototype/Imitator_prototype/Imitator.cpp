#include "stdafx.h"
#include <fstream>
#include <cstddef>

CImitator::CImitator()
{	
	GetConfig();

	this->CurrentTime = 0;
	this->targets = new CAirObject[NumberOfTargets];
	//this->TimeOfTakt = 0.0001;
}

CImitator::~CImitator()
{
	delete[] targets;
}

void CImitator::Scan()
{
	for (int i = 0; i < heightOfPlaceCorner; i++) {  // ��������� ��� ������� ������ � ������� �����
		for (int y = 0; y < widthOfAzimuth; y++) {
			if (NumberOfSteps == 0)
			{
				break; // ���������, ��� ������� ���������� ��������� 
			}
			this->CurrentTime += TimeOfTakt;
			NumberOfSteps--;
			for (int k = 0; k < this->NumberOfTargets; k++) {
				targets[k].Update(this->TimeOfTakt, this->StationCoordinates);  // �������� ���������� ��������� �����
				if (i == floor(targets[k].epsilon * 180 / 3.14159265 + .5) && y == floor(targets[k].beta * 180 / 3.14159265 +.5)) { // ���� ��� � ���� �������
					targets[k].SendToDb(k, CurrentTime);    // �������� ��������� ������ � ���� � ���� ������
					targets[k].SendToVoi(CurrentTime);    // �������� ���� �� ��� � ���������� �����
				}
			}
		}
	}
	if (NumberOfSteps > 0) // ���� ����� ������������� �� �������, ��������� ����� ������ ������
	{
		this->Scan();
	}
}

void CImitator::GetConfig()  // ������ ������ �����
{
	ifstream config("config.txt");
	int i = 6; // ���������� ���������� ��� ���������
	int j = 11; // ���������� ����������
	int k = 0;
	string buf = "";
	char* str = new char[25];
	while (k < i) {
		if (config.is_open()) {
			config.getline(str, 20, ':');
			switch (k){
			case 0:
				config.getline(str, 20, '\n');
				StationCoordinates.x = atoi(str); 
				StationCoordinates.y = atoi(str);
				StationCoordinates.z = atoi(str);
				break;
			case 1:
				config.getline(str, ';');
				NumberOfTargets = atoi(str);
				break;
			case 2:
				config.getline(str, ';');
				NumberOfSteps = atoi(str);
				break;
			case 3:
				config.getline(str, ';');
				buf = str;
				TimeOfTakt = stod(buf);
				break;
			case 4:
				config.getline(str, ';');
				widthOfAzimuth = atoi(str);
				break;
			case 5:
				config.getline(str, ';');
				heightOfPlaceCorner = atoi(str);
				break;
			}
		}
		k++;
	}

	while (k < j) {
		config.getline(str, 20, ':');
		switch (k)
		{
		case 6:
			config.getline(str, ';');
			buf = str;
			CAirObject::epsilonSKO = stod(buf);
			break;
		case 7:
			config.getline(str, ';');
			buf = str;
			CAirObject::betaSKO = stod(buf);
			break;
		case 8:
			config.getline(str, ';');
			buf = str;
			CAirObject::distanceSKO = stod(buf);
			break;
		case 9:
			config.getline(str, ';');
			buf = str;
			CAirObject::accelerationSKO = stod(buf);
			break;
		case 10:
			config.getline(str, ';');
			CAirObject::typeOfEmulation = atoi(str);
			break;
		}
		k++;
	}
	
	config.close();
}