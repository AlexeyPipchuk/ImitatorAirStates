#include "stdafx.h"
#include <math.h>
#include <random>

CAirObject::CAirObject() 
{
	this->beta = 0;
	this->epsilon = 0;
	this->distance = 0;
	// ��������� ����� ���������� ������������� ������������ ��������
	int type = rand() % 2;
	if (type == 1) {
		factualSpeed = 250; // 900 km/h
		cout << "Plane created\n";
	} else {
		factualSpeed = 97; // 350 km/h
		cout << "Helicopter created\n";
	}
	// �� ����������� ������ - ���������� z. ������ ���� ����� �� ������������� �������, ����� �� ���� ��� �����
	// ��������� ������������� ������� ��������
	try {
		Speed.x = rand() % (2 * factualSpeed) - factualSpeed;
		factualSpeed -= fabs(Speed.x);
		if (factualSpeed == 0) {
			throw(1);
		}
		Speed.z = rand() % (2 * factualSpeed) - factualSpeed;
		factualSpeed -= fabs(Speed.z);
		int znak = rand() % 1;
		if (znak == 1){
			Speed.y = factualSpeed;
		}
		else {
			Speed.y = factualSpeed * -1;
		}
	}
	catch (...) { // ���� ����������� ������� �� ����
		Speed.x = 100;
		Speed.y = 50;
		Speed.z = 100;
	}
	// ��������� ������������� ������� ���������
	Acceleration.x = rand() % 10 - 5;
	Acceleration.y = rand() % 10 - 5;
	Acceleration.z = rand() % 10 - 5;
	// ��������� ������������� ��������� �������
	Coordinate.x = 10000 + rand() % 20000 - 10000;
	Coordinate.y = 1000 + rand() % 500 - 250;
	Coordinate.z = 10000 + rand() % 20000 - 10000;
}

CAirObject::~CAirObject() {

}

void CAirObject::Update(const float& time, const CVector& station) {
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
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 1.0); // ���������� ������������� (����������� 0, �������������������� ����������)
	Acceleration.x += distribution(generator);
	Acceleration.x += distribution(generator);
	Acceleration.x += distribution(generator);
	// �������� �������
	distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2)); // ���������� �� ����
	float katet = sqrt(pow(Coordinate.z - station.z, 2) + pow(Coordinate.x - station.x, 2)); // ������� ���������, ��� Y ��� Z, X ��� Y, � Z ��� X
	float katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = katet2 / distance; // �������� �������
	// �������� ���� �����
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.z - station.z;
	float projection = sqrt(pow(katet, 2) + pow(katet2, 2)); // �������� distance �� ��������� XZ
	beta = katet2 / projection; // �������� ���� �����
}

void CAirObject::SendToVoi(const float& time)
{ // ��������� ����� �� ������/���� �����/���������
	default_random_engine generator;
	normal_distribution<float> distribution(0, 0.01); // ���������� ������������� (����������� 0, �������������������� ����������)
	float ep = this->epsilon + distribution(generator);
	normal_distribution<float> distribution2(0, 0.03);
	float bt = this->beta + distribution2(generator);
	normal_distribution<float> distribution3(0, 7.0);
	float di = this->distance + distribution3(generator);
  // ���������� ��������� � ������ ����
	float yWithNoise = ep * di;   // ����� �����
	float katet = sqrt(pow(di, 2) - pow(yWithNoise, 2));  // ������� ��������
	float zWithNoise = bt * katet; // ����� �����
	float xWithNoise = sqrt(pow(katet, 2) - pow(zWithNoise, 2));  // ������� ��������

	cout << "\nepsilonWithout " << epsilon << "   beta " << beta << "    distance " << distance << endl;
	cout << "\nep " << ep << "   bt " << bt << "    di " << di << endl;
	cout << "\nXwith noise = " << xWithNoise << "   y = " << yWithNoise << "  z = " << zWithNoise << " \n";
	
	CResultOfScan* package = new CResultOfScan(xWithNoise, yWithNoise, zWithNoise, time); // ������������ ������ ������ ��� �������� �� ���
	// ����� ����� ��������� ����� �� ���
	delete package;
}