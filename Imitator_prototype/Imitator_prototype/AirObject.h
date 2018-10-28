#ifndef AirObject_H
#define AirObject_H

struct CVector {
	float x, y, z;
};

class CAirObject {
public:
	CAirObject();
	~CAirObject();
	
	float beta; // ������
	float epsilon; // ���� �����
	static float epsilonSKO; // sko(���) - �������������������� ����������, ��������� ��� ��� ����������� ����������� �������������
	static float betaSKO;
	static float distanceSKO;
	static float accelerationSKO;
	static int typeOfEmulation;

	void Update(const float& time, const CVector& station);
	void SendToVoi(const float& time);
	void SendToDb(const int& Nt, const float& time);
private:
	int factualSpeed;
	float distance; // ���������� �� ������� �� ����
	CVector Coordinate; // m
	CVector Speed; // m/c
	CVector Acceleration; // m/c
};
#endif AirObject_H