#ifndef ResultOfScan_H
#define ResultOfScan_H

class CResultOfScan {
public:
	CResultOfScan(CVector coordinates, float vr, float time);
	~CResultOfScan();
	CVector Coordinates;
	float detectionTime;
	float Vr;  // радиальная скорость 
private:
};
#endif ResultOfScan_H