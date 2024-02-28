#pragma once
#include "global.h"
#include "CONSTANT.h"
#include "ScoreDao.h"
class CScoreLogic
{
protected:
	CScoreDao scoreDao;
public:
	CScoreLogic();
	~CScoreLogic();
	bool SaveScore(SCORE& score);//���������Ϣ
	int SearchRank(RankArray rankArray[MAXRANKLEVEL], int nModel);//��ȡ���а������Ϣ
private:
	void swapScore(SCORE &score1, SCORE &score2);//����SCORE��Ϣ
};

