#ifndef AirObject_H
#define AirObject_H

struct CVector {
	float x, y, z;
};

class CAirObject {
public:
	CAirObject();
	~CAirObject();
	int factualSpeed;
	CVector Coordinate; // m
	CVector Speed; // m/c
	CVector Acceleration; // m/c
	int beta; // азимут
	int epsilon; // угол места
	void Update(float time, CVector station);
	void SetNoise();
private: 
};

#endif AirObject_H