#ifndef AirObject_H
#define AirObject_H

struct CVector {
	double x, y, z;
};

class CAirObject {
public:
	CAirObject();
	~CAirObject();
	
	static double epsilonSKO; // sko(���) - �������������������� ����������, ��������� ��� ��� ����������� ����������� �������������
	static double betaSKO;
	static double distanceSKO;
	static double accelerationSKO;
	static int typeOfEmulation;

	void Update(const double& time, const CVector& station);
	void SendToVoi(const double& time);
	void SendToDb(const int& Nt, const double& time);
	double inline Get_beta()
	{
		return beta;
	}
	double inline Get_epsion()
	{
		return epsilon;
	}
private:
	double* Normal_distribution;
	double beta; // ������
	double epsilon; // ���� �����
	double distance; // ���������� �� ������� �� ����
	CVector Coordinate; // m
	CVector Speed; // m/c
	CVector Acceleration; // m/c
};
#endif AirObject_H