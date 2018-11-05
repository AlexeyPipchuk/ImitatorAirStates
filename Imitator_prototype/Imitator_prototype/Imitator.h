	// Дата: 02.11.18
// Автор: Пипчук А.А.
// Описание: описывается основной класс - имитатор, имеющий набор целей, инициализируемых по данным из конфиг файлов с помощью методов
// getConfig() - общий конфиг файл, init(char* path, bool withStates) - целевой конфиг файл. Метод Scan() запускает имитатор.

#ifndef Imitator_H
#define Imitator_H

#include "AirObject.h"
#include <vector>
#include <random> 

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
	int minBeta; // в градусах
	int maxBeta; 
	int minEpsilon; // в градусах
	int maxEpsilon;
	std::mt19937 eqGenerator;
	std::mt19937 poGenerator; // генератор вероятности для определеиня ложной засветки

	void getConfig(); // инициализация имитатора основным конфиг файлом
	void init(char* path, bool withStates);  // инициализация целей целевым конфиг файлом
	int returnUniformRandom(int max);
	int returnPoissonRandom(int lambda);
};

#endif Imitator_H