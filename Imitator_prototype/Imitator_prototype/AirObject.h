// ����: 02.11.18
// �����: ������ �.�.
// ��������: ����������� ����� ���������� ������� � ��� ��������� ����� ��������� ���������, ��������� ��� ����������� ����������
// ��������� ���������� ������ � ������������ ������� �������

#ifndef AirObject_H
#define AirObject_H

#include <random> 

struct CVector {
	double x, y, z;
};

class CAirObject {

public:

	class CAccelerationState  // ��������� ��������� � �����, � ������� �� ���������� ���������
	{
	public:
		CVector Acceleration;
		double time;

		CAccelerationState();
		~CAccelerationState();
	private:
	};

	CAccelerationState* AccelerationStates; // ������ ���������� ��������� ���������
	int AccelerationStatesLen; // ����� ������� ���� 
	CVector Coordinate; // m
	CVector Speed; // m/c
	CVector Acceleration; // m/c
	static double epsilonSko; // sko(���) - �������������������� ����������, ��������� ��� ��� ����������� ����������� �������������
	static double betaSko;
	static double distanceSko;
	static double accelerationSko;
	static double radialSko;
	static int typeOfEmulation; // ����� ������������ ������

	CAirObject();
	CAirObject(int fx, int fy, int fz, const CVector& station);
	~CAirObject();

	void Update(const double time, const double curTime, const CVector& station); // ���������� ���������� ���������� �������
	void SendToVoi(const double curTime, const bool fake = false); // �������� ������ �� ��������� ���������
	void SendToDb(const int numTarget, const double curTime); // �������� ������ � ���� ������
	double GetBeta() { return beta; }
	double GetEpsion() { return epsilon; }

private:
	std::mt19937 gaussGenerator; // ���������� �������������. ����� �������� �� ���� ��������� �������� ��� �����
	double beta; // ������
	double epsilon; // ���� �����
	double distance; // ���������� �� ������� �� ����
	double radialSpeed; // ���������� �������� 
	double** CovMat; // �������������� �������
	int aChangesCounter; // ����������, ����� ��������� ��������� �� ������ ������, ���� �������� �������� �� ������������ � ���������� ����������

	double returnGaussRandom(double sko);
};
#endif AirObject_H