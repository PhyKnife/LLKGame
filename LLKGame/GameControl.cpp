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
//设置成员属性的函数 结构调整后没有用处
/**********
[函数名]
[功能]设置第一次选中点的坐标
****************/
void CGameControl::setFirstVertex(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}
/**********
[函数名]
[功能]设置第二次选中点的坐标
****************/
void CGameControl::setSecVertex(int nRow, int nCol)
{
	m_ptSelSecond.row = nRow;
	m_ptSelSecond.col = nCol;
}
/**********
[函数名]
[功能]获取第一次选中点的坐标
****************/
Vertex CGameControl::getFirstVertex()
{
	return m_ptSelFirst;
}
/**********
[函数名]
[功能]获取第二次选中点的坐标
****************/
Vertex CGameControl::getSecVertex()
{
	return m_ptSelSecond;
}
/**********
[函数名]
[功能]
****************/
void CGameControl::setGameModel(int nModel)
{
	m_GameModel = nModel;
}
/**********
[函数名]
[功能]
****************/
int CGameControl::getGameModel()
{
	return m_GameModel;
}
//功能控制函数
/**********
[函数名]
[功能]开始游戏
****************/
Vertex CGameControl::startGame()
{
	//初始化地图
	m_gameL.InitMap(m_anMap, m_mapSize);

	//辅助逻辑判断设置为下次选择为第一次选中元素
	m_bFirstSelect = true;
	m_bUseTool = false;
	//设置游戏为进行中
	m_GameStatus = GAME_GOING;
	//设置积分为零 道具数为零
	m_nScore = 0;
	m_nToolNum = 0;
	//剩余元素数量为地图中非空当前元素数量
	leaveElementNum = (m_mapSize.row - 2)*(m_mapSize.col - 2);
	//向界面返回地图的行列数方便绘制时的控制
	return m_mapSize;
}
/**********
[函数名]
[功能]设置游戏难度
****************/
void CGameControl::setGameDifficulty(int nDifficulty)
{
	switch (nDifficulty)
	{
	case EASY:
	{
		//地图大小初始化
		m_mapSize.row = EASYMAPROW;
		m_mapSize.col = EASYMAPCOL;
	}break;
	case MEDIUM:
	{
		//地图大小初始化
		m_mapSize.row = MEDIUMMAPROW;
		m_mapSize.col = MEDIUMMAPCOL;
	}break;
	case DIFFICULT:
	{
		//地图大小初始化
		m_mapSize.row = DIFFICULTMAPROW;
		m_mapSize.col = DIFFICULTMAPCOL;
	}break;
	default:
	{
		//地图大小初始化
		m_mapSize.row = MEDIUMMAPROW;
		m_mapSize.col = MEDIUMMAPCOL;
	}; break;
	}
}
/**********
[函数名]
[功能]获取点击位置元素
****************/
int CGameControl::getElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}
/**********
[函数名]
[功能]响应用户点击地图中的元素
****************/
int CGameControl::UserClickMapElement(int nRow, int nCol)
{
	if ((m_anMap[nRow][nCol] == BLANK)||(GAME_PAUSE==m_GameStatus))//选中空白
	{
		return SELECTBLANK;
	}
	else if (m_bFirstSelect)
	{
		//第一次选择元素 记录
		m_ptSelFirst.row = nRow;
		m_ptSelFirst.col = nCol;
		m_bFirstSelect = !m_bFirstSelect;

		return FIRSTSELECT;
	}
	else
	{
		ClearLNNode();
		//第二次选择元素
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
		//判断是否可以连线
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
[函数名]
[功能]两点间可达时 返回可达连线
****************/
LN* CGameControl::getLineOfTwoVex()
{
	return pNode;
}
/*************
[函数名]
[功能]清空点集
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
[函数名]
[功能]将地图中元素重新排序
****************/
bool CGameControl::resortMap()
{
	m_gameL.Resort(m_anMap, m_mapSize);
	return true;
}
/*************
[函数名]
[功能]游戏是否结束
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
[函数名]
[功能]是否选中了元素  提示按钮的辅助功能
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
[函数名]
[功能]提示
****************/
int CGameControl::getTips()
{
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
			for(int k=i;k<m_mapSize.row-1;k++)
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
						return TIPS_GET;
					}
				}
		}
	return TIPS_NOTFIND;
}
/*************
[函数名]
[功能]修改游戏状态
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
[函数名]
[功能]获取当前积分
****************/
int CGameControl::getScore()
{
	return m_nScore;
}
/*************
[函数名]
[功能]游戏结束
****************/
void CGameControl::doAfterGameOver()
{
	m_gameL.EmptyMap(m_anMap, m_mapSize);
}
/*************
[函数名]
[功能]是否使用道具
****************/
void CGameControl::setUseTool()
{
	m_bUseTool = false;
}
/*************
[函数名]
[功能]将得分保存到文件
****************/
bool CGameControl::saveScore(int nScore)
{
	SCORE score;
	score.nGrade = nScore;
	score.nMode = m_GameModel;

	CScoreLogic scoreL;

	return scoreL.SaveScore(score);
}