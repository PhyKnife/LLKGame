#pragma once
#include "CONSTANT.h"
#include "global.h"
class CScoreDao
{
public:
	CScoreDao();
	~CScoreDao();
	bool Save(const CString & filePath, SCORE &score);
	int Read(const CString &filePath,CString mesStr[MAXRANKMES]);
	void PraseCString(CString cstr, SCORE &score);
};

