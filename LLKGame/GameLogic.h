#pragma once
#include"CONSTANT.h"
#include "global.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();

	void InitMap(int m_anMap[MAXMAPROW][MAXMAPCOL],Vertex mapSize);//��ʼ����ͼ
	bool IsLink(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect,LN pNode[MAXLNNUM],Vertex m_mapSize);//�ж��Ƿ������
	void Clear(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);//���ѡ��ͼƬ
	void Resort(int m_anMap[MAXMAPROW][MAXMAPCOL],Vertex m_mapSize);//��Ԫ������
	void EmptyMap(int m_Map[MAXMAPROW][MAXMAPCOL], Vertex mapSIze);//��յ�ͼ
private:
	//���ӹ���
	bool ClearElementByOneLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM]);
	bool ClearElementByTwoLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM]);
	bool ClearElementByThreeLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM],Vertex m_mapSize);
	//�����ж�
	bool LinkInRow(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);
	bool LinkInCol(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect);

	//�����洢
	void setLNArray(LN pNode[MAXLNNUM],Vertex sNode, int nIndex);
	bool setLNArrayF(LN pNode[MAXLNNUM], Vertex v1, Vertex v2, Vertex v3, Vertex v4,int m_anMap[MAXMAPROW][MAXMAPCOL],int nStatus);
};

