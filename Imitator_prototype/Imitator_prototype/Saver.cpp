#include <iostream>
#include <stdio.h>
#include <string.h> /* For strcmp() */
#include <stdlib.h> /* For EXIT_FAILURE, EXIT_SUCCESS */
#include "stdafx.h"//дл€ структур Real
#include "mat.h"

using namespace std;

const char *file = "SavedData.mat";
MATFile *pmat;

//создание файла в режиме записи
int createMatFile() {
	printf("Creating file %s...\n\n", file);
	pmat = matOpen(file, "w");
	if (pmat == NULL) {//проверка
		printf("Error creating file %s\n", file);
		printf("(Do you have write permission in this directory?)\n");
		return(EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}
//закрытие файла
int closeMat() {
	if (matClose(pmat) != 0) {
		printf("Error closing file %s\n", file);
		return(EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}
//ѕервоначальное создание структуры
int createStruct(CReferenceState* s, int target) {
	mxArray *RealArray;
	mxArray *mx;
	int status;
	const char *fieldNames[] = { "x", "y", "z", "Vx", "Vy", "Vz", "ax", "ay", "az", "t" };

	RealArray = mxCreateStructMatrix(1, target, 10, fieldNames);//???, ÷ели, измерени€(x,y,z...)

	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.x, sizeof(&s->Coordinate.x));
	mxSetField(RealArray, target - 1, fieldNames[0], mx);//2 аргумент - цель
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.y, sizeof(&s->Coordinate.y));
	mxSetField(RealArray, target - 1, fieldNames[1], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.z, sizeof(&s->Coordinate.z));
	mxSetField(RealArray, target - 1, fieldNames[2], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.x, sizeof(s->Speed.x));
	mxSetField(RealArray, target - 1, fieldNames[3], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.y, sizeof(s->Speed.y));
	mxSetField(RealArray, target - 1, fieldNames[4], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.z, sizeof(s->Speed.z));
	mxSetField(RealArray, target - 1, fieldNames[5], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.x, sizeof(s->Acceleration.x));
	mxSetField(RealArray, target - 1, fieldNames[6], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.y, sizeof(s->Acceleration.y));
	mxSetField(RealArray, target - 1, fieldNames[7], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.z, sizeof(s->Acceleration.z));
	mxSetField(RealArray, target - 1, fieldNames[8], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(RealArray, target - 1, fieldNames[9], mx);

	status = matPutVariable(pmat, "Real", RealArray);//засовываем в .mat
	if (status != 0) {
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(RealArray, NULL);
	mxDestroyArray(RealArray);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//
int createStruct(CResultOfScan* s) {
	mxArray *POIArray;
	mxArray *mx;
	int status;
	const char *fieldNames[] = { "x", "y", "z", "Vr", "t" };

	POIArray = mxCreateStructMatrix(1, 1, 5, fieldNames);//???, ÷ели, измерени€(x,y,z...)

	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinates.x, sizeof(&s->Coordinates.x));
	mxSetField(POIArray, 0, fieldNames[0], mx);//2 аргумент - цель
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinates.y, sizeof(&s->Coordinates.y));
	mxSetField(POIArray, 0, fieldNames[1], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinates.z, sizeof(&s->Coordinates.z));
	mxSetField(POIArray, 0, fieldNames[2], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Vr, sizeof(&s->Vr));
	mxSetField(POIArray, 0, fieldNames[3], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(POIArray, 0, fieldNames[4], mx);

	status = matPutVariable(pmat, "POI", POIArray);//засовываем в .mat
	if (status != 0) {
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(POIArray, NULL);
	mxDestroyArray(POIArray);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//
int createStruct(CNoize* s) {
	mxArray *POIArray;
	mxArray *mx;
	int status;
	const char *fieldNames[] = { "x", "y", "z", "Vr", "t" };

	POIArray = mxCreateStructMatrix(1, 1, 5, fieldNames);//???, ÷ели, измерени€(x,y,z...)

	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinates.x, sizeof(&s->Coordinates.x));
	mxSetField(POIArray, 0, fieldNames[0], mx);//2 аргумент - цель
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinates.y, sizeof(&s->Coordinates.y));
	mxSetField(POIArray, 0, fieldNames[1], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinates.z, sizeof(&s->Coordinates.z));
	mxSetField(POIArray, 0, fieldNames[2], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Vr, sizeof(&s->Vr));
	mxSetField(POIArray, 0, fieldNames[3], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(POIArray, 0, fieldNames[4], mx);

	status = matPutVariable(pmat, "Noize", POIArray);//засовываем в .mat
	if (status != 0) {
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(POIArray, NULL);
	mxDestroyArray(POIArray);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//
int createStruct(CVOI* s) {
	mxArray *VOIArray;
	mxArray *mx;
	int status;
	const char *fieldNames[] = { "x", "y", "z", "Vx", "Vy", "Vz", "ax", "ay", "az", "t" };

	VOIArray = mxCreateStructMatrix(1, 1, 10, fieldNames);//???, ÷ели, измерени€(x,y,z...)

	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.x, sizeof(&s->Coordinate.x));
	mxSetField(VOIArray, 0, fieldNames[0], mx);//2 аргумент - цель
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.y, sizeof(&s->Coordinate.y));
	mxSetField(VOIArray, 0, fieldNames[1], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.z, sizeof(&s->Coordinate.z));
	mxSetField(VOIArray, 0, fieldNames[2], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.x, sizeof(s->Speed.x));
	mxSetField(VOIArray, 0, fieldNames[3], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.y, sizeof(s->Speed.y));
	mxSetField(VOIArray, 0, fieldNames[4], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.z, sizeof(s->Speed.z));
	mxSetField(VOIArray, 0, fieldNames[5], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.x, sizeof(s->Acceleration.x));
	mxSetField(VOIArray, 0, fieldNames[6], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.y, sizeof(s->Acceleration.y));
	mxSetField(VOIArray, 0, fieldNames[7], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.z, sizeof(s->Acceleration.z));
	mxSetField(VOIArray, 0, fieldNames[8], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(VOIArray, 0, fieldNames[9], mx);

	status = matPutVariable(pmat, "VOI", VOIArray);//засовываем в .mat
	if (status != 0) {
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(VOIArray, NULL);
	mxDestroyArray(VOIArray);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//–асширение field (новые данные по известной цели)
int extendArray(CReferenceState* s, mxArray *origin, int target) {
	const char *fieldNames[] = { "x", "y", "z", "Vx", "Vy", "Vz", "ax", "ay", "az", "t" };
	int status;
	mxArray *tmp;
	mxArray *mx;
	int n;
	if (mxGetField(origin, target - 1, fieldNames[0])) {
		n = mxGetN(mxGetField(origin, target - 1, fieldNames[0]));
	}
	else {
		n = 0;
	}

	//Coordinate.x
	tmp = mxGetField(origin, target - 1, fieldNames[0]);//лучше не трогать индекс
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);//расшир€ю
	for (int i = 0; i<n; i++) {//вставка старых данных
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinate.x, sizeof(s->Coordinate.x));//вставка новых данных
	mxSetField(origin, target - 1, fieldNames[0], mx);//засовываю в структуру(поле)
	//Coordinate.y
	tmp = mxGetField(origin, target - 1, fieldNames[1]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinate.y, sizeof(s->Coordinate.y));
	mxSetField(origin, target - 1, fieldNames[1], mx);
	//Coordinate.z
	tmp = mxGetField(origin, target - 1, fieldNames[2]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinate.z, sizeof(s->Coordinate.z));
	mxSetField(origin, target - 1, fieldNames[2], mx);
	//Speed.x
	tmp = mxGetField(origin, target - 1, fieldNames[3]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Speed.x, sizeof(s->Speed.x));
	mxSetField(origin, target - 1, fieldNames[3], mx);
	//Speed.y
	tmp = mxGetField(origin, target - 1, fieldNames[4]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Speed.y, sizeof(s->Speed.y));
	mxSetField(origin, target - 1, fieldNames[4], mx);
	//Speed.z
	tmp = mxGetField(origin, target - 1, fieldNames[5]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Speed.z, sizeof(s->Speed.z));
	mxSetField(origin, target - 1, fieldNames[5], mx);
	//Acceleration.x
	tmp = mxGetField(origin, target - 1, fieldNames[6]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Acceleration.x, sizeof(s->Acceleration.x));
	mxSetField(origin, target - 1, fieldNames[6], mx);
	//Acceleration.y
	tmp = mxGetField(origin, target - 1, fieldNames[7]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Acceleration.y, sizeof(s->Acceleration.y));
	mxSetField(origin, target - 1, fieldNames[7], mx);
	//Acceleration.z
	tmp = mxGetField(origin, target - 1, fieldNames[8]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Acceleration.z, sizeof(s->Acceleration.z));
	mxSetField(origin, target - 1, fieldNames[8], mx);
	//DetectionTime
	tmp = mxGetField(origin, target - 1, fieldNames[9]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(origin, target - 1, fieldNames[9], mx);
	//

	status = matPutVariable(pmat, "Real", origin);//засовываем в .mat
	if (status != 0) {//проверка
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(tmp, NULL);
	mxDestroyArray(tmp);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//
int extendArray(CResultOfScan* s, mxArray *origin) {
	const char *fieldNames[] = { "x", "y", "z", "Vr", "t" };
	int status;
	mxArray *tmp;
	mxArray *mx;
	int n = mxGetN(mxGetField(origin, 0, fieldNames[0]));

	//Coordinate.x
	tmp = mxGetField(origin, 0, fieldNames[0]);//лучше не трогать индекс
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);//расшир€ю
	for (int i = 0; i<n; i++) {//вставка старых данных
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinates.x, sizeof(s->Coordinates.x));//вставка новых данных
	mxSetField(origin, 0, fieldNames[0], mx);//засовываю в структуру(поле)
	//Coordinate.y
	tmp = mxGetField(origin, 0, fieldNames[1]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinates.y, sizeof(s->Coordinates.y));
	mxSetField(origin, 0, fieldNames[1], mx);
	//Coordinate.z
	tmp = mxGetField(origin, 0, fieldNames[2]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinates.z, sizeof(s->Coordinates.z));
	mxSetField(origin, 0, fieldNames[2], mx);
	//Vr
	tmp = mxGetField(origin, 0, fieldNames[3]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Vr, sizeof(s->Vr));
	mxSetField(origin, 0, fieldNames[3], mx);
	//DetectionTime
	tmp = mxGetField(origin, 0, fieldNames[4]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(origin, 0, fieldNames[4], mx);
	//

	status = matPutVariable(pmat, "POI", origin);//засовываем в .mat
	if (status != 0) {//проверка
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(tmp, NULL);
	mxDestroyArray(tmp);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//
int extendArray(CNoize* s, mxArray *origin) {
	const char *fieldNames[] = { "x", "y", "z", "Vr", "t" };
	int status;
	mxArray *tmp;
	mxArray *mx;
	int n = mxGetN(mxGetField(origin, 0, fieldNames[0]));

	//Coordinate.x
	tmp = mxGetField(origin, 0, fieldNames[0]);//лучше не трогать индекс
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);//расшир€ю
	for (int i = 0; i<n; i++) {//вставка старых данных
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinates.x, sizeof(s->Coordinates.x));//вставка новых данных
	mxSetField(origin, 0, fieldNames[0], mx);//засовываю в структуру(поле)
	//Coordinate.y
	tmp = mxGetField(origin, 0, fieldNames[1]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinates.y, sizeof(s->Coordinates.y));
	mxSetField(origin, 0, fieldNames[1], mx);
	//Coordinate.z
	tmp = mxGetField(origin, 0, fieldNames[2]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinates.z, sizeof(s->Coordinates.z));
	mxSetField(origin, 0, fieldNames[2], mx);
	//Vr
	tmp = mxGetField(origin, 0, fieldNames[3]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Vr, sizeof(s->Vr));
	mxSetField(origin, 0, fieldNames[3], mx);
	//DetectionTime
	tmp = mxGetField(origin, 0, fieldNames[4]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(origin, 0, fieldNames[4], mx);
	//

	status = matPutVariable(pmat, "Noize", origin);//засовываем в .mat
	if (status != 0) {//проверка
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(tmp, NULL);
	mxDestroyArray(tmp);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//
int extendArray(CVOI* s, mxArray *origin, int target) {
	const char *fieldNames[] = { "x", "y", "z", "Vx", "Vy", "Vz", "ax", "ay", "az", "t" };
	int status;
	mxArray *tmp;
	mxArray *mx;
	int n = mxGetN(mxGetField(origin, target - 1, fieldNames[0]));

	//Coordinate.x
	tmp = mxGetField(origin, target - 1, fieldNames[0]);//лучше не трогать индекс
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);//расшир€ю
	for (int i = 0; i<n; i++) {//вставка старых данных
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinate.x, sizeof(s->Coordinate.x));//вставка новых данных
	mxSetField(origin, target - 1, fieldNames[0], mx);//засовываю в структуру(поле)
	//Coordinate.y
	tmp = mxGetField(origin, target - 1, fieldNames[1]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinate.y, sizeof(s->Coordinate.y));
	mxSetField(origin, target - 1, fieldNames[1], mx);
	//Coordinate.z
	tmp = mxGetField(origin, target - 1, fieldNames[2]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Coordinate.z, sizeof(s->Coordinate.z));
	mxSetField(origin, target - 1, fieldNames[2], mx);
	//Speed.x
	tmp = mxGetField(origin, target - 1, fieldNames[3]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Speed.x, sizeof(s->Speed.x));
	mxSetField(origin, target - 1, fieldNames[3], mx);
	//Speed.y
	tmp = mxGetField(origin, target - 1, fieldNames[4]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Speed.y, sizeof(s->Speed.y));
	mxSetField(origin, target - 1, fieldNames[4], mx);
	//Speed.z
	tmp = mxGetField(origin, target - 1, fieldNames[5]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Speed.z, sizeof(s->Speed.z));
	mxSetField(origin, target - 1, fieldNames[5], mx);
	//Acceleration.x
	tmp = mxGetField(origin, target - 1, fieldNames[6]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Acceleration.x, sizeof(s->Acceleration.x));
	mxSetField(origin, target - 1, fieldNames[6], mx);
	//Acceleration.y
	tmp = mxGetField(origin, target - 1, fieldNames[7]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Acceleration.y, sizeof(s->Acceleration.y));
	mxSetField(origin, target - 1, fieldNames[7], mx);
	//Acceleration.z
	tmp = mxGetField(origin, target - 1, fieldNames[8]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->Acceleration.z, sizeof(s->Acceleration.z));
	mxSetField(origin, target - 1, fieldNames[8], mx);
	//DetectionTime
	tmp = mxGetField(origin, target - 1, fieldNames[9]);
	mx = mxCreateDoubleMatrix(1, n + 1, mxREAL);
	for (int i = 0; i<n; i++) {
		memcpy((void *)(mxGetPr(mx) + i), (void *)(mxGetPr(tmp) + i), sizeof(mxGetPr(tmp)));
	}
	memcpy((void *)(mxGetPr(mx) + n), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(origin, target - 1, fieldNames[9], mx);
	//

	status = matPutVariable(pmat, "VOI", origin);//засовываем в .mat
	if (status != 0) {//проверка
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(tmp, NULL);
	mxDestroyArray(tmp);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//–асширение структуры (нова€ цель)
int extendStruct(CReferenceState* s, mxArray *origin, int oldN, int target) {
	mxArray *extendedStruct;
	mxArray *mx;
	int status;
	const char *fieldNames[] = { "x", "y", "z", "Vx", "Vy", "Vz", "ax", "ay", "az", "t" };

	extendedStruct = mxCreateStructMatrix(1, target, 10, fieldNames);//расшир€ем

	mxArray *tmp;
	for (int j = 0; j < oldN; j++) {//горизонталь
		for (int i = 0; i < 10; i++){//вертикаль
			tmp = mxGetField(origin, j, fieldNames[i]);
			mxSetField(extendedStruct, j, fieldNames[i], tmp);
		}
	}

	//«аносим новые данные в только что расширенную структуру
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.x, sizeof(&s->Coordinate.x));
	mxSetField(extendedStruct, target - 1, fieldNames[0], mx);//2 аргумент - цель
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.y, sizeof(&s->Coordinate.y));
	mxSetField(extendedStruct, target - 1, fieldNames[1], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.z, sizeof(&s->Coordinate.z));
	mxSetField(extendedStruct, target - 1, fieldNames[2], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.x, sizeof(s->Speed.x));
	mxSetField(extendedStruct, target - 1, fieldNames[3], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.y, sizeof(s->Speed.y));
	mxSetField(extendedStruct, target - 1, fieldNames[4], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.z, sizeof(s->Speed.z));
	mxSetField(extendedStruct, target - 1, fieldNames[5], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.x, sizeof(s->Acceleration.x));
	mxSetField(extendedStruct, target - 1, fieldNames[6], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.y, sizeof(s->Acceleration.y));
	mxSetField(extendedStruct, target - 1, fieldNames[7], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.z, sizeof(s->Acceleration.z));
	mxSetField(extendedStruct, target - 1, fieldNames[8], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(extendedStruct, target - 1, fieldNames[9], mx);
	//

	status = matPutVariable(pmat, "Real", extendedStruct);//засовываем в .mat
	if (status != 0) {
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(extendedStruct, NULL);
	mxDestroyArray(extendedStruct);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//
int extendStruct(CVOI* s, mxArray *origin, int oldN) {
	mxArray *extendedStruct;
	mxArray *mx;
	int status;
	const char *fieldNames[] = { "x", "y", "z", "Vx", "Vy", "Vz", "ax", "ay", "az", "t" };

	extendedStruct = mxCreateStructMatrix(1, oldN + 1, 10, fieldNames);//расшир€ем

	mxArray *tmp;
	for (int j = 0; j < oldN; j++) {//горизонталь
		for (int i = 0; i < 10; i++){//вертикаль
			tmp = mxGetField(origin, j, fieldNames[i]);
			mxSetField(extendedStruct, j, fieldNames[i], tmp);
		}
	}

	//«аносим новые данные в только что расширенную структуру
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.x, sizeof(&s->Coordinate.x));
	mxSetField(extendedStruct, oldN, fieldNames[0], mx);//2 аргумент - цель
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.y, sizeof(&s->Coordinate.y));
	mxSetField(extendedStruct, oldN, fieldNames[1], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Coordinate.z, sizeof(&s->Coordinate.z));
	mxSetField(extendedStruct, oldN, fieldNames[2], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.x, sizeof(s->Speed.x));
	mxSetField(extendedStruct, oldN, fieldNames[3], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.y, sizeof(s->Speed.y));
	mxSetField(extendedStruct, oldN, fieldNames[4], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Speed.z, sizeof(s->Speed.z));
	mxSetField(extendedStruct, oldN, fieldNames[5], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.x, sizeof(s->Acceleration.x));
	mxSetField(extendedStruct, oldN, fieldNames[6], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.y, sizeof(s->Acceleration.y));
	mxSetField(extendedStruct, oldN, fieldNames[7], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->Acceleration.z, sizeof(s->Acceleration.z));
	mxSetField(extendedStruct, oldN, fieldNames[8], mx);
	//
	mx = mxCreateDoubleMatrix(1, 1, mxREAL);
	memcpy((void *)(mxGetPr(mx)), &s->DetectionTime, sizeof(s->DetectionTime));
	mxSetField(extendedStruct, oldN, fieldNames[9], mx);
	//

	status = matPutVariable(pmat, "VOI", extendedStruct);//засовываем в .mat
	if (status != 0) {
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxSetData(extendedStruct, NULL);
	mxDestroyArray(extendedStruct);
	mxSetData(mx, NULL);
	mxDestroyArray(mx);

	return(EXIT_SUCCESS);
}
//ѕрием данных
void saveData(CReferenceState* s) {
	mxArray *mx;
	mx = matGetVariable(pmat, "Real");
	int oldN;
	if (mx == NULL) {
		createStruct(s, s->NumberOfTarget+1);
	}
	else if ((oldN = mxGetN(mx)) <s->NumberOfTarget+1){ //нова€ цель
		extendStruct(s, mx, oldN, s->NumberOfTarget+1);
	}
	else { //нова€ дата
		extendArray(s, mx, s->NumberOfTarget+1);
	}

	mxSetData(mx, NULL);
	mxDestroyArray(mx);
}
//
void saveData(CResultOfScan* s) {
	mxArray *mx;
	mx = matGetVariable(pmat, "POI");
	if (mx == NULL) {
		createStruct(s);
	}
	else { //нова€ дата
		extendArray(s, mx);
	}

	mxSetData(mx, NULL);
	mxDestroyArray(mx);
}
//
void saveData(CNoize* s) {
	mxArray *mx;
	mx = matGetVariable(pmat, "Noize");
	if (mx == NULL) {
		createStruct(s);
	}
	else { //нова€ дата
		extendArray(s, mx);
	}

	mxSetData(mx, NULL);
	mxDestroyArray(mx);
}
//
void saveData(CVOI* s) {
	mxArray *mx;
	mx = matGetVariable(pmat, "VOI");
	int oldN;
	if (mx == NULL && s->NumberOfTarget == 1) {
		createStruct(s);
	}
	else if ((oldN = mxGetN(mx)) <s->NumberOfTarget){ //нова€ цель
		extendStruct(s, mx, oldN);
	}
	else { //нова€ дата
		extendArray(s, mx, s->NumberOfTarget);
	}

	mxSetData(mx, NULL);
	mxDestroyArray(mx);
}