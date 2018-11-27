#ifndef Saver_H
#define Saver_H

#include "ReferenceState.h"
#include "ResultOfScan.h"
#include "VOI.h"
#include "Noize.h"
#include "Mat.h"

int createMatFile();
int closeMat();
int createStruct(CReferenceState* s, int target);
int createStruct(CResultOfScan* s);
int createStruct(CNoize* s);
int createStruct(CVOI* s);
int extendArray(CReferenceState* s, mxArray *origin, int target);
int extendArray(CResultOfScan* s, mxArray *origin);
int extendArray(CNoize* s, mxArray *origin);
int extendArray(CVOI* s, mxArray *origin, int target);
int extendStruct(CReferenceState* s, mxArray *origin, int oldN, int target);
int extendStruct(CVOI* s, mxArray *origin, int oldN);
void saveData(CReferenceState* s);
void saveData(CResultOfScan* s);
void saveData(CNoize* s);
void saveData(CVOI* s);


#endif Saver_H