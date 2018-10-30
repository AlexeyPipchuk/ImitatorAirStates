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
	// ��������� ������������� ��������� �������
	Coordinate.x = 30000 + rand() % 20000 - 10000;
	Coordinate.z = 30000 + rand() % 20000 - 10000;
	Coordinate.y = 900 + rand() % 200 - 50;
	// �� ����������� ������ - ���������� z. ������ ���� ����� �� ������������� �������, ����� �� ���� ��� �����
	// ��������� ������������� ������� ��������
	Speed.x = rand() % 500 - 250;
	Speed.y = rand() % 50 - 25;
	Speed.z = rand() % 500 - 250;
	
	switch (typeOfEmulation) {
	case 1: // ����������� ������������� ��������, �� ������ ��-�� ����� �� ���������	
		Acceleration.x = 0;
		Acceleration.z = 0;
		Acceleration.y = 0;
		break;
	case 2: // ��������� ��������
		// ��������� ������������� ������� ���������
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
	// time - ����� �����
	// �������� ���������
	Coordinate.x += Speed.x * time + 0.5 * Acceleration.x * pow(time, 2);
	Coordinate.y += Speed.y * time + 0.5 * Acceleration.y * pow(time, 2);
	Coordinate.z += Speed.z * time + 0.5 * Acceleration.z * pow(time, 2);
	// �������� ���������
	Speed.x += Acceleration.x * time;
	Speed.y += Acceleration.y * time;
	Speed.z += Acceleration.z * time;
	// �������� ����� �� ���������
	Acceleration.x += Normal_distribution[rand() % 1000];
	Acceleration.z += Normal_distribution[rand() % 1000];
	Acceleration.y += Normal_distribution[rand() % 1000];
	//cout << "Acceleration x = " << Acceleration.x << " Acceleration y = " << Acceleration.y << " Acceleration z = " << Acceleration.z << "\n";
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
}

void CAirObject::SendToVoi(const double& time)
{ 
	// ��������� ����� �� ������/���� �����/���������
	default_random_engine generator;
	normal_distribution<double> distribution(0, epsilonSKO); // ���������� ������������� (����������� 0, �������������������� ����������)
	double ep = this->epsilon + distribution(generator);
	normal_distribution<double> distribution2(0, betaSKO);
	double bt = this->beta + distribution2(generator);
	normal_distribution<double> distribution3(0, distanceSKO);
	double di = this->distance + distribution3(generator);
  // ���������� ��������� � ������ ����
	CVector coordinates; double re = betaSKO;
	coordinates.y = ep * di;   // ����� ����� 
	double katet = sqrt(pow(di, 2) - pow(coordinates.y, 2));  // ������� ��������
	coordinates.z = bt * katet; // ����� �����
	coordinates.x = sqrt(pow(katet, 2) - pow(coordinates.z, 2));  // ������� ��������
	
	CResultOfScan* package = new CResultOfScan(coordinates, 0, time); // ������������ ������ ������ ��� �������� �� ���
	// ����� ����� ��������� ����� �� ���
	delete package;
}

void CAirObject::SendToDb(const int& Nt, const double& time)
{
	cout << "\nTarget number " << Nt << " found!\nCoordinates without noise    X=" << Coordinate.x << " / Y=" << Coordinate.y << " / Z="
		<< Coordinate.z << "      after " << time << "sec";

	CReferenceState* package = new CReferenceState(Coordinate, Speed, Acceleration, time, Nt); // ������������ ������ ������ ��� �������� � ���� ������
	// ����� ����� ��������� ���� � ���� ������
}
