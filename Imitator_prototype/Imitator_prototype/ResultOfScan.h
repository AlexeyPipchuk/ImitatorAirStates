#ifndef ResultOfScan_H
#define ResultOfScan_H

class CResultOfScan {
public:
	CResultOfScan(int x,int y ,int z, float time);
	~CResultOfScan();
	int x;
	int y;
	int z;
	float detectionTime;
private:
};
#endif ResultOfScan_H