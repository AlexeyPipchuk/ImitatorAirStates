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
	float beta; // ������
	float epsilon; // ���� �����
	float distance; // ���������� �� ������� �� ����
	void Update(const float& time, const CVector& station);
	void SendToVoi(const float& time);
private:
};

#endif AirObject_H