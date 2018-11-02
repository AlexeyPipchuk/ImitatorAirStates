	// Дата: 02.11.18
// Автор: Пипчук А.А.
// Описание: описывается основной класс - имитатор, имеющий набор целей, инициализируемых по данным из конфиг файлов с помощью методов
// getConfig() - общий конфиг файл, init(char* path, bool withStates) - целевой конфиг файл. Метод Scan() запускает имитатор.

#ifndef Imitator_H
#define Imitator_H

#include "AirObject.h"
#include <vector>

class CImitator {
public:
	CImitator();
	~CImitator();
	void Scan();
private:
	CAirObject* targets;
	CVector stationCoordinates;
	int numberOfTargets;
	int numberOfSteps;  // длительность модели в тактах
	double currentTime;
	double timeOfTakt; // в секундах
	int widthOfAzimuth; // в градусах
	int heightOfPlaceCorner; // в градусах

	void getConfig(); // инициализация имитатора основным конфиг файлом
	void init(char* path, bool withStates);  // инициализация целей целевым конфиг файлом
};

#endif Imitator_H