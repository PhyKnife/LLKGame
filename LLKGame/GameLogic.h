#pragma once
#include"CONSTANT.h"
#include "global.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

	void InitMap(int m_anMap[MAXMAPROW][MAXMAPCOL],Vertex mapSize);//初始化地图
	bool IsLink(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect,LN pNode[MAXLNNUM],Vertex m_mapSize);//判断是否可连接
	void Clear(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);//清除选中图片
	void Resort(int m_anMap[MAXMAPROW][MAXMAPCOL],Vertex m_mapSize);//将元素重排
	void EmptyMap(int m_Map[MAXMAPROW][MAXMAPCOL], Vertex mapSIze);//清空地图
private:
	//消子规则
	bool ClearElementByOneLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM]);
	bool ClearElementByTwoLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM]);
	bool ClearElementByThreeLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM],Vertex m_mapSize);
	//辅助判断
	bool LinkInRow(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);
	bool LinkInCol(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);

	//辅助存储
	void setLNArray(LN pNode[MAXLNNUM],Vertex sNode, int nIndex);
	bool setLNArrayF(LN pNode[MAXLNNUM], Vertex v1, Vertex v2, Vertex v3, Vertex v4,int m_anMap[MAXMAPROW][MAXMAPCOL],int nStatus);
};

