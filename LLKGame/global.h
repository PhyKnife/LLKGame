#pragma once
#include "Config.h"
typedef struct Vertex
{
	int row;//�к�
	int col;//�к�
}Vertex; //ͼ��������Ϣ
typedef struct LineNode
{
	int row;//�к�
	int col;//�к�
	bool info;//�Ƿ�ʹ��
}LN;//����ʱ�������Ľڵ�
typedef struct tagScore
{
	int nMode;//��Ϸģʽ
	int nGrade;//���ַ���
	int nLevel;//���ֵȼ�
	CString strName;//�������
}SCORE;
typedef struct tagRankArray
{
	CString playerName;//����
	int nGrade;//�÷�
}RankArray;
typedef struct tagCString
{
	CString CStr;
	struct tagCString* next;
}CStr,*pCStr;//�洢���а���Ϣ
