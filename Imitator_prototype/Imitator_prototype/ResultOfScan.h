// ����: 02.11.18
// �����: ������ �.�.
// ��������: ����������� �����, ���������������� ��� ���������� ����������� ������ � ��������� �������, ������� ���������� �� ��������� ���������

#ifndef ResultOfScan_H
#define ResultOfScan_H

class CResultOfScan {
public:
	CResultOfScan(CVector coordinates, double vr, double time, double** cov);
	~CResultOfScan();
	CVector Coordinates;
	double** CovMat;
	double DetectionTime; // ����� ����������� ����
	double Vr;  // ���������� �������� 
private:
};
#endif ResultOfScan_H