#ifndef ReferenceState_H
#define ReferenceState_H

class CReferenceState {
public:
	CReferenceState(CVector coordinate, CVector speed, CVector acceleration, float time, int Nt);
	~CReferenceState();

	CVector Coordinate;
	CVector Speed;
	CVector Acceleration;
	float detectionTime;
	int Ntarget;
private:
};

#endif ReferenceState_H