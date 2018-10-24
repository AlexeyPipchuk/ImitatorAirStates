#include "stdafx.h"
#include <math.h>
#include <random>

CAirObject::CAirObject() 
{
	this->beta = 0;
	this->epsilon = 0;
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
		Speed.y = rand() % (2 * factualSpeed) - factualSpeed;
		factualSpeed -= fabs(Speed.y);
		int znak = rand() % 1;
		if (znak == 1){
			Speed.z = factualSpeed;
		}
		else {
			Speed.z = factualSpeed * -1;
		}
	}
	catch (...) {
		Speed.x = 100;
		Speed.y = 100;
		Speed.z = 50;
	}
	// ��������� ������������� ������� ���������
	Acceleration.x = rand() % 10 - 5;
	Acceleration.y = rand() % 10 - 5;
	Acceleration.z = rand() % 10 - 5;
	// ��������� ������������� ��������� �������
	Coordinate.x = 10000 + rand() % 20000 - 10000;
	Coordinate.y = 10000 + rand() % 20000 - 10000;
	Coordinate.z = 1000 + rand() % 500 - 250;
}

CAirObject::~CAirObject() {

}

void CAirObject::Update(float time, CVector station) {
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
	std::normal_distribution<double> distribution(0, 1.0);
	Acceleration.x += distribution(generator);
	Acceleration.x += distribution(generator);
	Acceleration.x += distribution(generator);
	// �������� �������
	float distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2));
	float katet = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2));
	float katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = floor( katet2 / distance * 180 / 3.14159265 + .5); // �������������� ������� � ������� � ���������� !!!
	// �������� ���� �����
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.y - station.y;
	distance = sqrt(pow(katet, 2) + pow(katet2, 2));
	beta = floor( katet2 / distance * 180 / 3.14159265 + .5); // �������������� ������� � ������� � ����������
}

void CAirObject::SetNoise()
{
	default_random_engine generator;
	normal_distribution<double> distribution(0, 5.0); // ����������� 0, �������������������� ����������
	this->Coordinate.x += distribution(generator);
	normal_distribution<double> distribution2(0, 2.0);
	this->Coordinate.y += distribution2(generator);
	normal_distribution<double> distribution3(0, 7.0);
	this->Coordinate.z += distribution3(generator);
}