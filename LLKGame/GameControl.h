#pragma once
#include"global.h"
#include "CONSTANT.h"
#include "GameLogic.h"
class CGameControl
{
protected:
	//��������Ҫ����
	int m_anMap[MAXMAPROW][MAXMAPCOL];//��ͼ����

	Vertex m_ptSelFirst;//��һ��ѡ��������
	Vertex m_ptSelSecond;//�ڶ���ѡ�������

	Vertex m_mapSize;//��Ϸ��ͼ������Ԫ�ظ���

	CGameLogic m_gameL;//��Ϸ�߼�
	bool m_bFirstSelect;//�Ƿ�Ϊ��һ��ѡ�У���Ϸ�и����жϴ����߼�
	bool m_bUseTool;//�Ƿ�ʹ�õ���
	int m_nScore;//�������
	int m_nToolNum;//�������

	int m_GameStatus;//��Ϸ״̬
	int m_GameModel;//��Ϸģʽ
	//��������
	LN pNode[MAXLNNUM];
	int leaveElementNum;//ʣ��ͼƬԪ������
public:
	CGameControl();
	~CGameControl();
	virtual Vertex startGame();//��ʼ��Ϸ ��Ӧ��ʼ��Ϸ��ť
	void setGameDifficulty(int nDifficulty);//������Ϸ�Ѷ� ��Ӧ��Ϸ�ѶȰ�ť
	int UserClickMapElement(int nRow, int nCol);//��Ӧ�û������ͼ�е�Ԫ��
	virtual bool resortMap();//��Ӧ���Ű�ť
	virtual int getTips();//��ʾ�û��ɴ������ͼƬ
	virtual int getScore();//��ȡ����

	int getGameModel();//��ȡ��Ϸģʽ
	void setGameModel(int nModel);//������Ϸģʽ

	int getElement(int nRow, int nCol);//���ص��λ��Ԫ��
	LN* getLineOfTwoVex();//���ؿɴ�����
	bool ifGameOver();//��Ϸ�Ƿ����
	bool ifSelect(Vertex* selectLoc);//�Ƿ�ѡ�� ��ѡ�з���ѡ������
    int changeGameStatus();//������Ϸ״̬
	virtual void setUseTool();  //����\ȡ��ʹ�õ���
	void doAfterGameOver();//��Ϸ������ִ�д˺���
	virtual bool saveScore(int nScore);//�洢������Ϣ

protected:
	void ClearLNNode();
private:
	//setter ����
	void setFirstVertex(int nRow, int nCol);//���õ�һ��ѡ�е������
	void setSecVertex(int nRow, int nCol);//���õڶ���ѡ�е������
	Vertex getFirstVertex();//��ȡ��һ��ѡ�е������
	Vertex getSecVertex();//��ȡ�ڶ���ѡ�е������
};

