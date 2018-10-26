#include "stdafx.h"
#include <math.h>
#include <random>

CAirObject::CAirObject() 
{
	this->beta = 0;
	this->epsilon = 0;
	this->distance = 0;
	// случайный выбор скоростных характеристик летательного аппарата
	int type = rand() % 2;
	if (type == 1) {
		factualSpeed = 250; // 900 km/h
		cout << "Plane created\n";
	} else {
		factualSpeed = 97; // 350 km/h
		cout << "Helicopter created\n";
	}
	// не продуманный момент - координата z. лететь вниз можно до определенного момента, чтобы не уйти под землю
	// случайная инициализация вектора скорости
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
	catch (...) { // есть вероятность деления на ноль
		Speed.x = 100;
		Speed.y = 50;
		Speed.z = 100;
	}
	// случайная инициализация вектора ускорения
	Acceleration.x = rand() % 10 - 5;
	Acceleration.y = rand() % 10 - 5;
	Acceleration.z = rand() % 10 - 5;
	// случайная инициализация координат объекта
	Coordinate.x = 10000 + rand() % 20000 - 10000;
	Coordinate.y = 1000 + rand() % 500 - 250;
	Coordinate.z = 10000 + rand() % 20000 - 10000;
}

CAirObject::~CAirObject() {

}

void CAirObject::Update(const float& time, const CVector& station) {
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
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 1.0); // нормальное распределение (матожидание 0, среднеквадратическое отклонение)
	Acceleration.x += distribution(generator);
	Acceleration.x += distribution(generator);
	Acceleration.x += distribution(generator);
	// пересчет азимута
	distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2)); // расстояние до цели
	float katet = sqrt(pow(Coordinate.z - station.z, 2) + pow(Coordinate.x - station.x, 2)); // система координат, где Y это Z, X это Y, а Z это X
	float katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = katet2 / distance; // пересчет азимута
	// пересчет угла места
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.z - station.z;
	float projection = sqrt(pow(katet, 2) + pow(katet2, 2)); // проекция distance на плоскость XZ
	beta = katet2 / projection; // пересчет угла места
}

void CAirObject::SendToVoi(const float& time)
{ // наложение шумов на азимут/угол места/дистанцию
	default_random_engine generator;
	normal_distribution<float> distribution(0, 0.01); // нормальное распределение (матожидание 0, среднеквадратическое отклонение)
	float ep = this->epsilon + distribution(generator);
	normal_distribution<float> distribution2(0, 0.03);
	float bt = this->beta + distribution2(generator);
	normal_distribution<float> distribution3(0, 7.0);
	float di = this->distance + distribution3(generator);
  // вычисление координат с учетом шума
	float yWithNoise = ep * di;   // через синус
	float katet = sqrt(pow(di, 2) - pow(yWithNoise, 2));  // теорема пифагора
	float zWithNoise = bt * katet; // через синус
	float xWithNoise = sqrt(pow(katet, 2) - pow(zWithNoise, 2));  // теорема пифагора

	cout << "\nepsilonWithout " << epsilon << "   beta " << beta << "    distance " << distance << endl;
	cout << "\nep " << ep << "   bt " << bt << "    di " << di << endl;
	cout << "\nXwith noise = " << xWithNoise << "   y = " << yWithNoise << "  z = " << zWithNoise << " \n";
	
	CResultOfScan* package = new CResultOfScan(xWithNoise, yWithNoise, zWithNoise, time); // формирование пакета данных для передачи на ВОИ
	// здесь нужно отправить пакет на ВОИ
	delete package;
}