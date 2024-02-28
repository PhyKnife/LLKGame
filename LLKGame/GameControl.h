#pragma once
#include"global.h"
#include "CONSTANT.h"
#include "GameLogic.h"
class CGameControl
{
protected:
	//控制器必要属性
	int m_anMap[MAXMAPROW][MAXMAPCOL];//地图矩阵

	Vertex m_ptSelFirst;//第一次选择点的坐标
	Vertex m_ptSelSecond;//第二次选择点坐标

	Vertex m_mapSize;//游戏地图中行列元素个数

	CGameLogic m_gameL;//游戏逻辑
	bool m_bFirstSelect;//是否为第一次选中，游戏中辅助判断处理逻辑
	bool m_bUseTool;//是否使用道具
	int m_nScore;//积分情况
	int m_nToolNum;//道具情况

	int m_GameStatus;//游戏状态
	int m_GameModel;//游戏模式
	//辅助属性
	LN pNode[MAXLNNUM];
	int leaveElementNum;//剩余图片元素数量
public:
	CGameControl();
	~CGameControl();
	virtual Vertex startGame();//开始游戏 响应开始游戏按钮
	void setGameDifficulty(int nDifficulty);//设置游戏难度 响应游戏难度按钮
	int UserClickMapElement(int nRow, int nCol);//响应用户点击地图中的元素
	virtual bool resortMap();//响应重排按钮
	virtual int getTips();//提示用户可达的两张图片
	virtual int getScore();//获取积分

	int getGameModel();//获取游戏模式
	void setGameModel(int nModel);//设置游戏模式

	int getElement(int nRow, int nCol);//返回点击位置元素
	LN* getLineOfTwoVex();//返回可达连线
	bool ifGameOver();//游戏是否结束
	bool ifSelect(Vertex* selectLoc);//是否选中 若选中返回选中坐标
    int changeGameStatus();//设置游戏状态
	virtual void setUseTool();  //设置\取消使用道具
	void doAfterGameOver();//游戏结束后执行此函数
	virtual bool saveScore(int nScore);//存储积分信息

protected:
	void ClearLNNode();
private:
	//setter 坐标
	void setFirstVertex(int nRow, int nCol);//设置第一次选中点的坐标
	void setSecVertex(int nRow, int nCol);//设置第二次选中点的坐标
	Vertex getFirstVertex();//获取第一次选中点的坐标
	Vertex getSecVertex();//获取第二次选中点的坐标
};

