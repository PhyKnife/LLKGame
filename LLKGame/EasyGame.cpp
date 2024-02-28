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
[函数名]
[功能]提示
****************/
int CEasyGame::getTips()
{
	if (m_nScore < 20)
		return TIPS_SCORENOTENOUGH;

	m_bFirstSelect = true;//提示按钮会清除当前选中对象
	ClearLNNode();//清空顶点集
				  //循环查找可达顶点
	for (int i = 1; i<m_mapSize.row - 1; i++)
		for (int j = 1; j < m_mapSize.col - 1; j++)//遍历顶点
		{
			//选择第一个顶点
			if (m_anMap[i][j] == BLANK)
				continue;
			m_ptSelFirst.row = i;
			m_ptSelFirst.col = j;
			for (int k = i; k<m_mapSize.row - 1; k++)
				for (int l = 0; l < m_mapSize.col - 1; l++)
				{
					//选择第二个顶点
					if (m_anMap[k][l] == BLANK)
						continue;
					m_ptSelSecond.row = k;
					m_ptSelSecond.col = l;

					//判断是否可以相连
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
[函数名]
[功能]将地图中元素重新排序
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
[函数名]
[功能]使用道具
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
[函数名]
[功能]获取积分
****************/
int CEasyGame::getScore()
{
	return m_nToolNum * 50 + m_nScore;
}