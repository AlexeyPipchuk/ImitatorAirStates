// Дата: 02.11.18
// Автор: Пипчук А.А.
// Описание: описывается класс, предназаначенный для сохранения зашумленных данных о воздушном объекте, которые передаются на вторичную обработку

#ifndef ResultOfScan_H
#define ResultOfScan_H

class CResultOfScan {
public:
	CResultOfScan(CVector coordinates, double vr, double time, double** cov);
	~CResultOfScan();
	CVector Coordinates;
	double** CovMat;
	double DetectionTime; // время обнаружения цели
	double Vr;  // радиальная скорость 
private:
};
#endif ResultOfScan_H