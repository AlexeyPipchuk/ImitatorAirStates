// ����: 02.11.18
// �����: ������ �.�.
// ��������: ����������� �����, ��������������� ��� ���������� ��������� ������ � ��������� ������� ��� ���������.

#ifndef ReferenceState_H
#define ReferenceState_H

class CReferenceState {
public:
	CReferenceState(CVector coordinate, CVector speed, CVector acceleration, double time, int numTarget);
	~CReferenceState();

	CVector Coordinate;
	CVector Speed;
	CVector Acceleration;
	double DetectionTime; // ����� ����������� ����
	int NumberOfTarget; // ���������� ����� ����
private:
};

#endif ReferenceState_H