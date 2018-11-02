// Дата: 02.11.18
// Автор: Пипчук А.А.
// Описание: описывается класс, предназначенный для сохранения эталонных данных о воздушном объекте при измерении.

#ifndef ReferenceState_H
#define ReferenceState_H

class CReferenceState {
public:
	CReferenceState(CVector coordinate, CVector speed, CVector acceleration, double time, int numTarget);
	~CReferenceState();

	CVector Coordinate;
	CVector Speed;
	CVector Acceleration;
	double DetectionTime; // время обнаружения цели
	int NumberOfTarget; // порядковый номер цели
private:
};

#endif ReferenceState_H