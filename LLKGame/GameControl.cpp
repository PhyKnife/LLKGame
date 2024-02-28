#include "stdafx.h"
#include "GameControl.h"
#include "GameLogic.h"
#include "ScoreLogic.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}
//���ó�Ա���Եĺ��� �ṹ������û���ô�
/**********
[������]
[����]���õ�һ��ѡ�е������
****************/
void CGameControl::setFirstVertex(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}
/**********
[������]
[����]���õڶ���ѡ�е������
****************/
void CGameControl::setSecVertex(int nRow, int nCol)
{
	m_ptSelSecond.row = nRow;
	m_ptSelSecond.col = nCol;
}
/**********
[������]
[����]��ȡ��һ��ѡ�е������
****************/
Vertex CGameControl::getFirstVertex()
{
	return m_ptSelFirst;
}
/**********
[������]
[����]��ȡ�ڶ���ѡ�е������
****************/
Vertex CGameControl::getSecVertex()
{
	return m_ptSelSecond;
}
/**********
[������]
[����]
****************/
void CGameControl::setGameModel(int nModel)
{
	m_GameModel = nModel;
}
/**********
[������]
[����]
****************/
int CGameControl::getGameModel()
{
	return m_GameModel;
}
//���ܿ��ƺ���
/**********
[������]
[����]��ʼ��Ϸ
****************/
Vertex CGameControl::startGame()
{
	//��ʼ����ͼ
	m_gameL.InitMap(m_anMap, m_mapSize);

	//�����߼��ж�����Ϊ�´�ѡ��Ϊ��һ��ѡ��Ԫ��
	m_bFirstSelect = true;
	m_bUseTool = false;
	//������ϷΪ������
	m_GameStatus = GAME_GOING;
	//���û���Ϊ�� ������Ϊ��
	m_nScore = 0;
	m_nToolNum = 0;
	//ʣ��Ԫ������Ϊ��ͼ�зǿյ�ǰԪ������
	leaveElementNum = (m_mapSize.row - 2)*(m_mapSize.col - 2);
	//����淵�ص�ͼ���������������ʱ�Ŀ���
	return m_mapSize;
}
/**********
[������]
[����]������Ϸ�Ѷ�
****************/
void CGameControl::setGameDifficulty(int nDifficulty)
{
	switch (nDifficulty)
	{
	case EASY:
	{
		//��ͼ��С��ʼ��
		m_mapSize.row = EASYMAPROW;
		m_mapSize.col = EASYMAPCOL;
	}break;
	case MEDIUM:
	{
		//��ͼ��С��ʼ��
		m_mapSize.row = MEDIUMMAPROW;
		m_mapSize.col = MEDIUMMAPCOL;
	}break;
	case DIFFICULT:
	{
		//��ͼ��С��ʼ��
		m_mapSize.row = DIFFICULTMAPROW;
		m_mapSize.col = DIFFICULTMAPCOL;
	}break;
	default:
	{
		//��ͼ��С��ʼ��
		m_mapSize.row = MEDIUMMAPROW;
		m_mapSize.col = MEDIUMMAPCOL;
	}; break;
	}
}
/**********
[������]
[����]��ȡ���λ��Ԫ��
****************/
int CGameControl::getElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}
/**********
[������]
[����]��Ӧ�û������ͼ�е�Ԫ��
****************/
int CGameControl::UserClickMapElement(int nRow, int nCol)
{
	if ((m_anMap[nRow][nCol] == BLANK)||(GAME_PAUSE==m_GameStatus))//ѡ�пհ�
	{
		return SELECTBLANK;
	}
	else if (m_bFirstSelect)
	{
		//��һ��ѡ��Ԫ�� ��¼
		m_ptSelFirst.row = nRow;
		m_ptSelFirst.col = nCol;
		m_bFirstSelect = !m_bFirstSelect;

		return FIRSTSELECT;
	}
	else
	{
		ClearLNNode();
		//�ڶ���ѡ��Ԫ��
		m_ptSelSecond.row = nRow;
		m_ptSelSecond.col = nCol;
		m_bFirstSelect = !m_bFirstSelect;
		if (m_bUseTool&&(m_anMap[m_ptSelFirst.row][m_ptSelFirst.col]==m_anMap[m_ptSelSecond.row][m_ptSelSecond.col]))
		{
			m_gameL.Clear(m_anMap, m_ptSelFirst, m_ptSelSecond);
			leaveElementNum = leaveElementNum - 2;
			m_nScore += 10;
			m_bUseTool = false;
			return CLEARSELECTUSETOOL;
		}
		//�ж��Ƿ��������
		if (m_gameL.IsLink(m_anMap,m_ptSelFirst,m_ptSelSecond,pNode,m_mapSize))
		{
			m_gameL.Clear(m_anMap, m_ptSelFirst, m_ptSelSecond);
			leaveElementNum = leaveElementNum - 2;
			m_nScore += 10;
			if ((GAME_MODEL_EASY == m_GameModel)&&(m_nScore>100))
			{
				m_nScore -= 100;
				m_nToolNum++;
			}
			return CLEARSELECT;
		}
		return RESELECT;
	}
}
/*************
[������]
[����]�����ɴ�ʱ ���ؿɴ�����
****************/
LN* CGameControl::getLineOfTwoVex()
{
	return pNode;
}
/*************
[������]
[����]��յ㼯
****************/
void CGameControl::ClearLNNode()
{
	for (int i = 0; i < MAXLNNUM; i++)
	{
		pNode[i].row = -1;
		pNode[i].col = -1;
		pNode[i].info = false;
	}
}
/*************
[������]
[����]����ͼ��Ԫ����������
****************/
bool CGameControl::resortMap()
{
	m_gameL.Resort(m_anMap, m_mapSize);
	return true;
}
/*************
[������]
[����]��Ϸ�Ƿ����
****************/
bool CGameControl::ifGameOver()
{
	if (leaveElementNum == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*************
[������]
[����]�Ƿ�ѡ����Ԫ��  ��ʾ��ť�ĸ�������
****************/
bool CGameControl::ifSelect(Vertex* selectLoc)
{
	if (m_bFirstSelect)
		return false;
	else
	{
		selectLoc->row = m_ptSelFirst.row;
		selectLoc->col = m_ptSelFirst.col;
		return true;
	}
}
/*************
[������]
[����]��ʾ
****************/
int CGameControl::getTips()
{
	m_bFirstSelect = true;//��ʾ��ť�������ǰѡ�ж���
	ClearLNNode();//��ն��㼯
	//ѭ�����ҿɴﶥ��
	for (int i = 1; i<m_mapSize.row - 1; i++)
		for (int j = 1; j < m_mapSize.col - 1; j++)//��������
		{
			//ѡ���һ������
			if (m_anMap[i][j] == BLANK)
				continue;
			m_ptSelFirst.row = i;
			m_ptSelFirst.col = j;
			for(int k=i;k<m_mapSize.row-1;k++)
				for (int l = 0; l < m_mapSize.col - 1; l++)
				{
					//ѡ��ڶ�������
					if (m_anMap[k][l] == BLANK)
						continue;
					m_ptSelSecond.row = k;
					m_ptSelSecond.col = l;

					//�ж��Ƿ��������
					if (m_gameL.IsLink(m_anMap, m_ptSelFirst, m_ptSelSecond, pNode, m_mapSize))
					{
						return TIPS_GET;
					}
				}
		}
	return TIPS_NOTFIND;
}
/*************
[������]
[����]�޸���Ϸ״̬
****************/
int CGameControl::changeGameStatus()
{
	if (m_GameStatus == GAME_GOING)
	{
		m_GameStatus = GAME_PAUSE;
		return GAME_PAUSE;
	}
	else
	{
		m_GameStatus = GAME_GOING;
		return GAME_GOING;
	}
}
/*************
[������]
[����]��ȡ��ǰ����
****************/
int CGameControl::getScore()
{
	return m_nScore;
}
/*************
[������]
[����]��Ϸ����
****************/
void CGameControl::doAfterGameOver()
{
	m_gameL.EmptyMap(m_anMap, m_mapSize);
}
/*************
[������]
[����]�Ƿ�ʹ�õ���
****************/
void CGameControl::setUseTool()
{
	m_bUseTool = false;
}
/*************
[������]
[����]���÷ֱ��浽�ļ�
****************/
bool CGameControl::saveScore(int nScore)
{
	SCORE score;
	score.nGrade = nScore;
	score.nMode = m_GameModel;

	CScoreLogic scoreL;

	return scoreL.SaveScore(score);
}