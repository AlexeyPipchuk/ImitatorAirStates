#include "stdafx.h"
#include <fstream>
#include <cstddef>
#include <random> 

CImitator::CImitator()
{	
	std::random_device device;
	eqGenerator.seed(device());
	poGenerator.seed(device());

	getConfig();

	this->currentTime = 0;
	
	switch( CAirObject::typeOfEmulation ) {
		case 1:
			init("Raid1.txt", false);
			break;
		case 2:
			init("Raid2.txt", false);
			break;
		case 3:
			init("Raid3.txt", false);
			break;
		case 4:
			init("Raid4.txt", false);
			break;
		case 5:
			init("Raid5.txt", true);
			break;
	}
}

CImitator::~CImitator()
{
	delete[] targets;
}

void CImitator::Scan()
{  
	for (int i = 0; i < widthOfAzimuth; i++) {  // пробегаем всю область обзора в двойном цикле
		for (int y = 0; y < heightOfPlaceCorner; y++) {
			if( numberOfSteps == 0 ) {
				break;
			}
			this->currentTime += timeOfTakt;
			numberOfSteps--;
			for (int k = 0; k < this->numberOfTargets; k++) {
				targets[k].Update(this->timeOfTakt, this->currentTime, this->stationCoordinates);  // пересчет параметров воздушных целей
				if (returnPoissonRandom(10) > 21) {  // какие параметры?
					cout << "\nFake target sended\n";
					int fx = returnUniformRandom(100000);
					int fy = returnUniformRandom(10000);	
					int fz = returnUniformRandom(100000);
					CAirObject* fake = new CAirObject(fx, fy, fz, stationCoordinates);
					fake->SendToVoi(currentTime);
				}
				// если луч и цель совпали
				if( y == floor(targets[k].GetEpsion() * 180 / 3.14159265 + .5) && i == floor(targets[k].GetBeta() * 180 / 3.14159265 +.5) ) {
					if (returnUniformRandom(10) == 10) { // измерить не удалось с веро€тностью 0.1
						cout << "\nMeasurement missed";
						continue;
					}
					targets[k].SendToDb(k, currentTime);    // отправка эталонных данных о цели в базу данных
					targets[k].SendToVoi(currentTime);    // отправка цели на ¬ќ» с наложением шумов
				}
			}
		}
	}
	if( numberOfSteps > 0 ) { // если врем€ моделировани€ не истекло, открываем новый период обзора
		cout << "\n/////////////////////////////////////////////////////////////////////////////////////";
		this->Scan();
	}
}

int CImitator::returnUniformRandom(int max)
{
	std::uniform_int_distribution<int> range(0, max);
	return range(eqGenerator);
}

int CImitator::returnPoissonRandom(int lambda)
{
	std::poisson_distribution<int> range(lambda);
	return range(poGenerator);
}

void CImitator::getConfig()  // парсер конфиг файла
{
	ifstream config("config.txt");
	int i = 5; // количество параметров дл€ имитатора
	int j = 10; // количество параметров
	int k = 0;
	char* str = new char[25];
	while( k < i ) {
		if( config.is_open() ) {
			config.getline(str, 20, ':');
			switch( k ) {
			case 0:
				config.getline(str, 20, ',');
				stationCoordinates.x = stod(str); 
				config.getline(str, 20, ',');
				stationCoordinates.y = stod(str);
				config.getline(str, '\n');
				stationCoordinates.z = stod(str);
				break;
			case 1:
				config.getline(str, '\n');
				numberOfSteps = atoi(str);
				break;
			case 2:
				config.getline(str, '\n');
				timeOfTakt = stod(str);
				break;
			case 3:
				config.getline(str, '\n');
				widthOfAzimuth = atoi(str);
				break;
			case 4:
				config.getline(str, '\n');
				heightOfPlaceCorner = atoi(str);
				break;
			}
		}
		k++;
	}

	while( k < j ) {
		config.getline(str, 20, ':');
		switch( k ) {
		case 5:
			config.getline(str, '\n');
			CAirObject::epsilonSko = stod(str);
			break;
		case 6:
			config.getline(str, '\n');
			CAirObject::betaSko = stod(str);
			break;
		case 7:
			config.getline(str, '\n');
			CAirObject::distanceSko = stod(str);
			break;
		case 8:
			config.getline(str, '\n');
			CAirObject::accelerationSko = stod(str);
			break;
		case 9:
			config.getline(str, '\n');
			CAirObject::typeOfEmulation = atoi(str);
			break;
		}
		k++;
	}
	config.close();
}

void CImitator::init(char* path, bool withStates)
{
	ifstream config(path);
	char* str = new char[25];
	if( config.is_open() ) {
		config.getline(str, 50, ':');
		config.getline(str, '\n');
		numberOfTargets = atoi(str);
		cout << "numberOfTargets : " << numberOfTargets << "\n";
		targets = new CAirObject[numberOfTargets];
	} else {
		exit(-1);
	}

	int i = 0;
	int j = 0;

	while( i < numberOfTargets ) {
		config.getline(str, '\n'); // попробуй потом другую штуку написать \n
		while( j < 3 ) {// 3 вектора, данный метод инициализирует только начальные значени€ векторов
			config.getline(str, 20, ':');
			switch( j ) {
			case 0:
				config.getline(str, 20, ',');
				targets[i].Coordinate.x = stod(str);
				config.getline(str, 20, ',');
				targets[i].Coordinate.y = stod(str);
				config.getline(str, '\n');
				targets[i].Coordinate.z = stod(str);
				break;
			case 1:
				config.getline(str, 20, ',');
				targets[i].Speed.x = stod(str);
				config.getline(str, 20, ',');
				targets[i].Speed.y = stod(str);
				config.getline(str, '\n');
				targets[i].Speed.z = stod(str);
				break;
			case 2:
				config.getline(str, 20, ',');
				targets[i].Acceleration.x = stod(str);
				config.getline(str, 20, ',');
				targets[i].Acceleration.y = stod(str);
				config.getline(str, '\n');
				targets[i].Acceleration.z = stod(str);
				break;
			/*default:
				assert(false);*/
			}
			j++;
		}
		if( withStates == true ) { // еслим имитатор работает по конфигурации с пересменными ускорени€ми
			config.getline(str, 50, ':');
			config.getline(str, '\n');
			targets[i].AccelerationStatesLen = atoi(str);
			targets[i].AccelerationStates = new CAirObject::CAccelerationState[targets[i].AccelerationStatesLen];
			int k = 0;
			int q = 0;
			while( k < targets[i].AccelerationStatesLen ) {
				while( q < 2 ) {
					config.getline(str, 20, ':');
					switch( q ) {
					case 0:
						config.getline(str, '\n');
						targets[i].AccelerationStates[k].time = stod(str);
						break;
					case 1:
						config.getline(str, 20, ',');
						targets[i].AccelerationStates[k].Acceleration.x = stod(str);
						config.getline(str, 20, ',');
						targets[i].AccelerationStates[k].Acceleration.y = stod(str);
						config.getline(str, '\n');
						targets[i].AccelerationStates[k].Acceleration.z = stod(str);
						break;
					}
					q++;
				}
				q = 0;
				k++;
			}
		}
		i++;
		j = 0;
	}
	config.close();
}
