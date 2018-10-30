#include "stdafx.h"
#include <math.h>
#include <random>
#include <ctime>

CAirObject::CAirObject() 
{
	Normal_distribution = new double[1000];
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, accelerationSKO);
	for (int i = 0; i < 1000; i++)
	{
		Normal_distribution[i] = distribution(generator);
		//cout << i << " = " << Normal_distribution[i] << "\n";
	}
	this->beta = 0;
	this->epsilon = 0;
	this->distance = 0;
	// случайная инициализация координат объекта
	Coordinate.x = 30000 + rand() % 20000 - 10000;
	Coordinate.z = 30000 + rand() % 20000 - 10000;
	Coordinate.y = 900 + rand() % 200 - 50;
	// не продуманный момент - координата z. лететь вниз можно до определенного момента, чтобы не уйти под землю
	// случайная инициализация вектора скорости
	Speed.x = rand() % 500 - 250;
	Speed.y = rand() % 50 - 25;
	Speed.z = rand() % 500 - 250;
	
	switch (typeOfEmulation) {
	case 1: // равномерное прямолинейное движение, не совсем из-за шумов на ускорении	
		Acceleration.x = 0;
		Acceleration.z = 0;
		Acceleration.y = 0;
		break;
	case 2: // случайное движение
		// случайная инициализация вектора ускорения
		Acceleration.x = rand() % 10 - 5;
		Acceleration.y = rand() % 10 - 5;
		Acceleration.z = rand() % 10 - 5;
		break;
	default:
		cout << "\nUndef type of emulation\n";
	}
}

CAirObject::~CAirObject() {
	delete[] Normal_distribution;
}

double CAirObject::epsilonSKO;
double CAirObject::betaSKO;
double CAirObject::distanceSKO;
double CAirObject::accelerationSKO;
int CAirObject::typeOfEmulation;

void CAirObject::Update(const double& time, const CVector& station) {
	// time - время такта
	// пересчет координат
	Coordinate.x += Speed.x * time + 0.5 * Acceleration.x * pow(time, 2);
	Coordinate.y += Speed.y * time + 0.5 * Acceleration.y * pow(time, 2);
	Coordinate.z += Speed.z * time + 0.5 * Acceleration.z * pow(time, 2);
	// пересчет скоростей
	Speed.x += Acceleration.x * time;
	Speed.y += Acceleration.y * time;
	Speed.z += Acceleration.z * time;
	// влиянеие шумов на ускорения
	Acceleration.x += Normal_distribution[rand() % 1000];
	Acceleration.z += Normal_distribution[rand() % 1000];
	Acceleration.y += Normal_distribution[rand() % 1000];
	//cout << "Acceleration x = " << Acceleration.x << " Acceleration y = " << Acceleration.y << " Acceleration z = " << Acceleration.z << "\n";
	// пересчет азимута
	distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2)); // расстояние до цели
	double katet = sqrt(pow(Coordinate.z - station.z, 2) + pow(Coordinate.x - station.x, 2)); // система координат, где Y это Z, X это Y, а Z это X
	double katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = katet2 / distance; // пересчет азимута
	// пересчет угла места
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.z - station.z;
	double projection = sqrt(pow(katet, 2) + pow(katet2, 2)); // проекция distance на плоскость XZ
	beta = katet2 / projection; // пересчет угла места
}

void CAirObject::SendToVoi(const double& time)
{ 
	// наложение шумов на азимут/угол места/дистанцию
	default_random_engine generator;
	normal_distribution<double> distribution(0, epsilonSKO); // нормальное распределение (матожидание 0, среднеквадратическое отклонение)
	double ep = this->epsilon + distribution(generator);
	normal_distribution<double> distribution2(0, betaSKO);
	double bt = this->beta + distribution2(generator);
	normal_distribution<double> distribution3(0, distanceSKO);
	double di = this->distance + distribution3(generator);
  // вычисление координат с учетом шума
	CVector coordinates; double re = betaSKO;
	coordinates.y = ep * di;   // через синус 
	double katet = sqrt(pow(di, 2) - pow(coordinates.y, 2));  // теорема пифагора
	coordinates.z = bt * katet; // через синус
	coordinates.x = sqrt(pow(katet, 2) - pow(coordinates.z, 2));  // теорема пифагора
	
	CResultOfScan* package = new CResultOfScan(coordinates, 0, time); // формирование пакета данных для передачи на ВОИ
	// здесь нужно отправить пакет на ВОИ
	delete package;
}

void CAirObject::SendToDb(const int& Nt, const double& time)
{
	cout << "\nTarget number " << Nt << " found!\nCoordinates without noise    X=" << Coordinate.x << " / Y=" << Coordinate.y << " / Z="
		<< Coordinate.z << "      after " << time << "sec";

	CReferenceState* package = new CReferenceState(Coordinate, Speed, Acceleration, time, Nt); // формирование пакета данных для передачи в базу данных
	// здесь нужно отправить пкет в базу данных
}
