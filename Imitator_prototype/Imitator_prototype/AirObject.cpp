#include "stdafx.h"
#include <math.h>
#include <random>
#include <ctime>

CAirObject::CAirObject()
{
	this->AccelerationStates = nullptr;
	this->beta = 0;
	this->epsilon = 0;
	this->distance = 0;
	this->aChangesCounter = 0;
	CovMat = new double*[4];
	for (int i = 0; i < 4; i++) {
		CovMat[i] = new double[4];
		for (int j = 0; j < 4; j++) {
			CovMat[i][j] = 0;
		}
	}
	CovMat[3][3] = pow(CAirObject::radialSko, 2);
}

CAirObject::CAirObject(int fx, int fy, int fz, const CVector& station)
{
	Coordinate.x = fx;
	Coordinate.y = fy;
	Coordinate.z = fz;
	distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2)); // расстояние до цели
	double katet = sqrt(pow(Coordinate.z - station.z, 2) + pow(Coordinate.x - station.x, 2)); // система координат, где Y это Z, X это Y, а Z это X
	double katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = katet2 / distance; // пересчет азимута
	// пересчет угла места
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.z - station.z;
	double projection = sqrt(pow(katet, 2) + pow(katet2, 2)); // проекция distance на плоскость XZ
	beta = katet2 / projection; // пересчет угла места
	std::random_device device;
	gaussGenerator.seed(device());
	CovMat = new double*[4];
	for (int i = 0; i < 4; i++) {
		CovMat[i] = new double[4];
		for (int j = 0; j < 4; j++) {
			CovMat[i][j] = 0;
		}
	}
	CovMat[3][3] = pow(CAirObject::radialSko, 2);
}

CAirObject::~CAirObject()
{
	if (AccelerationStates != nullptr) {
		delete[] AccelerationStates;
	}
}

double CAirObject::epsilonSko; // все необходимые среднеквадратические отклонения для шумов
double CAirObject::betaSko;
double CAirObject::distanceSko;
double CAirObject::accelerationSko;
double CAirObject::radialSko;
int CAirObject::typeOfEmulation;

void CAirObject::Update(const double time, const double curTime, const CVector& station) // time - время такта
{
	// пересчет координат
	Coordinate.x += Speed.x * time + 0.5 * Acceleration.x * pow(time, 2);
	Coordinate.z += Speed.z * time + 0.5 * Acceleration.z * pow(time, 2);
	Coordinate.y += Speed.y * time + 0.5 * Acceleration.y * pow(time, 2);
	if (Coordinate.y <= 0) {
		exit(-1);
	}; // объект ушел под землю

	// пересчет скоростей
	Speed.x += Acceleration.x * time;
	Speed.y += Acceleration.y * time;
	Speed.z += Acceleration.z * time;
	// пересчет радиальной скорости
	// модуль радиус-вектора
	double radiusSize = sqrt(pow((Coordinate.x - station.x), 2) + pow((Coordinate.y - station.y), 2) + pow((Coordinate.z - station.z), 2));
	CVector normir; // нормированный радиус вектор
	normir.x = (Coordinate.x - station.x) / radiusSize;
	normir.y = (Coordinate.y - station.y) / radiusSize;
	normir.z = (Coordinate.z - station.z) / radiusSize;
	radialSpeed = Speed.x * normir.x + Speed.y * normir.y + Speed.z * normir.z;
	// влиянеие шумов на ускорения если они есть
	if (accelerationSko != 0) {
		Acceleration.x += returnGaussRandom(accelerationSko);
		Acceleration.z += returnGaussRandom(accelerationSko);
		Acceleration.y += returnGaussRandom(accelerationSko);
	}
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

	if (AccelerationStates != nullptr && aChangesCounter < AccelerationStatesLen) { // если имитатор рабаботает в конфигурации с переменным ускорением
		if (AccelerationStates[aChangesCounter].time <= curTime) { // если закончилось время очередного состояния ускорения
			Acceleration.x = AccelerationStates[aChangesCounter].Acceleration.x;
			Acceleration.y = AccelerationStates[aChangesCounter].Acceleration.y;
			Acceleration.z = AccelerationStates[aChangesCounter].Acceleration.z;
			aChangesCounter++;
		}
	}
}

void CAirObject::SendToVoi(const double curTime, const bool fake)
{
	// наложение шумов на азимут/угол места/дистанцию/радиальную скорость
	radialSpeed += returnGaussRandom(radialSko);
	double ep = this->epsilon + returnGaussRandom(epsilonSko);
	double bt = this->beta + returnGaussRandom(betaSko);
	double di = this->distance + returnGaussRandom(distanceSko);
	// вычисление ковариационной матрицы

	double b1 = exp(-1 * pow(CAirObject::betaSko, 2) / 2);
	double b2 = exp(-1 * pow(CAirObject::epsilonSko, 2) / 2);

	CovMat[0][0] = (pow((b1 * b2), -2) - 2) * pow(di, 2) * pow(cos(bt), 2) * pow(cos(ep), 2) + 0.25
		* (pow(di, 2) + pow(CAirObject::distanceSko, 2)) * (1 + pow(b1, 4) * cos(2 * bt)) * (1 + pow(b2, 4) * cos(2 * ep));
	CovMat[1][1] = (pow((b1 * b2), -2) - 2) * pow(di, 2) * pow(sin(bt), 2) * pow(cos(ep), 2) + 0.25
		* (pow(di, 2) + pow(CAirObject::distanceSko, 2)) * (1 - pow(b1, 4) * cos(2 * bt)) * (1 + pow(b2, 4) * cos(2 * ep));
	CovMat[2][2] = (pow(b2, -2) - 2) * pow(di, 2) * pow(sin(ep), 2) + 0.5 * (pow(di, 2) + pow(CAirObject::distanceSko, 2))
		* (1 - pow(b2, 4) * cos(2 * ep));
	CovMat[0][1] = (pow(b1 * b2, -2) - 2) * pow(di, 2) * sin(bt) * cos(bt) * pow(cos(ep), 2) + 0.25
		* (pow(di, 2) + pow(CAirObject::distanceSko, 2)) * pow(b1, 4) * sin(2 * bt) * (1 + pow(b2, 4) * cos(2 * ep));
	CovMat[1][0] = CovMat[0][1];
	CovMat[0][2] = (pow(b1, -1) * pow(b2, -1) - pow(b1, -1) - b1) * pow(di, 2) * cos(bt) * sin(ep) * cos(ep) + 0.5
		* (pow(di, 2) + pow(CAirObject::distanceSko, 2)) * b1 * pow(b2, 4) * cos(bt) * sin(2 * ep);
	CovMat[2][0] = CovMat[0][2];
	CovMat[1][2] = (pow(b1, -1) * pow(b2, -2) - pow(b1, -1) - b1) * pow(di, 2) * sin(bt) * sin(ep) * cos(ep) + 0.5
		* (pow(di, 2) + pow(CAirObject::distanceSko, 2)) * b1 * pow(b2, 4) * sin(bt) * sin(2 * ep);
	CovMat[2][1] = CovMat[1][2];

	// вычисление координат с учетом шума
	CVector coordinates;
	coordinates.y = ep * di;   // через синус 
	double katet = sqrt(pow(di, 2) - pow(coordinates.y, 2));  // теорема пифагора
	coordinates.z = bt * katet; // через синус
	coordinates.x = sqrt(pow(katet, 2) - pow(coordinates.z, 2));  // теорема пифагора


	CResultOfScan* package = new CResultOfScan(coordinates, radialSpeed, curTime, CovMat); // формирование пакета данных для передачи на ВОИ
	cout << "\nNoised Coordinates     X=" << coordinates.x << "  Y=" << coordinates.y << "  Z=" << coordinates.z << "\n";
	// pushMeasurements(package);
	if (fake == false) {
		saveData(package);
	}
	else {
		CNoize* noize = new CNoize(coordinates, radialSpeed, curTime);
		saveData(noize);
	}

	delete package;
}

void CAirObject::SendToDb(const int numTarget, const double curTime)
{
	cout << "\nTarget " << numTarget << " :\nPerfect Coordinates    X=" << Coordinate.x << "  Y=" << Coordinate.y << "  Z="
		<< Coordinate.z << " ----------------- Detection Time " << curTime << "sec";
	cout << "\n      Accelerations    " << Acceleration.x << " / " << Acceleration.y << " / " << Acceleration.z << "  Speeds " << Speed.x << " / " << Speed.y << " / " << Speed.z;
	CReferenceState* RefPackage = new CReferenceState(Coordinate, Speed, Acceleration, curTime, numTarget); // формирование пакета данных для передачи в базу данных
	saveData(RefPackage);
	delete RefPackage;
}

double CAirObject::returnGaussRandom(double sko)
{
	std::normal_distribution<double> range(0, sko);
	return range(gaussGenerator);
}

CAirObject::CAccelerationState::CAccelerationState()
{
	time = 0;
}

CAirObject::CAccelerationState::~CAccelerationState()
{

}