#include "stdafx.h"
#include <fstream>

CImitator::CImitator()
{
	//ifstream config("config.txt");
	//if (config.is_open()) {
	//	config >> 
	//}
	//config.close();
	this->CurrentTime = 0;
	this->NumberOfSteps = 8;
	this->NumberOfTargets = 3;
	this->StationCoordinates.x = 0;
	this->StationCoordinates.y = 0;
	this->StationCoordinates.z = 0;
	this->TimeOfTakt = 0.0001f; // 100 микросекунд
	this->widthOfAzimuth = 90;
	this->heightOfPlaceCorner = 5;
	this->targets = new CAirObject[NumberOfTargets];
}

CImitator::~CImitator()
{
	delete[] targets;
}

void CImitator::Scan()
{
	vector<CResultOfScan*> package;
	for (int k = 0; k < this->NumberOfTargets; k++){  // пересчет параметров воздушных целей
		targets[k].Update(this->TimeOfTakt, this->StationCoordinates);
	}

	for (int i = 0; i < heightOfPlaceCorner; i++) {
		for (int y = 0; y < widthOfAzimuth; y++) {
			this->CurrentTime += TimeOfTakt;
			for (int k = 0; k < this->NumberOfTargets; k++) {
				if (i == targets[k].epsilon && y == targets[k].beta) {
					cout << "\nTarget found!\nCoordinates without noise " << targets[k].Coordinate.x << " / " << targets[k].Coordinate.y << " / " 
						<< targets[k].Coordinate.z << "      after " << CurrentTime << "sec";
					targets[k].SetNoise();    // наложение шумов
					cout << "\nCoordinates with noise " << targets[k].Coordinate.x << " / " << targets[k].Coordinate.y << " / "
						<< targets[k].Coordinate.z << "      after " << CurrentTime << "sec\n\n";
					package.push_back(new CResultOfScan(targets[k].Coordinate.x, targets[k].Coordinate.y, targets[k].Coordinate.z, CurrentTime));
				}
			}
		}
	}
	for each (CResultOfScan* target in package)
	{
		delete target;
	}
}