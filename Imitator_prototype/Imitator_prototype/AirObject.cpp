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
}

CAirObject::CAirObject(int fx, int fy, int fz, const CVector& station)
{
	Coordinate.x = fx;
	Coordinate.y = fy;
	Coordinate.z = fz;
	distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2)); // ���������� �� ����
	double katet = sqrt(pow(Coordinate.z - station.z, 2) + pow(Coordinate.x - station.x, 2)); // ������� ���������, ��� Y ��� Z, X ��� Y, � Z ��� X
	double katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = katet2 / distance; // �������� �������
	// �������� ���� �����
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.z - station.z;
	double projection = sqrt(pow(katet, 2) + pow(katet2, 2)); // �������� distance �� ��������� XZ
	beta = katet2 / projection; // �������� ���� �����
	std::random_device device;
	gaussGenerator.seed(device());
}

CAirObject::~CAirObject() 
{
	if (AccelerationStates != nullptr) {
		delete[] AccelerationStates;
	}
}

double CAirObject::epsilonSko; // ��� ����������� �������������������� ���������� ��� �����
double CAirObject::betaSko;
double CAirObject::distanceSko;
double CAirObject::accelerationSko;
int CAirObject::typeOfEmulation; 

void CAirObject::Update(const double time, const double curTime, const CVector& station) // time - ����� �����
{                
	// �������� ���������
	Coordinate.x += Speed.x * time + 0.5 * Acceleration.x * pow(time, 2);
	Coordinate.z += Speed.z * time + 0.5 * Acceleration.z * pow(time, 2);
	Coordinate.y += Speed.y * time + 0.5 * Acceleration.y * pow(time, 2);
	if (Coordinate.y <= 0) {
		exit(-1);
	}; // ������ ���� ��� �����

	// �������� ���������
	Speed.x += Acceleration.x * time;
	Speed.y += Acceleration.y * time;
	Speed.z += Acceleration.z * time;
	// �������� ����� �� ��������� ���� ��� ����
	if( accelerationSko != 0 ) {
		Acceleration.x += returnGaussRandom(accelerationSko);
		Acceleration.z += returnGaussRandom(accelerationSko);
		Acceleration.y += returnGaussRandom(accelerationSko);
	}
	// �������� �������
	distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2)); // ���������� �� ����
	double katet = sqrt(pow(Coordinate.z - station.z, 2) + pow(Coordinate.x - station.x, 2)); // ������� ���������, ��� Y ��� Z, X ��� Y, � Z ��� X
	double katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = katet2 / distance; // �������� �������
	// �������� ���� �����
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.z - station.z;
	double projection = sqrt(pow(katet, 2) + pow(katet2, 2)); // �������� distance �� ��������� XZ
	beta = katet2 / projection; // �������� ���� �����

	if( AccelerationStates != nullptr && aChangesCounter < AccelerationStatesLen ) { // ���� �������� ���������� � ������������ � ���������� ����������
		if( AccelerationStates[aChangesCounter].time <= curTime ) { // ���� ����������� ����� ���������� ��������� ���������
			Acceleration.x = AccelerationStates[aChangesCounter].Acceleration.x;
			Acceleration.y = AccelerationStates[aChangesCounter].Acceleration.y;
			Acceleration.z = AccelerationStates[aChangesCounter].Acceleration.z;
			aChangesCounter++;
		}
	}
}

void CAirObject::SendToVoi(const double curTime)
{ 
	// ��������� ����� �� ������/���� �����/���������
	double ep = this->epsilon + returnGaussRandom(epsilonSko);
	double bt = this->beta + returnGaussRandom(betaSko);
	double di = this->distance + returnGaussRandom(distanceSko);
  // ���������� ��������� � ������ ����
	CVector coordinates; double re = betaSko;
	coordinates.y = ep * di;   // ����� ����� 
	double katet = sqrt(pow(di, 2) - pow(coordinates.y, 2));  // ������� ��������
	coordinates.z = bt * katet; // ����� �����
	coordinates.x = sqrt(pow(katet, 2) - pow(coordinates.z, 2));  // ������� ��������
	
	CResultOfScan* package = new CResultOfScan(coordinates, 0, curTime); // ������������ ������ ������ ��� �������� �� ���
	// ����� ����� ��������� ����� �� ���
	delete package;
}

void CAirObject::SendToDb(const int numTarget, const double curTime)
{
	cout << "\nTarget number " << numTarget << " found!\nCoordinates without noise    X=" << Coordinate.x << " / Y=" << Coordinate.y << " / Z="
		<< Coordinate.z << "      after " << curTime << "sec";
	cout << "\nacceleration " << Acceleration.x << " / " << Acceleration.y << " / " << Acceleration.z << "  speed " << Speed.x << " / " << Speed.y << " / " << Speed.z;

	CReferenceState* package = new CReferenceState(Coordinate, Speed, Acceleration, curTime, numTarget); // ������������ ������ ������ ��� �������� � ���� ������
	// ����� ����� ��������� ���� � ���� ������
	delete package;
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