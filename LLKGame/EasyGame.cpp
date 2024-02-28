#include "stdafx.h"
#include "EasyGame.h"


CEasyGame::CEasyGame()
{
	m_GameModel = GAME_MODEL_EASY;
}


CEasyGame::~CEasyGame()
{
}

/*************
[������]
[����]��ʾ
****************/
int CEasyGame::getTips()
{
	if (m_nScore < 20)
		return TIPS_SCORENOTENOUGH;

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
			for (int k = i; k<m_mapSize.row - 1; k++)
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
						m_nScore -= 20;
						return TIPS_GET;
					}
				}
		}
	return TIPS_NOTFIND;
}
/*************
[������]
[����]����ͼ��Ԫ����������
****************/
bool CEasyGame::resortMap()
{
	if (m_nScore < 50)
		return false;
	else
	{
		m_nScore -= 50;
		m_gameL.Resort(m_anMap, m_mapSize);
		return true;
	}
}
/*************
[������]
[����]ʹ�õ���
****************/
void CEasyGame::setUseTool()
{
	if (m_bUseTool)
	{
		m_bUseTool = false;
		m_nToolNum++;
	}
	else
	{
		if (m_nToolNum > 0)
		{
			m_nToolNum--;
			m_bUseTool = true;
			return;
		}
		else if (m_nScore >= 50)
		{
			m_bUseTool = true;
			m_nScore -= 50;
			return;
		}
	}
}
/*************
[������]
[����]��ȡ����
****************/
int CEasyGame::getScore()
{
	return m_nToolNum * 50 + m_nScore;
}