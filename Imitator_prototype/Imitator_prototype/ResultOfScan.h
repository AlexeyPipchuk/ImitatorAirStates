#ifndef ResultOfScan_H
#define ResultOfScan_H

class CResultOfScan {
public:
	CResultOfScan(float x, float y, float z, float time);
	~CResultOfScan();
	float x;
	float y;
	float z;
	float detectionTime;
private:
};
#endif ResultOfScan_H