// ����: 02.11.18
// �����: ������ �.�.
// ��������: ����������� ����� ���������� ������� � ��� ��������� ����� ��������� ���������, ��������� ��� ����������� ����������
// ��������� ���������� ������ � ������������ ������� �������

#ifndef AirObject_H
#define AirObject_H

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
	static int typeOfEmulation; // ����� ������������ ������

	CAirObject();
	CAirObject(int fx, int fy, int fz, const CVector& station);
	~CAirObject();

	void Update(const double time, const double curTime, const CVector& station); // ���������� ���������� ���������� �������
	void SendToVoi(const double curTime); // �������� ������ �� ��������� ���������
	void SendToDb(const int numTarget, const double curTime); // �������� ������ � ���� ������
	double GetBeta() { return beta; }
	double GetEpsion() { return epsilon; }

private:
    double* normalDistributionArray; // ����� �������� �� ���� ��������� �������� ��� �����
	double beta; // ������
	double epsilon; // ���� �����
	double distance; // ���������� �� ������� �� ����
	int aChangesCounter; // ����������, ����� ��������� ��������� �� ������ ������, ���� �������� �������� �� ������������ � ���������� ����������
};
#endif AirObject_H