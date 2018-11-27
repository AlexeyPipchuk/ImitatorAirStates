#ifndef VOI_H
#define VOI_H

class CVOI {
public:
	CVOI(CVector coordinate, CVector speed, CVector acceleration, double time, int Nt);
	~CVOI();

	CVector Coordinate;
	CVector Speed;
	CVector Acceleration;
	double DetectionTime;
	int NumberOfTarget;
private:
};

#endif VOI_H